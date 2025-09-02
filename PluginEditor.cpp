#include "PluginProcessor.h"
#include "PluginEditor.h"

static constexpr float kMonoAverageScale = 0.5f; // (L+R)/2 ~ like 1k/1k passive summer

GainMonoAudioProcessor::GainMonoAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
    apvts(*this, nullptr, "PARAMS", createLayout())
{
    smoothedGain.reset(44100.0, 0.02); // will be reset properly in prepareToPlay
}

juce::AudioProcessorValueTreeState::ParameterLayout GainMonoAudioProcessor::createLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "gainDb", "Gain (dB)",
        juce::NormalisableRange<float>(-24.0f, 24.0f, 0.01f, 1.0f),
        0.0f));

    params.push_back(std::make_unique<juce::AudioParameterBool>(
        "mono", "Mono Sum", false));

    return { params.begin(), params.end() };
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainMonoAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    // Allow mono or stereo I/O, but we keep output at least stereo for FL Studio niceness
    const auto& mainIn = layouts.getMainInputChannelSet();
    const auto& mainOut = layouts.getMainOutputChannelSet();
    if (mainIn.isDisabled() || mainOut.isDisabled())
        return false;

    // Support mono<->mono, stereo<->stereo
    if (!(mainIn == juce::AudioChannelSet::mono() || mainIn == juce::AudioChannelSet::stereo()))
        return false;
    if (!(mainOut == juce::AudioChannelSet::mono() || mainOut == juce::AudioChannelSet::stereo()))
        return false;

    return true;
}
#endif

void GainMonoAudioProcessor::prepareToPlay(double sampleRate, int /*samplesPerBlock*/)
{
    smoothedGain.reset(sampleRate, 0.02f); // 20 ms smoothing
    // Initialize smoothing to current target
    const float dB = apvts.getRawParameterValue("gainDb")->load();
    smoothedGain.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(dB));
}

void GainMonoAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    juce::ignoreUnused(midi);

    const int numCh = buffer.getNumChannels();
    const int numSamp = buffer.getNumSamples();

    // Update gain target each block
    const float targetLin = juce::Decibels::decibelsToGain(apvts.getRawParameterValue("gainDb")->load());
    smoothedGain.setTargetValue(targetLin);

    const bool doMono = apvts.getRawParameterValue("mono")->load() > 0.5f;

    if (doMono)
    {
        // Sum all available input channels -> mono, scale to avoid clipping
        auto* ch0 = buffer.getWritePointer(0);

        for (int n = 0; n < numSamp; ++n)
        {
            float sum = 0.0f;
            for (int c = 0; c < numCh; ++c)
                sum += buffer.getReadPointer(c)[n];

            // For stereo sources this equals (L+R)/2. We want (L+R)/2 exactly, so multiply by 2 then by 0.5 (kMonoAverageScale).
            const float avg = sum / (float)juce::jmax(1, numCh);
            const float monoSample = avg * (numCh == 2 ? kMonoAverageScale * 2.0f : 1.0f);
            ch0[n] = monoSample;
        }

        // Duplicate the mono signal to all output channels, applying smoothed gain sample-by-sample
        for (int n = 0; n < numSamp; ++n)
        {
            const float g = smoothedGain.getNextValue(); // Get smoothed gain per sample
            const float v = ch0[n] * g;
            for (int c = 0; c < numCh; ++c)
                buffer.getWritePointer(c)[n] = v;
        }
    }
    else
    {
        // Stereo passthrough with gain, per-channel, sample-by-sample
        for (int n = 0; n < numSamp; ++n)
        {
            const float g = smoothedGain.getNextValue(); // Get smoothed gain per sample
            for (int c = 0; c < numCh; ++c)
            {
                auto* data = buffer.getWritePointer(c);
                data[n] *= g;
            }
        }
    }
}

void GainMonoAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream mos(destData, true);
    apvts.state.writeToStream(mos);
}

void GainMonoAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData(data, (size_t)sizeInBytes);
    if (tree.isValid())
        apvts.replaceState(tree);
}

juce::AudioProcessorEditor* GainMonoAudioProcessor::createEditor()
{
    return new GainMonoAudioProcessorEditor(*this);
}

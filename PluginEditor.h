#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class GainMonoAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit GainMonoAudioProcessorEditor(GainMonoAudioProcessor&);
    ~GainMonoAudioProcessorEditor() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    GainMonoAudioProcessor& processor;

    juce::Slider gainSlider;
    juce::ToggleButton monoButton{ "Mono Sum" };

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    std::unique_ptr<SliderAttachment> gainAttach;
    std::unique_ptr<ButtonAttachment> monoAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainMonoAudioProcessorEditor)
};

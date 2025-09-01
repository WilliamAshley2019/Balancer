#include "PluginEditor.h"

GainMonoAudioProcessorEditor::GainMonoAudioProcessorEditor(GainMonoAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    setSize(340, 180);

    // Gain
    gainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    gainSlider.setRange(-24.0, 24.0, 0.01);
    gainSlider.setSkewFactor(1.0);
    addAndMakeVisible(gainSlider);

    // Mono toggle
    addAndMakeVisible(monoButton);

    // Attachments
    gainAttach = std::make_unique<SliderAttachment>(processor.apvts, "gainDb", gainSlider);
    monoAttach = std::make_unique<ButtonAttachment>(processor.apvts, "mono", monoButton);
}

void GainMonoAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(18.0f);
    g.drawFittedText("Gain + Mono", getLocalBounds().removeFromTop(28), juce::Justification::centred, 1);
}

void GainMonoAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(16);
    auto top = area.removeFromTop(32);
    juce::ignoreUnused(top);

    auto center = area.reduced(8);
    gainSlider.setBounds(center.removeFromLeft(center.getWidth() / 2).reduced(8));
    monoButton.setBounds(center.reduced(8));
}

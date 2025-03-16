/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleEQAudioProcessorEditor::SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
  DBG("EQPlotComponent::paint() called"); 
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(600, 400);
    addAndMakeVisible(eqPlot);

    startTimerHz(30);
}

SimpleEQAudioProcessorEditor::~SimpleEQAudioProcessorEditor()
{
}

//==============================================================================
void SimpleEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello Worldd!", getLocalBounds(), juce::Justification::centred, 1);
}

void SimpleEQAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    eqPlot.setBounds(getLocalBounds().reduced(20));
}

void SimpleEQAudioProcessorEditor::timerCallback()
{   
    //auto coeffs = processorRef.getFilterCoefficients();
    eqPlot.setFilterCoefficients(audioProcessor.getFilterCoefficients());

    //eqPlot.setFilterCoefficients(coeffs);
    eqPlot.repaint();
}

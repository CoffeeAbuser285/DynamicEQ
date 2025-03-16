#include "EQPlotComponent.h"

EQPlotComponent::EQPlotComponent()
{
    magnitudeResponse.resize(200); // 200 frequency points
}

void EQPlotComponent::setFilterCoefficients(const juce::dsp::IIR::Coefficients<float>::Ptr& coeffs)
{
    filterCoefficients = coeffs;
    updateResponseCurve();
    repaint();
}

void EQPlotComponent::updateResponseCurve()
{
    if (!filterCoefficients) return;

    for (size_t i = 0; i < magnitudeResponse.size(); ++i)
    {
        double freq = 20.0 * std::pow(10.0, (i / 199.0) * 3.0); // Log scale from 20Hz to 20kHz
        double mag = filterCoefficients->getMagnitudeForFrequency(freq, 44100.0);

        magnitudeResponse[i] = juce::Decibels::gainToDecibels(static_cast<float>(mag));
    }
}

void EQPlotComponent::paint(juce::Graphics& g)
{
    DBG("EQPlotComponent::paint() called"); 
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    
    auto bounds = getLocalBounds().toFloat();
    juce::Path eqCurve;
    
    for (size_t i = 0; i < magnitudeResponse.size(); ++i)
    {
        float x = juce::jmap<float>(static_cast<float>(i), 0.0f, magnitudeResponse.size() - 1, bounds.getX(), bounds.getRight());
        float y = juce::jmap<float>(magnitudeResponse[i], -24.0f, 24.0f, bounds.getBottom(), bounds.getY());

        if (i == 0)
            eqCurve.startNewSubPath(x, y);
        else
            eqCurve.lineTo(x, y);
    }

    g.strokePath(eqCurve, juce::PathStrokeType(2.0f));
}

void EQPlotComponent::resized()
{
    repaint();
}
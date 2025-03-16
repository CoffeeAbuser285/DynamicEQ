#pragma once
#include <JuceHeader.h>

class EQPlotComponent : public juce::Component
{
public:
    EQPlotComponent();
    void paint(juce::Graphics& g) override;
    void resized() override;

    void setFilterCoefficients(const juce::dsp::IIR::Coefficients<float>::Ptr& coeffs);

private:
    std::vector<float> magnitudeResponse;
    juce::dsp::IIR::Coefficients<float>::Ptr filterCoefficients;

    void updateResponseCurve();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EQPlotComponent)
};
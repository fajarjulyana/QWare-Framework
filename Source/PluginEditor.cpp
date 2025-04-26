/*
  ==============================================================================

    PluginEditor.cpp
    Created for QWare.id Audio Plugin
    Developer: Fajar Julyana
    JUCE Framework Version: 7.0.9

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
/**
 * Constructor for the editor
 * Sets up all UI components and connects them to parameters
 */
QWareAudioProcessorEditor::QWareAudioProcessorEditor(QWareAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Apply custom look and feel
    setLookAndFeel(&qwareLookAndFeel);
    
    // Set plugin window size
    setSize(400, 300);
    
    // Setup gain slider
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag); // Rotary knob style
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    gainSlider.setRange(0.0, 1.0, 0.01);
    gainSlider.setDoubleClickReturnValue(true, 0.5); // Double-click resets to 0.5
    
    // Setup gain label
    addAndMakeVisible(gainLabel);
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centred);
    gainLabel.attachToComponent(&gainSlider, false);
    
    // Setup company and developer labels
    addAndMakeVisible(companyLabel);
    companyLabel.setText("QWare.id", juce::dontSendNotification);
    companyLabel.setJustificationType(juce::Justification::centred);
    companyLabel.setFont(juce::Font(18.0f, juce::Font::bold));
    
    addAndMakeVisible(developerLabel);
    developerLabel.setText("Developer: Fajar Julyana", juce::dontSendNotification);
    developerLabel.setJustificationType(juce::Justification::centred);
    developerLabel.setFont(juce::Font(14.0f));
    
    // Create parameter attachments - these connect UI controls to parameters
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "gain", gainSlider);
}

/**
 * Destructor
 * Ensures the look and feel is properly cleaned up
 */
QWareAudioProcessorEditor::~QWareAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

/**
 * Paint method - handles custom drawing of the plugin UI
 */
void QWareAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Draw background image if available
    if (qwareLookAndFeel.backgroundImage.isValid())
    {
        g.drawImageWithin(qwareLookAndFeel.backgroundImage, 
                         0, 0, getWidth(), getHeight(),
                         juce::RectanglePlacement::stretchToFit);
    }
    else
    {
        // Fallback background if image isn't available
        g.fillAll(juce::Colour(30, 30, 34));
        g.setColour(juce::Colours::white.withAlpha(0.2f));
        g.drawRect(getLocalBounds(), 1);  // Draw a subtle border
    }
    
    // Draw company logo if available
    if (qwareLookAndFeel.logoImage.isValid())
    {
        const int logoWidth = 100;
        const int logoHeight = 40;
        g.drawImage(qwareLookAndFeel.logoImage, 
                    getWidth() - logoWidth - 10, 10, 
                    logoWidth, logoHeight, 
                    0, 0, 
                    qwareLookAndFeel.logoImage.getWidth(), qwareLookAndFeel.logoImage.getHeight(),
                    true);  // Enable alpha blending
    }
}

/**
 * Handles component layout when the window is resized
 */
void QWareAudioProcessorEditor::resized()
{
    // Define margins and layout areas
    auto area = getLocalBounds().reduced(20);
    
    // Company and developer info at the top
    companyLabel.setBounds(area.removeFromTop(30));
    developerLabel.setBounds(area.removeFromTop(20));
    
    area.removeFromTop(20); // Add some spacing
    
    // Controls section
    auto gainArea = area.removeFromTop(150);
    gainSlider.setBounds(gainArea.withSizeKeepingCentre(100, 100));
    // Note: gainLabel is already attached to the slider, so we don't need to position it separately
    
    // Additional controls would be positioned here
}
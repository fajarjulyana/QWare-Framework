/*
  ==============================================================================

    PluginEditor.h
    Created for QWare.id Audio Plugin
    Developer: Fajar Julyana
    JUCE Framework Version: 7.0.9

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
 * The editor/UI class for the audio processor
 * Handles all user interface elements and interaction
 */
class QWareAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    /**
     * Constructor
     * Sets up UI components and parameter attachments
     */
    QWareAudioProcessorEditor(QWareAudioProcessor&);
    
    /**
     * Destructor
     */
    ~QWareAudioProcessorEditor() override;
    
    /**
     * Draws the plugin UI
     */
    void paint(juce::Graphics&) override;
    
    /**
     * Handles component layout when the window is resized
     */
    void resized() override;
    
private:
    // Reference to the processor that owns this editor
    QWareAudioProcessor& audioProcessor;
    
    // Custom look and feel for QWare styling
    QWareLookAndFeel qwareLookAndFeel;
    
    // UI Components
    juce::Slider gainSlider;       // Slider for controlling gain
    juce::Label gainLabel;         // Label for the gain slider
    juce::Label companyLabel;      // Label displaying company name
    juce::Label developerLabel;    // Label displaying developer credit
    
    // Parameter attachments - connect UI controls to processor parameters
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QWareAudioProcessorEditor)
};
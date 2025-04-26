/*
  ==============================================================================

    PluginProcessor.h
    Created for QWare.id Audio Plugin
    Developer: Fajar Julyana
    JUCE Framework Version: 7.0.9

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "QWareLookAndFeel.h"

//==============================================================================
/**
 * The main audio processor class
 * Handles audio processing, parameter management, and plugin state
 */
class QWareAudioProcessor : public juce::AudioProcessor
{
public:
    /**
     * Constructor
     * Sets up audio buses and initializes parameters
     */
    QWareAudioProcessor();
    
    /**
     * Destructor
     */
    ~QWareAudioProcessor() override;

    /**
     * Called before playback starts to prepare resources
     */
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    
    /**
     * Called when playback stops to free resources
     */
    void releaseResources() override;
    
    /**
     * Checks if the given bus layout is supported by this processor
     */
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    
    /**
     * The main processing function - where audio is processed
     */
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    /**
     * Creates the editor/UI for this processor
     */
    juce::AudioProcessorEditor* createEditor() override;
    
    /**
     * Indicates if this processor has an editor
     */
    bool hasEditor() const override;
    
    /**
     * Returns the name of the processor
     */
    const juce::String getName() const override;
    
    /**
     * MIDI capability flags
     */
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    
    /**
     * Returns the tail length in seconds
     */
    double getTailLengthSeconds() const override;
    
    /**
     * Program handling methods
     * (not fully implemented in this basic framework)
     */
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;
    
    /**
     * State saving and loading methods
     */
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    
    /**
     * Parameter tree for managing plugin parameters
     * Makes parameters accessible to the UI and host automation
     */
    juce::AudioProcessorValueTreeState parameters;
    
private:
    /**
     * Creates the parameter layout for the plugin
     */
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    // Audio processing parameters
    float gain = 1.0f;  // Default gain value
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QWareAudioProcessor)
};
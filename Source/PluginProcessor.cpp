/*
  ==============================================================================

    PluginProcessor.cpp
    Created for QWare.id Audio Plugin
    Developer: Fajar Julyana
    JUCE Framework Version: 7.0.9

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
QWareAudioProcessor::QWareAudioProcessor()
    : AudioProcessor(BusesProperties()
                     .withInput("Input", juce::AudioChannelSet::stereo(), true)    // Stereo input bus
                     .withOutput("Output", juce::AudioChannelSet::stereo(), true)), // Stereo output bus
      parameters(*this, nullptr, "Parameters", createParameters())
{
}

QWareAudioProcessor::~QWareAudioProcessor() 
{
    // Clean up any dynamically allocated resources here if needed
}

/**
 * Creates the parameter layout for the plugin
 * Add all audio parameters here so they can be automated and saved/loaded
 */
juce::AudioProcessorValueTreeState::ParameterLayout QWareAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // Add a gain parameter (0.0 to 1.0, default 0.5)
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "gain",             // Parameter ID
        "Gain",             // Parameter name
        0.0f,               // Minimum value
        1.0f,               // Maximum value
        0.5f));             // Default value
    
    // Add more parameters as needed for your plugin
    // Example:
    // params.push_back(std::make_unique<juce::AudioParameterFloat>(
    //    "frequency", "Frequency", 20.0f, 20000.0f, 1000.0f));
    
    return { params.begin(), params.end() };
}

void QWareAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Initialize DSP modules here based on sample rate and block size
    // This is called when the audio stream starts
}

void QWareAudioProcessor::releaseResources()
{
    // Free any resources allocated in prepareToPlay
    // This is called when the audio stream stops
}

/**
 * Checks if a particular bus layout is supported
 * This implementation accepts mono or stereo for both input and output
 */
bool QWareAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    // Accept mono or stereo for both input and output
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
    
    // Input and output must have same channel configuration
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
    
    return true;
}

/**
 * The main processing function - where audio samples are processed
 * In this simple implementation, we just apply gain to the audio
 */
void QWareAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // Clear any output channels that don't contain input data
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
    
    // Get current gain parameter value
    gain = *parameters.getRawParameterValue("gain");
    
    // Process each channel's samples with gain
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        
        // Apply gain to each sample
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] *= gain;
        }
    }
}

/**
 * Creates the editor/UI for this processor
 */
juce::AudioProcessorEditor* QWareAudioProcessor::createEditor()
{
    return new QWareAudioProcessorEditor(*this);
}

bool QWareAudioProcessor::hasEditor() const 
{ 
    return true;  // This plugin has a custom GUI
}

const juce::String QWareAudioProcessor::getName() const 
{ 
    return "QWare Audio Plugin"; 
}

// MIDI capability methods - this plugin doesn't process MIDI
bool QWareAudioProcessor::acceptsMidi() const { return false; }
bool QWareAudioProcessor::producesMidi() const { return false; }
bool QWareAudioProcessor::isMidiEffect() const { return false; }

// No tail on this plugin
double QWareAudioProcessor::getTailLengthSeconds() const { return 0.0; }

// Program handling methods - basic implementation with just one program
int QWareAudioProcessor::getNumPrograms() { return 1; }
int QWareAudioProcessor::getCurrentProgram() { return 0; }
void QWareAudioProcessor::setCurrentProgram(int index) {}
const juce::String QWareAudioProcessor::getProgramName(int index) { return {}; }
void QWareAudioProcessor::changeProgramName(int index, const juce::String& newName) {}

/**
 * Saves the plugin state to a memory block
 * This is called when the host wants to save the plugin state
 */
void QWareAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // Save parameters
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

/**
 * Restores the plugin state from memory
 * This is called when the host loads a saved plugin state
 */
void QWareAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

// Create the factory that creates instances of our plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new QWareAudioProcessor();
}
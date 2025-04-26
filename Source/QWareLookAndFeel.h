/*
  ==============================================================================

    QWareLookAndFeel.h
    Created for QWare.id Audio Plugin
    Developer: Fajar Julyana
    JUCE Framework Version: 7.0.9

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
 * Custom Look And Feel class for QWare.id styling
 * This class handles the custom drawing of UI components
 * including knobs based on PNG sprite strips.
 */
class QWareLookAndFeel : public juce::LookAndFeel_V4
{
public:
    QWareLookAndFeel()
    {
        // Load background image from binary resources
        backgroundImage = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
        
        // Load company logo from binary resources
        logoImage = juce::ImageCache::getFromMemory(BinaryData::qware_logo_png, BinaryData::qware_logo_pngSize);
        
        // Load vertical knob image strip from binary resources
        // This is expected to be a vertical strip of frames showing different knob positions
        knobStripImage = juce::ImageCache::getFromMemory(BinaryData::knob_vertical_png, BinaryData::knob_vertical_pngSize);
    }
    
    /**
     * Custom drawing method for rotary sliders.
     * Uses the vertical sprite strip to display the knob at different positions.
     */
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                      float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                      juce::Slider& slider) override
{
    if (knobStripImage.isValid())
    {
        const int numFrames = knobStripImage.getHeight() / knobStripImage.getWidth();
        const int frameIndex = juce::jlimit(0, numFrames - 1, (int)(sliderPos * (numFrames - 1)));
        const int frameWidth = knobStripImage.getWidth();
        const int frameHeight = frameWidth; // Assuming square frames

        juce::Rectangle<int> sourceRect(0, frameIndex * frameHeight, frameWidth, frameHeight);

        const int knobSize = juce::jmin(width, height);
        juce::Rectangle<int> destRect(
            x + (width - knobSize) / 2,
            y + (height - knobSize) / 2,
            knobSize,
            knobSize
        );

        g.drawImage(knobStripImage,
                    destRect.getX(), destRect.getY(), destRect.getWidth(), destRect.getHeight(),
                    sourceRect.getX(), sourceRect.getY(), sourceRect.getWidth(), sourceRect.getHeight());
    }
    else
    {
        LookAndFeel_V4::drawRotarySlider(g, x, y, width, height, sliderPos, rotaryStartAngle, rotaryEndAngle, slider);
    }
}

    
    // Images used for custom UI rendering
    juce::Image backgroundImage;
    juce::Image logoImage;
    juce::Image knobStripImage;
};

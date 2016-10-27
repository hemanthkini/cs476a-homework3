// CS476A Homework 3
// Author: Hemanth Kini
// Description: Plugin GUI Header file

// Modified from BasicAudioPlugin and MIDIPolySynth Starter Code:
// Original Heading follows below:

// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple JUCE sine wave synthesizer plug-in

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "TronLookAndFeel.h"


//==============================================================================
/**
*/
class BasicAudioPlugInAudioProcessorEditor  :
public AudioProcessorEditor,
private Slider::Listener,
private ToggleButton::Listener
{
public:
    BasicAudioPlugInAudioProcessorEditor (BasicAudioPlugInAudioProcessor&);
    ~BasicAudioPlugInAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider* slider) override;
    void buttonClicked (Button* button) override;
    
    //==============================================================================
    // Populate third slider's GUI based on toggle
    void populateFlute();
    void populateClarinet();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BasicAudioPlugInAudioProcessor& processor;
    
    // All our GUI elements.
    Slider gainSlider;
    Slider mixSlider;
    ToggleButton fluteOnButton;
    ToggleButton clarinetOnButton;
    Slider pressureSlider;
    Label pressureLabel;
    Slider breathSlider;
    Label breathLabel;
    Slider thirdSlider;
    Label thirdLabel;
    
    Label titleLabel;
    Label gainLabel;
    Label mixLabel;
    Label fluteOnLabel;
    Label clarinetOnLabel;
    
    TronLookAndFeel otherLookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicAudioPlugInAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED

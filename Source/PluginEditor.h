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

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BasicAudioPlugInAudioProcessor& processor;
    
    Slider frequencySlider;
    Slider gainSlider;
    ToggleButton onOffButton;
    
    Label frequencyLabel;
    Label gainLabel;
    Label onOffLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicAudioPlugInAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED

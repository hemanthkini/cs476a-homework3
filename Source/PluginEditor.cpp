// CS476A Homework 3
// Author: Hemanth Kini
// Description: Plugin GUI C++ file

// Modified from BasicAudioPlugin and MIDIPolySynth Starter Code:
// Original Heading follows below:

// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple JUCE sine wave synthesizer plug-in

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
BasicAudioPlugInAudioProcessorEditor::BasicAudioPlugInAudioProcessorEditor (BasicAudioPlugInAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 100);
    
    // configuring frequency slider and adding it to the main window
    addAndMakeVisible (frequencySlider);
    frequencySlider.setRange (50.0, 5000.0);
    frequencySlider.setSkewFactorFromMidPoint (500.0);
    frequencySlider.setValue(1000);
    frequencySlider.addListener(this);
    
    // configuring frequency label box and adding it to the main window
    addAndMakeVisible(frequencyLabel);
    frequencyLabel.setText ("Frequency", dontSendNotification);
    frequencyLabel.attachToComponent (&frequencySlider, true);
    
    
    // configuring gain slider and adding it to the main window
    addAndMakeVisible (gainSlider);
    gainSlider.setRange (0.0, 1.0);
    gainSlider.setValue(0.5);
    gainSlider.addListener (this);
    
    
    // configuring gain label and adding it to the main window
    addAndMakeVisible(gainLabel);
    gainLabel.setText ("Gain", dontSendNotification);
    gainLabel.attachToComponent (&gainSlider, true);
    
    
    // configuring on/off button and adding it to the main window
    addAndMakeVisible(onOffButton);
    onOffButton.addListener(this);
    
    
    // configuring on/off label and adding it to the main window
    addAndMakeVisible(onOffLabel);
    onOffLabel.setText ("On/Off", dontSendNotification);
    onOffLabel.attachToComponent (&onOffButton, true);
}

BasicAudioPlugInAudioProcessorEditor::~BasicAudioPlugInAudioProcessorEditor()
{
}

//==============================================================================
void BasicAudioPlugInAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::lightgrey);
}

void BasicAudioPlugInAudioProcessorEditor::resized()
{
    const int sliderLeft = 80;
    frequencySlider.setBounds (sliderLeft, 10, getWidth() - sliderLeft - 20, 20);
    gainSlider.setBounds (sliderLeft, 40, getWidth() - sliderLeft - 20, 20);
    onOffButton.setBounds (sliderLeft, 70, getWidth() - sliderLeft - 20, 20);
}

void BasicAudioPlugInAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (processor.samplingRate > 0.0){
        if (slider == &frequencySlider){
            processor.sine.setFrequency(frequencySlider.getValue());
        }
        else if (slider == &gainSlider){
            processor.gain = gainSlider.getValue();
        }
    }
}

void BasicAudioPlugInAudioProcessorEditor::buttonClicked(Button *button){
    if(button == &onOffButton && onOffButton.getToggleState()){
        processor.onOff = 1.0;
    }
    else{
        processor.onOff = 0.0;
    }
}

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
#include "TronLookAndFeel.h"


//==============================================================================
BasicAudioPlugInAudioProcessorEditor::BasicAudioPlugInAudioProcessorEditor (BasicAudioPlugInAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 100);
    
    // configuring frequency slider and adding it to the main window
    addAndMakeVisible (gainSlider);
    gainSlider.setRange (0, 1.0);
    gainSlider.setValue(0.5);
    gainSlider.addListener(this);
    gainSlider.setLookAndFeel(&otherLookAndFeel);
    
    // configuring frequency label box and adding it to the main window
    addAndMakeVisible(frequencyLabel);
    frequencyLabel.setText ("Frequency", dontSendNotification);
    frequencyLabel.attachToComponent (&gainSlider, true);
    
    
    // configuring gain slider and adding it to the main window
    addAndMakeVisible (mixSlider);
    mixSlider.setRange (0.0, 1.0);
    mixSlider.setValue(0.5);
    mixSlider.addListener (this);
    
    
    // configuring gain label and adding it to the main window
    addAndMakeVisible(gainLabel);
    gainLabel.setText ("Gain", dontSendNotification);
    gainLabel.attachToComponent (&mixSlider, true);
    
    
    // configuring on/off button and adding it to the main window
    addAndMakeVisible(fluteOnButton);
    fluteOnButton.addListener(this);
    fluteOnButton.setLookAndFeel(&otherLookAndFeel);
    
    // configuring on/off label and adding it to the main window
    addAndMakeVisible(onOffLabel);
    onOffLabel.setText ("On/Off", dontSendNotification);
    onOffLabel.attachToComponent (&fluteOnButton, true);
    
    // configuring pressure slider and adding it to the main window
    addAndMakeVisible (pressureSlider);
    pressureSlider.setRange (0, 1.0);
    pressureSlider.setValue(0.5);
    pressureSlider.addListener(this);
    pressureSlider.setLookAndFeel(&otherLookAndFeel);
    
    // configuring breath slider and adding it to the main window
    addAndMakeVisible (breathSlider);
    breathSlider.setRange (0, 1.0);
    breathSlider.setValue(0.5);
    breathSlider.addListener(this);
    breathSlider.setLookAndFeel(&otherLookAndFeel);
    
    // configuring third slider and adding it to the main window
    addAndMakeVisible (thirdSlider);
    thirdSlider.setRange (0, 1.0);
    thirdSlider.setValue(0.5);
    thirdSlider.addListener(this);
    thirdSlider.setLookAndFeel(&otherLookAndFeel);
    
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
    breathSlider.setBounds (sliderLeft, 10, getWidth() - sliderLeft - 20, 20);
    mixSlider.setBounds (sliderLeft, 40, getWidth() - sliderLeft - 20, 20);
    fluteOnButton.setBounds (sliderLeft, 70, getWidth() - sliderLeft - 20, 20);
}

void BasicAudioPlugInAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (processor.samplingRate > 0.0){
        if (slider == &thirdSlider){
            //processor.sine.setFrequency(gainSlider.getValue());
        }
        else if (slider == &mixSlider){
            processor.gain = mixSlider.getValue();
        }
    }
}

void BasicAudioPlugInAudioProcessorEditor::buttonClicked(Button *button){
    if(button == &fluteOnButton && fluteOnButton.getToggleState()){
        processor.onOff = 1.0;
    }
    else{
        processor.onOff = 0.0;
    }
}

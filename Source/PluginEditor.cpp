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
    setSize (400, 400);
    
    // configuring frequency slider and adding it to the main window
    addAndMakeVisible (gainSlider);
    gainSlider.setRange (0, 1.0);
    gainSlider.setValue(0.5);
    gainSlider.addListener(this);
    gainSlider.setLookAndFeel(&otherLookAndFeel);
    
    // configuring gain label box and adding it to the main window
    addAndMakeVisible(gainLabel);
    gainLabel.setText ("Gain", dontSendNotification);
    gainLabel.attachToComponent (&gainSlider, true);
    
    
    // configuring gain slider and adding it to the main window
    addAndMakeVisible (mixSlider);
    mixSlider.setRange (0.0, 1.0);
    mixSlider.setValue(0.5);
    mixSlider.addListener (this);
    mixSlider.setLookAndFeel(&otherLookAndFeel);
    
    // configuring mix label and adding it to the main window
    addAndMakeVisible(mixLabel);
    mixLabel.setText ("Mix", dontSendNotification);
    mixLabel.attachToComponent (&mixSlider, true);
    
    
    // configuring on/off button and adding it to the main window
    addAndMakeVisible(fluteOnButton);
    fluteOnButton.addListener(this);
    fluteOnButton.setLookAndFeel(&otherLookAndFeel);
    
    // configuring flute label and adding it to the main window
    addAndMakeVisible(fluteOnLabel);
    fluteOnLabel.setText ("Flute", dontSendNotification);
    fluteOnLabel.attachToComponent (&fluteOnButton, true);
    
    // configuring on/off button and adding it to the main window
    addAndMakeVisible(clarinetOnButton);
    clarinetOnButton.addListener(this);
    clarinetOnButton.setLookAndFeel(&otherLookAndFeel);
    
    // configuring clarinet label and adding it to the main window
    addAndMakeVisible(clarinetOnLabel);
    clarinetOnLabel.setText ("Clarinet", dontSendNotification);
    clarinetOnLabel.attachToComponent (&clarinetOnButton, true);



    // configuring pressure slider and adding it to the main window
    addAndMakeVisible (pressureSlider);
    pressureSlider.setRange (0, 1.0);
    pressureSlider.setValue(0.5);
    pressureSlider.addListener(this);
    pressureSlider.setLookAndFeel(&otherLookAndFeel);

    // configuring pressure label and adding it to the main window
    addAndMakeVisible(pressureLabel);
    pressureLabel.setText ("Pressure", dontSendNotification);
    pressureLabel.attachToComponent (&pressureSlider, true);


    // configuring breath slider and adding it to the main window
    addAndMakeVisible (breathSlider);
    breathSlider.setRange (0, 1.0);
    breathSlider.setValue(0.5);
    breathSlider.addListener(this);
    breathSlider.setLookAndFeel(&otherLookAndFeel);

    // configuring breath label and adding it to the main window
    addAndMakeVisible(breathLabel);
    breathLabel.setText ("Breath", dontSendNotification);
    breathLabel.attachToComponent (&breathSlider, true);

    
    // configuring third slider and adding it to the main window
    addAndMakeVisible (thirdSlider);
    thirdSlider.setRange (0, 1.0);
    thirdSlider.setValue(0.5);
    thirdSlider.addListener(this);
    thirdSlider.setLookAndFeel(&otherLookAndFeel);
    
    // configuring pressure label and adding it to the main window
    addAndMakeVisible(thirdLabel);
    thirdLabel.setText ("Third", dontSendNotification);
    thirdLabel.attachToComponent (&thirdSlider, true);

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
    int heightIncrement = 30;
    int heightOfNextElement = 10;
    gainSlider.setBounds (sliderLeft, heightOfNextElement, getWidth() - sliderLeft - 20, 20);
    heightOfNextElement += heightIncrement;
    mixSlider.setBounds (sliderLeft, heightOfNextElement, getWidth() - sliderLeft - 20, 20);
    heightOfNextElement += heightIncrement;
    fluteOnButton.setBounds (sliderLeft, heightOfNextElement, 40, 20);
    clarinetOnButton.setBounds (sliderLeft + 200, heightOfNextElement, 40, 20);
    heightOfNextElement += heightIncrement;
    
    pressureSlider.setBounds (sliderLeft, heightOfNextElement, getWidth() - sliderLeft - 20, 20);
    heightOfNextElement += heightIncrement;
    breathSlider.setBounds (sliderLeft, heightOfNextElement, getWidth() - sliderLeft - 20, 20);
    heightOfNextElement += heightIncrement;
    thirdSlider.setBounds (sliderLeft, heightOfNextElement, getWidth() - sliderLeft - 20, 20);
    heightOfNextElement += heightIncrement;
    

}

void BasicAudioPlugInAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (processor.samplingRate > 0.0){
        if (slider == &thirdSlider){
            //processor.sine.setFrequency(gainSlider.getValue());
        }
        else if (slider == &mixSlider){
            processor.setMix(mixSlider.getValue());
        }
    }
}

void BasicAudioPlugInAudioProcessorEditor::buttonClicked(Button *button){
    if(button == &fluteOnButton){
        clarinetOnButton.setToggleState(false, dontSendNotification);
        fluteOnButton.setToggleState(true, dontSendNotification);
        
        // TODO populate flute stuff
        
    }
    else if (button == &clarinetOnButton) {
        fluteOnButton.setToggleState(false, dontSendNotification);
        clarinetOnButton.setToggleState(true, dontSendNotification);
        
        // TODO Populate clarinet stuff
        
    }
}

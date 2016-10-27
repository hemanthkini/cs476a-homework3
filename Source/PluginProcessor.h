// CS476A Homework 3
// Author: Hemanth Kini
// Description: Audio Plugin Processor header file

// Modified from BasicAudioPlugin and MIDIPolySynth Starter Code:
// Original Heading follows below:

// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple JUCE sine wave synthesizer plug-in

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Sine.h"


//==============================================================================
/**
*/
class BasicAudioPlugInAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    BasicAudioPlugInAudioProcessor();
    ~BasicAudioPlugInAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    // GUI callbacks to synthesizer
    void setGain (float x);
    void setMix (float x);
    void setClarinetPressure (float x);
    void setFlutePressure (float x);
    void setClarinetBreath (float x);
    void setFluteBreath (float x);
    void setClarinetThird (float x);
    void setFluteThird (float x);
    
    float getClarinetPressure ();
    float getFlutePressure ();
    float getClarinetBreath ();
    float getFluteBreath ();
    float getClarinetThird ();
    float getFluteThird ();
    
    
    
    //Sine sine;
    
    float onOff, gain;
    int samplingRate;
    
private:
    float** audioBuffer;
    int nChans;
    Synthesiser synth;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicAudioPlugInAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED

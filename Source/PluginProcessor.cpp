// CS476A Homework 3
// Author: Hemanth Kini
// Description: Audio Plugin Processor C++ file

// Modified from BasicAudioPlugin and MIDIPolySynth Starter Code:
// Original Heading follows below:

// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple JUCE sine wave synthesizer plug-in

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Breath.h"



// Not really using this here, but we need it for things to work
struct FMSound : public SynthesiserSound
{
    FMSound() {}
    
    bool appliesToNote (int /*midiNoteNumber*/) override        { return true; }
    bool appliesToChannel (int /*midiChannel*/) override        { return true; }
};


// The FM synth voice. The FM synth is hardcoded here but ideally it should be in its own class
// to have a clear hierarchy (Sine -> FMSynth -> FMVoice)
struct FMVoice : public SynthesiserVoice
{
    FMVoice():
    carrierFrequency(440.0),
    level(0.5),
    envelope(0.0),
    onOff (false),
    tailOff(false)
    {
        carrier.setSamplingRate(getSampleRate());
        Logger::outputDebugString("Successfully constructed a voice!\n");
        breath.init(getSampleRate()); // initializing the Faust module
        breath.buildUserInterface(&breathControl); // linking the Faust module to the controler
        
        // Print the list of parameters address of "breath"
        // To get the current (default) value of these parameters, breathControl.getParamValue("paramPath") can be used
        for (int i = 0; i<breathControl.getParamsCount(); i++) {
            Logger::outputDebugString(breathControl.getParamAdress(i));
            Logger::outputDebugString("\n");
        }
    };
    
    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast<FMSound*> (sound) != nullptr;
    }
    
    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    {
        Logger::outputDebugString("Got a note start event.\n");
        // converting MIDI note number into freq
        carrierFrequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        
        /*
        // we don't want an ugly sweep when the note begins...
        smooth[0].setSmooth(0);
        smooth[0].tick(carrierFrequency);
        
        // standard smoothing...
        for(int i=0; i<2; i++){
            smooth[i].setSmooth(0.999);
        } */
        
        //level = velocity;
        level = pow(velocity,2); // if we want linear dynamic
        Logger::outputDebugString("Level is: ");
        Logger::outputDebugString(std::to_string(level));
        Logger::outputDebugString("\n");
        
        // tells the note to begin!
        onOff = true;
        
        // These parameters could be controlled with UI elements and could
        // be assigned to specific MIDI controllers. If you do so,
        // don't forget to smooth them!
        index = 150;
    }
    
    void stopNote (float /*velocity*/, bool allowTailOff) override
    {
        onOff = false; // end the note
        level = 0; // ramp envelope to 0 if tail off is allowed
        
        tailOff = allowTailOff;
    }
    
    void pitchWheelMoved (int /*newValue*/) override
    {
        // Pitch wheel is an important standard MIDI feature that should be implemented
    }
    
    void controllerMoved (int /*controllerNumber*/, int /*newValue*/) override
    {
        // Thats where you would change the value of the modulator index and frequency
        // if you wanted to control them with MIDI controllers
    }
    
    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
        // only compute block if note is on!
        if(onOff){
            while (--numSamples >= 0){
                carrier.setFrequency(carrierFrequency);
                const float currentSample = (float) carrier.tick() * level;
                for (int i = outputBuffer.getNumChannels(); --i >= 0;){
                    outputBuffer.addSample (i, startSample, currentSample);
                }
                ++startSample;
                
                // if tail off is disabled, we end the note right away, otherwise, we wait for envelope
                // to reach a safe value
                if(!onOff && (envelope < 0.001 || !tailOff)){
                    envelope = 0;
                    clearCurrentNote();
                }
            }
        }
    }
    
private:
    Sine carrier;
    Breath breath;
    MapUI breathControl;
    double carrierFrequency, index, level, envelope;
    bool onOff, tailOff;
};



//==============================================================================
BasicAudioPlugInAudioProcessor::BasicAudioPlugInAudioProcessor() : onOff (0.0), gain (0.0), samplingRate(0.0)
{
    nChans = getTotalNumOutputChannels();
    audioBuffer = new float*[nChans];
    
    // Add some voices to our synth, to play the sounds..
    int nVoices = 4;
    for (int i = 0; i < nVoices; i++)
    {
        synth.addVoice (new FMVoice());
    }
    
    synth.clearSounds();
    synth.addSound (new FMSound());
}

BasicAudioPlugInAudioProcessor::~BasicAudioPlugInAudioProcessor()
{
    delete [] audioBuffer;
}

//==============================================================================
const String BasicAudioPlugInAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BasicAudioPlugInAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BasicAudioPlugInAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double BasicAudioPlugInAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BasicAudioPlugInAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BasicAudioPlugInAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BasicAudioPlugInAudioProcessor::setCurrentProgram (int index)
{
}

const String BasicAudioPlugInAudioProcessor::getProgramName (int index)
{
    return String();
}

void BasicAudioPlugInAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BasicAudioPlugInAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    samplingRate = sampleRate;
    //sine.setSamplingRate(sampleRate);
    //sine.setFrequency(1000); // default value for frequency
    synth.setCurrentPlaybackSampleRate (sampleRate);
}

void BasicAudioPlugInAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BasicAudioPlugInAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

void BasicAudioPlugInAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    /* for (int channel = 0; channel < nChans; ++channel)
    {
        audioBuffer[channel] = buffer.getWritePointer (channel);
    }
    // computing one block
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        // configuring frequency slider and adding it to the main window
        audioBuffer[0][sample] = sine.tick()*onOff*gain;
        for (int channel = 1; channel < nChans; ++channel)
        {
            audioBuffer[channel][sample] = audioBuffer[0][sample];
        }
    } */
    synth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
    
}

//==============================================================================
bool BasicAudioPlugInAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BasicAudioPlugInAudioProcessor::createEditor()
{
    return new BasicAudioPlugInAudioProcessorEditor (*this);
}

//==============================================================================
void BasicAudioPlugInAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BasicAudioPlugInAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BasicAudioPlugInAudioProcessor();
}

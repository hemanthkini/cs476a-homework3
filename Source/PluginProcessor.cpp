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
    FMVoice(int x):
    carrierFrequency(440.0),
    level(0.5),
    envelope(0.0),
    onOff (false),
    tailOff(false)
    {
        Logger::outputDebugString("Successfully constructed a voice!\n");
        breath.init(getSampleRate()); // initializing the Faust module
        breath.buildUserInterface(&breathControl); // linking the Faust module to the controler
        
        // Print the list of parameters address of "breath"
        // To get the current (default) value of these parameters, breathControl.getParamValue("paramPath") can be used
        for (int i = 0; i<breathControl.getParamsCount(); i++) {
            Logger::outputDebugString(breathControl.getParamAdress(i));
            Logger::outputDebugString("\n");
        }
        
        // Create audio buffer
        audioBuffer = new float*[2];
        voiceIndex = x;
    };
    
    ~FMVoice() {
        delete[] audioBuffer;
    }
    
    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast<FMSound*> (sound) != nullptr;
    }
    
    // Create note start.
    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    {
        // converting MIDI note number into freq
        carrierFrequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        
        // Set frequency of notes.
        breathControl.setParamValue("/0x00/SFlute/Frequency", carrierFrequency);
        breathControl.setParamValue("/0x00/SClarinet/CLARINET/Instrument/Frequency", carrierFrequency);
        
        
        // These parameters could be controlled with UI elements and could
        // be assigned to specific MIDI controllers. If you do so,
        // don't forget to smooth them!
        index = 150;
        
        // Start notes.
        breathControl.setParamValue("/0x00/SClarinet/CLARINET/ON/OFF", 1.0);
        
        breathControl.setParamValue("/0x00/SFlute/ON/OFF_(ASR_Envelope)", 1.0);

    }
    
    // Create note stop.
    void stopNote (float /*velocity*/, bool allowTailOff) override
    {
        breathControl.setParamValue("/0x00/SClarinet/CLARINET/ON/OFF", 0.0);
        
        breathControl.setParamValue("/0x00/SFlute/ON/OFF_(ASR_Envelope)", 0.0);
        
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
    
    // Rendering audio.
    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
        // Always render next audio block - or else we clip. (Smoothing is built into Faust)
        audioBuffer[0] = outputBuffer.getWritePointer(0, startSample);
            
        breath.compute(numSamples, NULL, audioBuffer); // computing one block with Faust
    }
    
    // Getters and setters for the synth parameters.
    void setGain(float level) {
        breathControl.setParamValue("/0x00/Gain", level);
    }
    
    void setMix (float level) {
        breathControl.setParamValue("/0x00/flute_=_0,_clarinet_=_1", level);
    }
    
    void setFluteBreath(float level) {
        breathControl.setParamValue("/0x00/SFlute/Breath_Noise", level);
    }
    
    float getFluteBreath() {
        return breathControl.getParamValue("/0x00/SFlute/Breath_Noise");
    }
    
    void setFlutePressure(float level) {
        breathControl.setParamValue("/0x00/SFlute/Pressure", level);
    }
    
    float getFlutePressure() {
        return breathControl.getParamValue("/0x00/SFlute/Pressure");
    }
    
    void setFluteThird(float level) {
        breathControl.setParamValue("/0x00/SFlute/Vibrato_Freq_(Vibrato_Envelope)", level);
    }
    
    float getFluteThird() {
        return breathControl.getParamValue("/0x00/SFlute/Vibrato_Freq_(Vibrato_Envelope)");
    }
    
    void setClarinetBreath(float level) {
        breathControl.setParamValue("/0x00/SClarinet/CLARINET/Parameters/Breath_Noise", level);
    }
    
    float getClarinetBreath() {
        return breathControl.getParamValue("/0x00/SClarinet/CLARINET/Parameters/Breath_Noise");
    }
    
    void setClarinetPressure(float level) {
        breathControl.setParamValue("/0x00/SClarinet/CLARINET/Parameters/Pressure", level);
    }
    
    float getClarinetPressure() {
        return breathControl.getParamValue("/0x00/SClarinet/CLARINET/Parameters/Pressure");
    }
    
    void setClarinetThird(float level) {
        breathControl.setParamValue("/0x00/SClarinet/CLARINET/Parameters/Instrument_Stiffness", level);
    }
    
    float getClarinetThird() {
        return breathControl.getParamValue("/0x00/SClarinet/CLARINET/Parameters/Instrument_Stiffness");
    }
    
    

private:
    Breath breath;
    MapUI breathControl;
    double carrierFrequency, index, level, envelope;
    int voiceIndex;
    bool onOff, tailOff;
    float** audioBuffer; // multichannel audio buffer used both for input and output
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
        synth.addVoice (new FMVoice(i));
    }
    
    // Doesn't do anything here.
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


// GUI Callback methods - handle update from GUI, pass it along to each voice

void BasicAudioPlugInAudioProcessor::setGain (float x) {
    int numVoices = synth.getNumVoices();
    for (int i = 0; i < numVoices; i++) {
        ((FMVoice *)synth.getVoice(i))->setGain(x);
    }
}



void BasicAudioPlugInAudioProcessor::setMix (float x) {
    int numVoices = synth.getNumVoices();
    for (int i = 0; i < numVoices; i++) {
        ((FMVoice *)synth.getVoice(i))->setMix(x);
    }
}

void BasicAudioPlugInAudioProcessor::setClarinetPressure (float x){
    int numVoices = synth.getNumVoices();
    for (int i = 0; i < numVoices; i++) {
        ((FMVoice *)synth.getVoice(i))->setClarinetPressure(x);
    }
}

float BasicAudioPlugInAudioProcessor::getClarinetPressure (){
    return ((FMVoice *)synth.getVoice(0))->getClarinetPressure();
}

void BasicAudioPlugInAudioProcessor::setFlutePressure (float x){
    int numVoices = synth.getNumVoices();
    for (int i = 0; i < numVoices; i++) {
        ((FMVoice *)synth.getVoice(i))->setFlutePressure(x);
    }
}

float BasicAudioPlugInAudioProcessor::getFlutePressure (){
    return ((FMVoice *)synth.getVoice(0))->getFlutePressure();
}

void BasicAudioPlugInAudioProcessor::setClarinetBreath (float x){
    int numVoices = synth.getNumVoices();
    for (int i = 0; i < numVoices; i++) {
        ((FMVoice *)synth.getVoice(i))->setClarinetBreath(x);
    }
}

float BasicAudioPlugInAudioProcessor::getClarinetBreath (){
    return ((FMVoice *)synth.getVoice(0))->getClarinetBreath();
}

void BasicAudioPlugInAudioProcessor::setFluteBreath (float x){
    int numVoices = synth.getNumVoices();
    for (int i = 0; i < numVoices; i++) {
        ((FMVoice *)synth.getVoice(i))->setFluteBreath(x);
    }
}

float BasicAudioPlugInAudioProcessor::getFluteBreath (){
    return ((FMVoice *)synth.getVoice(0))->getFluteBreath();
}


void BasicAudioPlugInAudioProcessor::setClarinetThird (float x){
    int numVoices = synth.getNumVoices();
    for (int i = 0; i < numVoices; i++) {
        ((FMVoice *)synth.getVoice(i))->setClarinetThird(x);
    }
}

float BasicAudioPlugInAudioProcessor::getClarinetThird (){
    return ((FMVoice *)synth.getVoice(0))->getClarinetThird();
}


void BasicAudioPlugInAudioProcessor::setFluteThird (float x){
    int numVoices = synth.getNumVoices();
    for (int i = 0; i < numVoices; i++) {
        ((FMVoice *)synth.getVoice(i))->setFluteThird(x);
    }
}

float BasicAudioPlugInAudioProcessor::getFluteThird (){
    return ((FMVoice *)synth.getVoice(0))->getFluteThird();
}




import("stdfaust.lib");
flute = vgroup("SFlute",environment{declare name "Flute";
declare description "Nonlinear WaveGuide Flute";
declare author "Romain Michon (rmichon@ccrma.stanford.edu)";
declare copyright "Romain Michon";
declare version "1.0";
declare licence "STK-4.3"; // Synthesis Tool Kit 4.3 (MIT style license);
declare description "A simple flute based on Smith algorythm: https://ccrma.stanford.edu/~jos/pasp/Flutes_Recorders_Pipe_Organs.html";

//Modifications GRAME July 2015

/* =========== DESCRITPION ===========

- Flute
- Turn ON flute (0=OFF, 1=ON)
- Head = High frequencies/ Silence
- Bottom = Low frequencies
- Left = No vibrato
- Right = Fast vibrato
- Front = Full sound
- Back = Breathy sound

*/

import("stdfaust.lib");
instrument = library("instrument.lib");

//==================== INSTRUMENT =======================

flute = (_ <: (flow + *(feedBack1) : embouchureDelay: poly) + *(feedBack2) : reflexionFilter)~(boreDelay) : NLFM : *(env2)*gain:_;

process = flute;

//==================== GUI SPECIFICATION ================
gate = hslider("[0]ON/OFF (ASR Envelope)",0,0,1,1);
freq = hslider("[1]Frequency[acc:1 1 -10 0 10]", 440,247,1200,1):si.smooth(0.999);
pressure = hslider("[2]Pressure[style:knob][acc:1 0 -10 0 10]", 0.96, 0.2, 0.99, 0.01):si.smooth(0.999):min(0.99):max(0.2);
breathAmp = hslider("[3]Breath Noise[style:knob][acc:2 0 -10 0 10]", 0.02, 0.01, 0.2, 0.01):si.smooth(0.999):min(0.2):max(0.01);

vibratoFreq = hslider("[4]Vibrato Freq (Vibrato Envelope)[style:knob][unit:Hz][acc:0 1 -10 0 10]", 4,0.5,8,0.1);
env1Attack = 0.1;//hslider("h:Parameters/Press_Env_Attack[unit:s][style:knob][acc:1 0 -10 0 10][tooltip:Pressure envelope attack duration]",0.05,0.05,0.2,0.01);



//-------------------- Non-Variable Parameters -----------

gain = 1;
typeModulation = 0;
nonLinearity = 0;
frequencyMod = 220;
nonLinAttack = 0.1;
vibratoGain = 0.05;
vibratoBegin = 0.1;
vibratoAttack = 0.5;
vibratoRelease = 0.2;
pressureEnvelope = 0;
env1Decay = 0.2;
env2Attack = 0.1;
env2Release = 0.1;
env1Release = 0.5;


//==================== SIGNAL PROCESSING ================

//----------------------- Nonlinear filter ----------------------------
//nonlinearities are created by the nonlinear passive allpass ladder filter declared in filter.lib

//nonlinear filter order
nlfOrder = 6;

//attack - sustain - release envelope for nonlinearity (declared in instrument.lib)
envelopeMod = en.asr(nonLinAttack,100,0.1,gate);

//nonLinearModultor is declared in instrument.lib, it adapts allpassnn from filter.lib
//for using it with waveguide instruments
NLFM =  instrument.nonLinearModulator((nonLinearity : si.smooth(0.999)),envelopeMod,freq,
     typeModulation,(frequencyMod : si.smooth(0.999)),nlfOrder);

//----------------------- Synthesis parameters computing and functions declaration ----------------------------

//Loops feedbacks gains
feedBack1 = 0.4;
feedBack2 = 0.4;

//Delay Lines
embouchureDelayLength = (ma.SR/freq)/2-2;
boreDelayLength = ma.SR/freq-2;
embouchureDelay = de.fdelay(4096,embouchureDelayLength);
boreDelay = de.fdelay(4096,boreDelayLength);

//Polinomial
poly = _ <: _ - _*_*_;

//jet filter is a lowwpass filter (declared in filter.lib)
reflexionFilter = fi.lowpass(1,2000);


//----------------------- Algorithm implementation ----------------------------

//Pressure envelope
env1 = en.adsr(env1Attack,env1Decay,90,env1Release,(gate | pressureEnvelope))*pressure*1.1;

//Global envelope
env2 = en.asr(env2Attack,100,env2Release,gate)*0.5;

//Vibrato Envelope
vibratoEnvelope = instrument.envVibrato(vibratoBegin,vibratoAttack,100,vibratoRelease,gate)*vibratoGain;

vibrato = os.osc(vibratoFreq)*vibratoEnvelope;

breath = no.noise*env1;

flow = env1 + breath*breathAmp + vibrato;
}.process);

flute2 = vgroup("SClarinet",environment{declare name "Clarinet";
declare description "Nonlinear WaveGuide Clarinet";
declare author "Romain Michon";
declare copyright "Romain Michon (rmichon@ccrma.stanford.edu)";
declare version "1.0";
declare licence "STK-4.3"; // Synthesis Tool Kit 4.3 (MIT style license);
declare description "A simple clarinet physical model, as discussed by Smith (1986), McIntyre, Schumacher, Woodhouse (1983), and others.";
declare reference "https://ccrma.stanford.edu/~jos/pasp/Woodwinds.html";

//Modification Grame July 2015

import("stdfaust.lib");
instrument = library("instrument.lib");

/* =============== DESCRIPTION ================= :

- Clarinet responding to vigorous gestures
- Turn ON clarinet (0=OFF, 1=ON)
- Head = High frequencies/Silence when hold still
- Tilt = very soft sound
- Bottom = Low frequencies
- Right = Breathy clarinet
- Fishing rod (vigorous mouvements) :
 ==> Downward = to reach lower frequencies
 ==> Upward = To 'through' the sound in the air = vanishes, comes back when Tilt
- Rocking = from full sound to breathy sound
- Shaking in right position = no.noise impulses

*/

//==================== INSTRUMENT =======================

process = vgroup("CLARINET",
	//Commuted Loss Filtering
	(_,(breathPressure <: _,_) : (filter*-0.95 - _ <: 
	
	//Non-Linear Scattering
	*(reedTable)) + _) ~ 
	
	//Delay with Feedback
	(delayLine):// : NLFM) : 
	
	//scaling and stereo
	*(gain)*1.5); 
	
//==================== GUI SPECIFICATION ================


freq = hslider("h:[2]Instrument/Frequency[unit:Hz][tooltip:Tone frequency][acc:1 1 -14 0 10]", 440,110,1300,0.01):si.smooth(0.999);
gain = 1;
gate = hslider("[1]ON/OFF",0,0,1,1);

reedStiffness = hslider("h:[3]Parameters/Instrument Stiffness[style:knob][acc:0 1 -12 0 12]", 0.25,0.01,1,0.01);
noiseGain = hslider("h:[3]Parameters/Breath Noise[style:knob][acc:0 1 -10 0 12]", 0.02,0,0.12,0.01);
pressure = hslider("h:[3]Parameters/ Pressure[style:knob][acc:1 0 -10 0 10]", 0.8,0.25,1,0.01);

vibratoFreq = 5;
vibratoGain = 0.1;
vibratoAttack = 0.5;
vibratoRelease = 0.01;

envelopeAttack = 0.1;
envelopeDecay = 0.05;
envelopeRelease = 0.1;

//==================== SIGNAL PROCESSING ======================


//----------------------- Synthesis PARAMETERS computing and functions declaration ----------------------------

//reed table PARAMETERS
reedTableOffset = 0.7;
reedTableSlope = -0.44 + (0.26*reedStiffness);

//the reed function is declared in INSTRUMENT.lib
reedTable = instrument.reed(reedTableOffset,reedTableSlope);

//delay line with a length adapted in function of the order of nonlinear filter
delayLength = ma.SR/freq*0.5 - 1.5;// - (nlfOrder*nonLinearity)*(typeModulation < 2);
delayLine = de.fdelay(4096,delayLength);

//one zero filter used as a allpass: pole is set to -1
filter = instrument.oneZero0(0.5,0.5);

//stereoizer is declared in INSTRUMENT.lib and implement a stereo spacialisation in function of 
//the frequency period in number of samples 
//stereo = stereoizerCla(ma.SR/freq);

//----------------------- Algorithm implementation ----------------------------

//Breath pressure + vibrato + breath no.noise + envelope (Attack / Decay / Sustain / Release)
envelope = en.adsr(envelopeAttack,envelopeDecay,100,envelopeRelease,gate)*pressure*0.9;

vibrato = os.osc(vibratoFreq)*vibratoGain*
	instrument.envVibrato(0.1*2*vibratoAttack,0.9*2*vibratoAttack,100,vibratoRelease,gate);
breath = envelope + envelope*no.noise*noiseGain;
breathPressure = breath + breath*vibrato;





}.process);

inbetween = hslider("flute = 0, clarinet = 1", 0, 0, 1, 0.01) : si.smoo;
gain = hslider("Gain", 0.5, 0, 1, 0.01) : si.smoo;
process = (flute * (inbetween) + flute2 * (1 - inbetween)) * gain;

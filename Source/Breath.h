//----------------------------------------------------------
// name: "Flute", "Clarinet"
// author: "Romain Michon (rmichon@ccrma.stanford.edu)", "Romain Michon"
// copyright: "Romain Michon (rmichon@ccrma.stanford.edu)", "Romain Michon"
// version: "1.0"
//
// Code generated with Faust 0.9.90 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif
// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple Faust architecture file to easily integrate a Faust DSP module
// in a JUCE project

// needed by any Faust arch file
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <string.h>
#include <stdlib.h>

/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __meta__
#define __meta__

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
    virtual ~Meta() {};
};

#endif

using std::max;
using std::min;

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

inline int lsr(int x, int n)	{ return int(((unsigned int)x) >> n); }

inline int int2pow2(int x)		{ int r = 0; while ((1<<r) < x) r++; return r; }

inline long lopt(char* argv[], const char* name, long def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

inline bool isopt(char* argv[], const char* name)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
	return false;
}

inline const char* lopts(char* argv[], const char* name, const char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}

#endif


// allows to control a Faust DSP module in a simple manner by using parameter's path
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <vector>
#include <map>
#include <string>

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/
 
#ifndef FAUST_UI_H
#define FAUST_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust User Interface
 * This abstract class contains only the method that the faust compiler can
 * generate to describe a DSP interface.
 ******************************************************************************/

class UI
{

    public:

        UI() {}

        virtual ~UI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
};

//----------------------------------------------------------------
//  Generic decorator
//----------------------------------------------------------------

class DecoratorUI : public UI
{
    protected:
    
        UI* fUI;

    public:
    
        DecoratorUI(UI* ui = 0):fUI(ui)
        {}

        virtual ~DecoratorUI() { delete fUI; }

        // -- widget's layouts
        virtual void openTabBox(const char* label)          { fUI->openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fUI->openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fUI->openVerticalBox(label); }
        virtual void closeBox()                             { fUI->closeBox(); }

        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)         { fUI->addButton(label, zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)    { fUI->addCheckButton(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
            { fUI->addVerticalSlider(label, zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 	
            { fUI->addHorizontalSlider(label, zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 			
            { fUI->addNumEntry(label, zone, init, min, max, step); }

        // -- passive widgets	
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
            { fUI->addHorizontalBargraph(label, zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            { fUI->addVerticalBargraph(label, zone, min, max); }

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) { fUI->declare(zone, key, val); }

};

#endif
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
};

#endif  // FAUST_PATHBUILDER_H

/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete hierarchical path and zones for each UI items.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
    public:
        
        MapUI() {};
        virtual ~MapUI() {};
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openHorizontalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openVerticalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void closeBox()
        {
            fControlsLevel.pop_back();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // set/get
        void setParamValue(const std::string& path, float value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            }
        }
        
        float getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                return 0.;
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return fPathZoneMap.size(); }
        
        std::string getParamAdress(int index) 
        { 
            std::map<std::string, FAUSTFLOAT*>::iterator it = fPathZoneMap.begin();
            while (index-- > 0 && it++ != fPathZoneMap.end()) {}
            return (*it).first;
        }
};

#endif // FAUST_MAPUI_H

// needed by any Faust arch file
/************************************************************************
    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

 ************************************************************************
 ************************************************************************/
 
/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

#ifndef __dsp__
#define __dsp__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;
struct Meta;

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the UI* parameter with instance specific calls
         * to 'addBtton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the UI* user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /** Global init, calls the following methods :
         * - static class 'classInit' : static table initialisation
         * - 'instanceInit' : constants and instance table initialisation
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void init(int samplingRate) = 0;
    
        /** Init instance state
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void instanceInit(int samplingRate) = 0;
    
        /** Init instance constant state
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void instanceConstants(int samplingRate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (delay lines...) */
        virtual void instanceClear() = 0;
    
        /**  
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value metadata).
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with sucessive in/out audio buffers.
         *
         * @param count - the nomber of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation : alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the nomber of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         *
         */
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = 0):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int samplingRate) { fDSP->init(samplingRate); }
        virtual void instanceInit(int samplingRate) { fDSP->instanceInit(samplingRate); }
        virtual void instanceConstants(int samplingRate) { fDSP->instanceConstants(samplingRate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { return fDSP->metadata(m); }
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
       
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif

// tags used by the Faust compiler to paste the generated c++ code
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  


#ifndef FAUSTCLASS 
#define FAUSTCLASS Breath
#endif

class Breath : public dsp {
  private:
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT 	fslider1;
	float 	fConst0;
	float 	fConst1;
	int 	iVec0[2];
	float 	fRec1[2];
	float 	fConst2;
	float 	fRec3[2];
	float 	fConst3;
	float 	fConst4;
	float 	fRec2[2];
	FAUSTFLOAT 	fslider2;
	int 	iRec4[2];
	float 	fConst5;
	float 	fConst6;
	float 	fConst7;
	float 	fRec5[2];
	float 	fConst8;
	float 	fRec6[2];
	int 	iRec7[2];
	int 	iRec8[2];
	float 	fConst9;
	float 	fConst10;
	float 	fRec9[2];
	float 	fConst11;
	FAUSTFLOAT 	fslider3;
	float 	fRec11[2];
	float 	fRec10[2];
	FAUSTFLOAT 	fslider4;
	int 	IOTA;
	float 	fRec0[8192];
	FAUSTFLOAT 	fslider5;
	float 	fRec12[2];
	FAUSTFLOAT 	fslider6;
	float 	fRec13[2];
	float 	fRec15[2];
	float 	fRec14[2];
	float 	fConst12;
	float 	fConst13;
	float 	fConst14;
	float 	fConst15;
	float 	fRec18[2];
	float 	fConst16;
	float 	fRec20[2];
	float 	fConst17;
	float 	fRec19[2];
	float 	fConst18;
	FAUSTFLOAT 	fslider7;
	float 	fRec21[2];
	FAUSTFLOAT 	fslider8;
	float 	fRec22[2];
	float 	fConst19;
	FAUSTFLOAT 	fslider9;
	float 	fRec23[2];
	float 	fRec24[2];
	int 	iRec25[2];
	int 	iRec26[2];
	float 	fConst20;
	float 	fRec27[2];
	FAUSTFLOAT 	fslider10;
	float 	fRec28[2];
	float 	fVec1[4096];
	float 	fVec2[2];
	float 	fRec17[2];
	float 	fRec16[8192];
	float 	fRec29[2];
	float 	fRec35[2];
	float 	fRec34[2];
	float 	fRec33[2];
	float 	fRec32[2];
	float 	fRec31[2];
	float 	fRec30[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("miscoscillator.lib/name", "Faust Oscillator Library");
		m->declare("miscoscillator.lib/version", "0.0");
		m->declare("envelope.lib/name", "Faust Envelope Library");
		m->declare("envelope.lib/version", "0.0");
		m->declare("envelope.lib/author", "GRAME");
		m->declare("envelope.lib/copyright", "GRAME");
		m->declare("envelope.lib/license", "LGPL with exception");
		m->declare("noise.lib/name", "Faust Noise Generator Library");
		m->declare("noise.lib/version", "0.0");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/version", "2.0");
		m->declare("delay.lib/name", "Faust Delay Library");
		m->declare("delay.lib/version", "0.0");
		m->declare("name", "Flute");
		m->declare("description", "Nonlinear WaveGuide Flute");
		m->declare("author", "Romain Michon (rmichon@ccrma.stanford.edu)");
		m->declare("contributor", "Romain Michon");
		m->declare("copyright", "Romain Michon (rmichon@ccrma.stanford.edu)");
		m->declare("version", "1.0");
		m->declare("licence", "STK-4.3");
		m->declare("reference", "https://ccrma.stanford.edu/~jos/pasp/Woodwinds.html");
		m->declare("basic.lib/name", "Faust Basic Element Library");
		m->declare("basic.lib/version", "0.0");
		m->declare("math.lib/name", "Faust Math Library");
		m->declare("math.lib/version", "2.0");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("signal.lib/name", "Faust Signal Routing Library");
		m->declare("signal.lib/version", "0.0");
		m->declare("instrument.lib/name", "Faust-STK Tools Library");
		m->declare("instrument.lib/author", "Romain Michon (rmichon@ccrma.stanford.edu)");
		m->declare("instrument.lib/copyright", "Romain Michon");
		m->declare("instrument.lib/version", "1.0");
		m->declare("instrument.lib/licence", "STK-4.3");
	}

	virtual int getNumInputs() { return 0; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(1.92e+05f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (0.1f * fConst0);
		fConst2 = (0.15f * fConst0);
		fConst3 = (1e+01f / fConst0);
		fConst4 = (2e+01f / fConst0);
		fConst5 = (31.415926f / fConst0);
		fConst6 = sinf(fConst5);
		fConst7 = cosf(fConst5);
		fConst8 = (0 - fConst6);
		fConst9 = (1.1111112f / fConst0);
		fConst10 = (1 - (1.0f / powf(1e+05f,(1e+02f / fConst0))));
		fConst11 = (0.5f * fConst0);
		fConst12 = (1.0f / tanf((6283.1855f / fConst0)));
		fConst13 = (1 + fConst12);
		fConst14 = (0 - ((1 - fConst12) / fConst13));
		fConst15 = (1.0f / fConst13);
		fConst16 = (0.3f * fConst0);
		fConst17 = (5.0f / fConst0);
		fConst18 = (2.0f / fConst0);
		fConst19 = (6.2831855f / fConst0);
		fConst20 = (1 - (1.0f / powf(1e+05f,(5.0f / fConst0))));
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.8f;
		fslider1 = 0.0f;
		fslider2 = 0.02f;
		fslider3 = 4.4e+02f;
		fslider4 = 0.25f;
		fslider5 = 0.0f;
		fslider6 = 0.0f;
		fslider7 = 0.96f;
		fslider8 = 0.02f;
		fslider9 = 4.0f;
		fslider10 = 4.4e+02f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) iVec0[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) iRec4[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) iRec7[i] = 0;
		for (int i=0; i<2; i++) iRec8[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec10[i] = 0;
		IOTA = 0;
		for (int i=0; i<8192; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec22[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) iRec25[i] = 0;
		for (int i=0; i<2; i++) iRec26[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<4096; i++) fVec1[i] = 0;
		for (int i=0; i<2; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<8192; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<2; i++) fRec34[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<2; i++) fRec30[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	virtual Breath* clone() {
		return new Breath();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Breath");
		ui_interface->openVerticalBox("SClarinet");
		ui_interface->openVerticalBox("CLARINET");
		ui_interface->declare(&fslider1, "1", "");
		ui_interface->addHorizontalSlider("ON/OFF", &fslider1, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Instrument");
		ui_interface->declare(&fslider3, "acc", "1 1 -14 0 10");
		ui_interface->declare(&fslider3, "tooltip", "Tone frequency");
		ui_interface->declare(&fslider3, "unit", "Hz");
		ui_interface->addHorizontalSlider("Frequency", &fslider3, 4.4e+02f, 1.1e+02f, 1.3e+03f, 0.01f);
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("Parameters");
		ui_interface->declare(&fslider0, "acc", "1 0 -10 0 10");
		ui_interface->declare(&fslider0, "style", "knob");
		ui_interface->addHorizontalSlider("Pressure", &fslider0, 0.8f, 0.25f, 1.0f, 0.01f);
		ui_interface->declare(&fslider2, "acc", "0 1 -10 0 12");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->addHorizontalSlider("Breath Noise", &fslider2, 0.02f, 0.0f, 0.12f, 0.01f);
		ui_interface->declare(&fslider4, "acc", "0 1 -12 0 12");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->addHorizontalSlider("Instrument Stiffness", &fslider4, 0.25f, 0.01f, 1.0f, 0.01f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->openVerticalBox("SFlute");
		ui_interface->declare(&fslider6, "0", "");
		ui_interface->addHorizontalSlider("ON/OFF (ASR Envelope)", &fslider6, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->declare(&fslider10, "1", "");
		ui_interface->declare(&fslider10, "acc", "1 1 -10 0 10");
		ui_interface->addHorizontalSlider("Frequency", &fslider10, 4.4e+02f, 247.0f, 1.2e+03f, 1.0f);
		ui_interface->declare(&fslider7, "2", "");
		ui_interface->declare(&fslider7, "acc", "1 0 -10 0 10");
		ui_interface->declare(&fslider7, "style", "knob");
		ui_interface->addHorizontalSlider("Pressure", &fslider7, 0.96f, 0.2f, 0.99f, 0.01f);
		ui_interface->declare(&fslider8, "3", "");
		ui_interface->declare(&fslider8, "acc", "2 0 -10 0 10");
		ui_interface->declare(&fslider8, "style", "knob");
		ui_interface->addHorizontalSlider("Breath Noise", &fslider8, 0.02f, 0.01f, 0.2f, 0.01f);
		ui_interface->declare(&fslider9, "4", "");
		ui_interface->declare(&fslider9, "acc", "0 1 -10 0 10");
		ui_interface->declare(&fslider9, "style", "knob");
		ui_interface->declare(&fslider9, "unit", "Hz");
		ui_interface->addHorizontalSlider("Vibrato Freq (Vibrato Envelope)", &fslider9, 4.0f, 0.5f, 8.0f, 0.1f);
		ui_interface->closeBox();
		ui_interface->addHorizontalSlider("flute = 0, clarinet = 1", &fslider5, 0.0f, 0.0f, 1.0f, 0.01f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = float(fslider0);
		float 	fSlow1 = float(fslider1);
		int 	iSlow2 = (fSlow1 > 0);
		int 	iSlow3 = int((iSlow2 > 0));
		int 	iSlow4 = (1 - iSlow2);
		int 	iSlow5 = faustpower<2>(iSlow2);
		int 	iSlow6 = int(((fSlow1 == 0) > 0));
		float 	fSlow7 = (fConst4 * (fSlow1 - 1));
		float 	fSlow8 = (4.1909515e-10f * float(fslider2));
		int 	iSlow9 = (fSlow1 <= 0);
		float 	fSlow10 = (0.001f * float(fslider3));
		float 	fSlow11 = ((0.26f * float(fslider4)) - 0.44f);
		float 	fSlow12 = (0.001f * float(fslider5));
		float 	fSlow13 = float(fslider6);
		int 	iSlow14 = (fSlow13 > 0);
		int 	iSlow15 = int((iSlow14 > 0));
		int 	iSlow16 = (1 - iSlow14);
		int 	iSlow17 = faustpower<2>(iSlow14);
		int 	iSlow18 = int(((fSlow13 == 0) > 0));
		float 	fSlow19 = (fConst3 * fSlow13);
		float 	fSlow20 = (0.9f * fSlow13);
		float 	fSlow21 = (fConst17 * (fSlow20 - 1));
		float 	fSlow22 = (0.001f * float(fslider7));
		float 	fSlow23 = (0.001f * float(fslider8));
		float 	fSlow24 = (fConst19 * float(fslider9));
		float 	fSlow25 = sinf(fSlow24);
		float 	fSlow26 = cosf(fSlow24);
		float 	fSlow27 = (0 - fSlow25);
		int 	iSlow28 = (fSlow13 <= 0);
		float 	fSlow29 = (0.001f * float(fslider10));
		FAUSTFLOAT* output0 = output[0];
		for (int i=0; i<count; i++) {
			iVec0[0] = 1;
			fRec1[0] = ((iSlow3)?0:min(fConst1, (1 + fRec1[1])));
			fRec3[0] = ((iSlow6)?0:min(fConst2, (1 + fRec3[1])));
			int iTemp0 = int((fRec3[0] < fConst1));
			fRec2[0] = ((iSlow4 * fRec2[1]) + (iSlow5 * ((iTemp0)?((int((fRec3[0] < 0)))?0:((iTemp0)?(fConst3 * fRec3[0]):1)):((int((fRec3[0] < fConst2)))?(1 + (fSlow7 * (fRec3[0] - fConst1))):fSlow1))));
			iRec4[0] = (12345 + (1103515245 * iRec4[1]));
			fRec5[0] = ((fConst6 * fRec6[1]) + (fConst7 * fRec5[1]));
			fRec6[0] = ((1 + ((fConst7 * fRec6[1]) + (fConst8 * fRec5[1]))) - iVec0[1]);
			iRec7[0] = (iSlow2 & (iRec7[1] | (fRec9[1] >= 1)));
			iRec8[0] = (iSlow2 * (1 + iRec8[1]));
			int iTemp1 = (iSlow9 & (fRec9[1] > 0));
			fRec9[0] = (((fConst9 * ((1 - (iRec8[1] < fConst1)) * ((((iRec7[1] == 0) & iSlow2) & (fRec9[1] < 1)) & (iRec8[1] > fConst1)))) + (fRec9[1] * (1 - (fConst10 * iTemp1)))) * ((iTemp1 == 0) | (fRec9[1] >= 1e-06f)));
			float fTemp2 = (fSlow0 * ((((int((fRec1[0] < 0)))?fRec2[0]:((int((fRec1[0] < fConst1)))?(fRec2[0] + (fConst3 * (fRec1[0] * (0 - fRec2[0])))):0)) * (0.9f + (fSlow8 * iRec4[0]))) * (1 + (0.1f * (fRec5[0] * fRec9[0])))));
			fRec11[0] = (fSlow10 + (0.999f * fRec11[1]));
			float fTemp3 = (fConst11 / fRec11[0]);
			float fTemp4 = (fTemp3 - 1.5f);
			int iTemp5 = int(fTemp4);
			float fTemp6 = floorf(fTemp4);
			fRec10[0] = (0.5f * ((fRec0[(IOTA-int((1 + int((iTemp5 & 4095)))))&8191] * ((2.5f + fTemp6) - fTemp3)) + (fRec10[1] + ((fTemp3 - (1.5f + fTemp6)) * fRec0[(IOTA-int((1 + int((int((1 + iTemp5)) & 4095)))))&8191]))));
			float fTemp7 = (0 - (fTemp2 + (0.95f * fRec10[0])));
			float fTemp8 = (0.7f + (fSlow11 * fTemp7));
			float fTemp9 = ((fTemp8 > 1) + (fTemp8 * (fTemp8 <= 1)));
			fRec0[IOTA&8191] = (fTemp2 + (fTemp7 * ((fTemp9 * (fTemp9 >= -1)) - (fTemp9 < -1))));
			fRec12[0] = (fSlow12 + (0.999f * fRec12[1]));
			fRec13[0] = ((iSlow15)?0:min(fConst1, (1 + fRec13[1])));
			fRec15[0] = ((iSlow18)?0:min(fConst1, (1 + fRec15[1])));
			fRec14[0] = ((iSlow16 * fRec14[1]) + (iSlow17 * ((int((fRec15[0] < 0)))?0:((int((fRec15[0] < fConst1)))?(fSlow19 * fRec15[0]):fSlow13))));
			float fTemp10 = ((int((fRec13[0] < 0)))?fRec14[0]:((int((fRec13[0] < fConst1)))?(fRec14[0] + (fConst3 * (fRec13[0] * (0 - fRec14[0])))):0));
			fRec18[0] = ((iSlow15)?0:min(fConst11, (1 + fRec18[1])));
			fRec20[0] = ((iSlow18)?0:min(fConst16, (1 + fRec20[1])));
			int iTemp11 = int((fRec20[0] < fConst1));
			fRec19[0] = ((iSlow16 * fRec19[1]) + (iSlow17 * ((iTemp11)?((int((fRec20[0] < 0)))?0:((iTemp11)?(fConst3 * fRec20[0]):1)):((int((fRec20[0] < fConst16)))?(1 + (fSlow21 * (fRec20[0] - fConst1))):fSlow20))));
			fRec21[0] = (fSlow22 + (0.999f * fRec21[1]));
			fRec22[0] = (fSlow23 + (0.999f * fRec22[1]));
			fRec23[0] = ((fSlow25 * fRec24[1]) + (fSlow26 * fRec23[1]));
			fRec24[0] = ((1 + ((fSlow26 * fRec24[1]) + (fSlow27 * fRec23[1]))) - iVec0[1]);
			iRec25[0] = (iSlow14 & (iRec25[1] | (fRec27[1] >= 1)));
			iRec26[0] = (iSlow14 * (1 + iRec26[1]));
			int iTemp12 = (iSlow28 & (fRec27[1] > 0));
			fRec27[0] = (((iTemp12 == 0) | (fRec27[1] >= 1e-06f)) * ((fConst18 * (((((iRec25[1] == 0) & iSlow14) & (fRec27[1] < 1)) & (iRec26[1] > fConst1)) * (1 - (iRec26[1] < fConst1)))) + (fRec27[1] * (1 - (fConst20 * iTemp12)))));
			fRec28[0] = (fSlow29 + (0.999f * fRec28[1]));
			float fTemp13 = (fConst0 / fRec28[0]);
			float fTemp14 = (fTemp13 - 2);
			int iTemp15 = int(fTemp14);
			float fTemp16 = floorf(fTemp14);
			float fTemp17 = (0.4f * ((fRec16[(IOTA-int((1 + int((iTemp15 & 4095)))))&8191] * ((3 + fTemp16) - fTemp13)) + ((fTemp13 - (2 + fTemp16)) * fRec16[(IOTA-int((1 + int((int((1 + iTemp15)) & 4095)))))&8191])));
			float fTemp18 = ((((((int((fRec18[0] < 0)))?fRec19[0]:((int((fRec18[0] < fConst11)))?(fRec19[0] + (fConst18 * (fRec18[0] * (0 - fRec19[0])))):0)) * max(0.2f, min(0.99f, fRec21[0]))) * (1.1f + (5.122274e-10f * (iRec4[0] * max(0.01f, min(0.2f, fRec22[0])))))) + (0.05f * (fRec23[0] * fRec27[0]))) + fTemp17);
			fVec1[IOTA&4095] = fTemp18;
			float fTemp19 = (fConst11 / fRec28[0]);
			float fTemp20 = (fTemp19 - 2);
			int iTemp21 = int(fTemp20);
			float fTemp22 = floorf(fTemp20);
			float fTemp23 = (fVec1[(IOTA-int((iTemp21 & 4095)))&4095] * ((3 + fTemp22) - fTemp19));
			float fTemp24 = ((fTemp19 - (2 + fTemp22)) * fVec1[(IOTA-int((int((1 + iTemp21)) & 4095)))&4095]);
			float fTemp25 = (fTemp23 + (fTemp17 + fTemp24));
			float fTemp26 = faustpower<3>((fTemp24 + fTemp23));
			fVec2[0] = (fTemp25 - fTemp26);
			fRec17[0] = ((fConst14 * fRec17[1]) + (fConst15 * ((fVec2[1] + fTemp25) - fTemp26)));
			fRec16[IOTA&8191] = fRec17[0];
			float fTemp27 = fRec16[(IOTA-0)&8191];
			fRec29[0] = (0.999f * fRec29[1]);
			float fTemp28 = (3.1415927f * ((fTemp10 * fRec29[0]) * fTemp27));
			float fTemp29 = sinf(fTemp28);
			float fTemp30 = (0 - fTemp29);
			float fTemp31 = cosf(fTemp28);
			float fTemp32 = ((fRec30[1] * fTemp30) + (fTemp27 * fTemp31));
			float fTemp33 = ((fRec31[1] * fTemp30) + (fTemp31 * fTemp32));
			float fTemp34 = ((fRec32[1] * fTemp30) + (fTemp31 * fTemp33));
			float fTemp35 = ((fRec33[1] * fTemp30) + (fTemp31 * fTemp34));
			float fTemp36 = ((fRec34[1] * fTemp30) + (fTemp31 * fTemp35));
			fRec35[0] = ((fRec35[1] * fTemp30) + (fTemp31 * fTemp36));
			fRec34[0] = ((fTemp29 * fTemp36) + (fRec35[1] * fTemp31));
			fRec33[0] = ((fTemp29 * fTemp35) + (fRec34[1] * fTemp31));
			fRec32[0] = ((fTemp29 * fTemp34) + (fRec33[1] * fTemp31));
			fRec31[0] = ((fTemp29 * fTemp33) + (fRec32[1] * fTemp31));
			fRec30[0] = ((fTemp29 * fTemp32) + (fRec31[1] * fTemp31));
			output0[i] = (FAUSTFLOAT)((1.5f * (fRec0[(IOTA-0)&8191] * (1 - fRec12[0]))) + (0.5f * ((fTemp10 * fRec12[0]) * ((fTemp27 * (1 - fRec29[0])) + (fRec29[0] * ((fTemp27 * fTemp29) + (fRec30[1] * fTemp31)))))));
			// post processing
			fRec30[1] = fRec30[0];
			fRec31[1] = fRec31[0];
			fRec32[1] = fRec32[0];
			fRec33[1] = fRec33[0];
			fRec34[1] = fRec34[0];
			fRec35[1] = fRec35[0];
			fRec29[1] = fRec29[0];
			fRec17[1] = fRec17[0];
			fVec2[1] = fVec2[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			iRec26[1] = iRec26[0];
			iRec25[1] = iRec25[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec18[1] = fRec18[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			IOTA = IOTA+1;
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec9[1] = fRec9[0];
			iRec8[1] = iRec8[0];
			iRec7[1] = iRec7[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			iRec4[1] = iRec4[0];
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec1[1] = fRec1[0];
			iVec0[1] = iVec0[0];
		}
	}
};



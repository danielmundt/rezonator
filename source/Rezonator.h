/* Rezonator VST Plugin (based on the Resonate sources by Don Cross)
 * Copyright (C) 2007 Daniel Schubert
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef REZONATOR_H_
#define REZONATOR_H_

#include "public.sdk/source/vst2.x/audioeffectx.h"
#include "Notchbank.h"

using namespace Rezonator;

class Rezonator : public AudioEffectX
{
public:
	Rezonator( audioMasterCallback audioMaster );
	virtual ~Rezonator();

	// Processing
	virtual void processReplacing( float** inputs, float** outputs,
		VstInt32 sampleFrames );
	virtual void processDoubleReplacing( double** inputs, double** outputs,
		VstInt32 sampleFrames );

	// Program
	virtual void setProgramName( char* name );
	virtual void getProgramName( char* name );

	// Parameters
	virtual void setParameter( VstInt32 index, float value );
	virtual float getParameter( VstInt32 index );
	virtual void getParameterLabel( VstInt32 index, char* label );
	virtual void getParameterDisplay( VstInt32 index, char* text );
	virtual void getParameterName( VstInt32 index, char* text );

	virtual bool getEffectName( char* name );
	virtual bool getVendorString( char* text );
	virtual bool getProductString( char* text );
	virtual VstInt32 getVendorVersion();

protected:
	float fGain;
	char programName[ kVstMaxProgNameLen + 1 ];
	
private:
	Notchbank notchbank;
};

#endif /*REZONATOR_H_*/

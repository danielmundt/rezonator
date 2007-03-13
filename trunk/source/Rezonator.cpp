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

#include "rezonator.h"
#include "common.h"

#define AGAIN_ID	VST_MAKE_ID( 'R', 'e', 'z', '1' )

Rezonator::Rezonator( audioMasterCallback audioMaster )
	: AudioEffectX( audioMaster, 1, 1 )	// 1 program, 1 parameter only
{
	setNumInputs( 2 );			//<! stereo in
	setNumOutputs( 2 );			//<! stereo out
	setUniqueID( AGAIN_ID );	//<! identify
	canProcessReplacing();		//<! supports replacing output
	canDoubleReplacing();		//<! supports double precision processing

	fGain = 1.f;				//<! default to 0 dB
	vst_strncpy( programName, "Default", kVstMaxProgNameLen );	// <!default program name
}

Rezonator::~Rezonator()
{
	// nothing to do here
}

void Rezonator::setProgramName( char* name )
{
	vst_strncpy( programName, name, kVstMaxProgNameLen );
}

void Rezonator::getProgramName( char* name )
{
	vst_strncpy( name, programName, kVstMaxProgNameLen );
}

void Rezonator::setParameter( VstInt32 index, float value )
{
	fGain = value;
}

float Rezonator::getParameter( VstInt32 index )
{
	return fGain;
}

void Rezonator::getParameterName( VstInt32 index, char* label )
{
	vst_strncpy( label, "Gain", kVstMaxParamStrLen );
}

void Rezonator::getParameterDisplay( VstInt32 index, char* text )
{
	dB2string( fGain, text, kVstMaxParamStrLen );
}

void Rezonator::getParameterLabel( VstInt32 index, char* label )
{
	vst_strncpy( label, "dB", kVstMaxParamStrLen );
}

bool Rezonator::getEffectName( char* name )
{
	vst_strncpy( name, "Rezonator", kVstMaxEffectNameLen );
	return true;
}

bool Rezonator::getProductString( char* text )
{
	vst_strncpy( text, "Rezonator", kVstMaxProductStrLen );
	return true;
}

bool Rezonator::getVendorString( char* text )
{
	vst_strncpy( text, "TAGEZ Audio", kVstMaxVendorStrLen );
	return true;
}

VstInt32 Rezonator::getVendorVersion()
{ 
	return 1000; 
}

void Rezonator::processReplacing( float** inputs, float** outputs,
	VstInt32 sampleFrames )
{
	float* in1  =  inputs[ 0 ];
	float* in2  =  inputs[ 1 ];
	float* out1 = outputs[ 0 ];
	float* out2 = outputs[ 1 ];

	notchbank.process( inputs, outputs, sampleFrames );
	brickwall.process( inputs, outputs, sampleFrames );

	while( --sampleFrames >= 0 )
	{
		(*out1++) = (*in1++) * fGain;
		(*out2++) = (*in2++) * fGain;
	}
}

void Rezonator::processDoubleReplacing( double** inputs, double** outputs,
	VstInt32 sampleFrames )
{
	double* in1  =  inputs[ 0 ];
	double* in2  =  inputs[ 1 ];
	double* out1 = outputs[ 0 ];
	double* out2 = outputs[ 1 ];
	double dGain = fGain;
	
	notchbank.process( ( float** )( inputs ), ( float** )( outputs ), 
		sampleFrames );
	brickwall.process( ( float** )( inputs ), ( float** )( outputs ), 
		sampleFrames );

	while( --sampleFrames >= 0 )
	{
		(*out1++) = (*in1++) * dGain;
		(*out2++) = (*in2++) * dGain;
	}
}

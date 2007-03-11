
#include "rezonator.h"
#include "common.h"

#define AGAIN_ID	VST_MAKE_ID( 'R', 'e', 'z', '1' )

AudioEffect* createEffectInstance( audioMasterCallback audioMaster )
{
	return new Rezonator::Rezonator( audioMaster );
}

Rezonator::Rezonator( audioMasterCallback audioMaster )
	: AudioEffectX( audioMaster, 1, 1 )	// 1 program, 1 parameter only
{
	setNumInputs(2);		//<! stereo in
	setNumOutputs(2);		//<! stereo out
	setUniqueID(AGAIN_ID);	//<! identify
	canProcessReplacing();	//<! supports replacing output
	canDoubleReplacing();	//<! supports double precision processing

	fGain = 1.f;			//<! default to 0 dB
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
//	float* in1  =  inputs[ 0 ];
//	float* in2  =  inputs[ 1 ];
//	float* out1 = outputs[ 0 ];
//	float* out2 = outputs[ 1 ];
//	
//	while( --sampleFrames >= 0 )
//	{
//		(*out1++) = (*in1++) * fGain;
//		(*out2++) = (*in2++) * fGain;
//	}
	
	notchbank.process( inputs, outputs, sampleFrames );
}

void Rezonator::processDoubleReplacing( double** inputs, double** outputs,
	VstInt32 sampleFrames )
{
//	double* in1  =  inputs[ 0 ];
//	double* in2  =  inputs[ 1 ];
//	double* out1 = outputs[ 0 ];
//	double* out2 = outputs[ 1 ];
//	double dGain = fGain;
//	
//	while( --sampleFrames >= 0 )
//	{
//		(*out1++) = (*in1++) * dGain;
//		(*out2++) = (*in2++) * dGain;
//	}

	notchbank.process( ( float** )( inputs ), ( float** )( outputs ), 
		sampleFrames );
}

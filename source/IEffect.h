#ifndef IEFFECT_H_
#define IEFFECT_H_

#include "public.sdk/source/vst2.x/audioeffectx.h"

namespace Rezonator
{

class IEffect
{
public:
	virtual ~IEffect() {};
	
	virtual void process( float** inputs, float** outputs,
		VstInt32 sampleFrames ) = 0;
};

}

#endif /*IEFFECT_H_*/

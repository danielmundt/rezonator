#ifndef BRICKWALL_H_
#define BRICKWALL_H_

#include "IEffect.h"

namespace Rezonator
{

class Brickwall : IEffect
{
public:
	Brickwall();
	virtual ~Brickwall();
	
	void process( float** inputs, float** outputs, VstInt32 sampleFrames );
};

}

#endif /*BRICKWALL_H_*/

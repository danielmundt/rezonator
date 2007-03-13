#ifndef REZONATORMAIN_H_
#define REZONATORMAIN_H_

#ifndef REZONATOR_H_
#include "Rezonator.h"
#endif

AudioEffect* createEffectInstance( audioMasterCallback audioMaster )
{
	return new Rezonator::Rezonator( audioMaster );
}

#endif /*REZONATORMAIN_H_*/

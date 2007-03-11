#ifndef IEFFECT_H_
#define IEFFECT_H_

namespace Rezonator
{

class IEffect
{
public:
	virtual ~IEffect();
	
	virtual void process() = 0;
};

}

#endif /*IEFFECT_H_*/

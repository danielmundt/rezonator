#ifndef REZONATORPROGRAM_H_
#define REZONATORPROGRAM_H_

namespace Rezonator
{

class RezonatorProgram
{
private:	
	float inGain;
	float outGain;
	char name[ 24 ];
	
public:
	enum ProgramParameters
	{
		// global
		NumPrograms = 16,
	
		//pParameters tags
		InGain = 0,
		OutGain,
	
		NumParams
	};

	RezonatorProgram();
	virtual ~RezonatorProgram();
};

}

#endif /*REZONATORPROGRAM_H_*/

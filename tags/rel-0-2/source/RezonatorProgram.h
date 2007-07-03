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

#ifndef REZONATORPROGRAM_H_
#define REZONATORPROGRAM_H_

namespace Rezonator
{

class RezonatorProgram
{
public:
	enum ProgramParameters
	{
		// global
		kNumPrograms = 16,
	
		// common parameters tags
		kInGain = 0,
		kWetDry,
		kOutGain,
		
		// notch specific tags
		kMidNotchFreq,
		kMidNotchActive,
		kMidNotchGain,
		
		kSideNotchFreq,
		kSideNotchActive,
		kSideNotchGain,
	
		kNumParams
	};

	RezonatorProgram();
	virtual ~RezonatorProgram();

private:	
	float fInGain;
	float fWetDry;
	float fOutGain;
	char name[ 24 ];
	
	// for furture extension
	float freserved[32];
};

}

#endif /*REZONATORPROGRAM_H_*/

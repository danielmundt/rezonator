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

#ifndef NOTCHBANK_H_
#define NOTCHBANK_H_

#include <math.h>

#include "IEffect.h"
#include "Notch.h"

namespace Rezonator
{

class Notchbank : IEffect
{
private:
	Notch* notch;
	
	double halfLife1;
	double halfLife2;
	double sr;

    double lambda1;
    double kappa1;

    double lambda2;
    double kappa2;
	
public:
	Notchbank();
	virtual ~Notchbank();
	
	void process( float** inputs, float** outputs, VstInt32 sampleFrames );
};

}

#endif /*NOTCHBANK_H_*/

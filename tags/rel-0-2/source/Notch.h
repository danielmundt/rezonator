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

#ifndef NOTCH_H_
#define NOTCH_H_

#include <math.h>

#include "public.sdk/source/vst2.x/audioeffectx.h"

namespace Rezonator
{

class Notch
{
public:
	double coeff;		//!< attenuation coefficient for demod
	double accum[ 2 ];	//!< demod accumulators (one per channel)
	double remod[ 2 ];	//!< remod accumulators (one per channel)

	double alpha;		//!< recurrence relation constant
	double beta;		//!< recurrence relation constant

	double ca;			//!< current cos(n*theta)
	double sa;			//!< current sin(n*theta)

	Notch();
	Notch( double theta, double coeff );
	virtual ~Notch();
	
	void init( double theta, double coeff );
	void update();
};

}

#endif /*NOTCH_H_*/

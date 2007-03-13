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

#include "Notch.h"

namespace Rezonator
{

Notch::Notch()
{
}

Notch::Notch( double theta, double coeff )
{
	init( theta, coeff );
}

Notch::~Notch()
{
}

void Notch::init( double theta, double _coeff )
{
	coeff = _coeff;
	alpha = sin( 0.5 * theta );
	alpha = 2.0 * alpha * alpha;
	beta  = sin( theta );
	
	sa = 0.0;
	ca = 1.0;

    for ( int i = 0; i < 2; i++ )
    {
        accum[i] = 0.0;
        remod[i] = 0.0;
    }
}

void Notch::update()
{
	double delta_ca = alpha * ca + beta * sa;
	sa -= ( alpha * sa - beta * ca);
	ca -= delta_ca;	
}

}

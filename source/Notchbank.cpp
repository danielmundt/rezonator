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

#include "notchbank.h"

#define  DDC_PI  ((double)( 3.14159265358979323846 ))

namespace Rezonator
{

Notchbank::Notchbank()
{
	int numNotches = 6;
	
	notch = new Notch[ numNotches ];

	halfLife1 = 50;
	halfLife2 = 50;	
	sr = 44100;

    lambda1 = exp ( -log( 2.0 ) / ( sr * halfLife1 * 0.001 ) );
    kappa1 = 1.0 - lambda1;

    lambda2 = exp ( -log( 2.0 ) / ( sr * halfLife2 * 0.001 ) );
    kappa2 = 1.0 - lambda2;
    
    double f_exp = 1.0;
    double loFreq = 50;
    double hiFreq = 880;

    const double df = exp ( log( hiFreq / loFreq ) / double( numNotches - 1 ) );
    double cf = 1.0;
    const double loRadsPerSample = loFreq * ( 2.0 * DDC_PI ) / sr;
    
    for ( int j = 0; j < numNotches; j++ )
    {
        notch[j].init ( cf * loRadsPerSample, pow( cf, f_exp ) );
        cf *= df;
    }
}

Notchbank::~Notchbank()
{
}

void Notchbank::process( float** inputs, float** outputs,
	VstInt32 sampleFrames )
{
	int numChannels = 2;
	int numNotches = 6;
	
	//for ( int i = 0; i < sampleFrames; i += numChannels )
	for ( int i = 0; i < sampleFrames; i++ )
	{
		for ( int c = 0; c < numChannels; c++ )
		{
			double y = 0.0;  // output value
			double x = double( inputs[ c ][ i ] );
			
			for ( int j = 0; j < numNotches; j++ )
			{
				Notch &nn = notch[ j ];
				double &accum = nn.accum[ c ];
				double &remod = nn.remod[ c ];
				accum = accum * lambda1 + x * nn.ca * nn.coeff * kappa1;
				remod = remod * lambda2 + accum * kappa2;
				y += nn.sa * remod;
			}
			
			outputs[ c ][ i ] = float( y );
		}
			
		// Update trig functions
		/*for ( int j = 0; j < numNotches; j++ )
		{
			Notch &nn = notch[ j ];
			double delta_ca = nn.alpha * nn.ca + nn.beta * nn.sa;
			nn.sa -= (nn.alpha * nn.sa - nn.beta * nn.ca);
			nn.ca -= delta_ca;
		}*/
		for ( int j = 0; j < numNotches; j++ )
		{
			notch[ j ].update();
		}
	}
}

}

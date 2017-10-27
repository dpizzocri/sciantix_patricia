//////////////////////////////////////////////////
//                                              //
//           S C I A N T I X                    //
//           ---------------                    //
//                                              //
//  Version: 0.1                                //
//  Year   : 2016                               //
//  Authors: D. Pizzocri, T. Barani, A. Magni   //
//                                              //
//////////////////////////////////////////////////

/// TrappingRate
/// This function contains the evaluation of the
/// trapping rate of gas atoms dissolved in the fuel
/// matrix into intragranular bubbles.
/// [1] Olander, Wongsawaeng, Journal of Nuclear Materials, 354 (2006), 94-109

#include "TrappingRate.h"

double TrappingRate(double diffusion_coefficient, double bubble_radius, double bubble_density)
{
	double trapping_rate(0.0); // (atoms/s)

	switch(itrapping_rate)
	{
		case 0 :
			// constant value for trial, from [1] table pag. 95:
			// const double kd = 4 * Pi * diffusion_coefficient * bubble_radius; // (m3 s-1)
			// const double bubble_density_const = 7.0 * 1.0e-04 * 1.0e+27; // (bubbles/m3)
			// trapping_rate = kd * bubble_density_const; // 1.0e-04;
			
			trapping_rate = 1.0e-04;
			break;

		case 1 :
			// from [1]
			trapping_rate = 4.0 * Pi * diffusion_coefficient * (bubble_radius + Xenon_radius_in_lattice) * bubble_density;
			break;

        default :
          ErrorMessages::Switch("TrappingRate", "itrapping_rate", itrapping_rate);
          break;
	}

	return sf_trapping_rate * trapping_rate;
}


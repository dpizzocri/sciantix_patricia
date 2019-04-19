///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.4                         //
//  Year   : 2019                        //
//  Authors: D. Pizzocri and T. Barani   //
//                                       //
///////////////////////////////////////////

/// DiffusionRate
/// This function contains the calculation of the
/// diffusion of gas atoms per unit time (1/s)

#include "DiffusionRate.h"

double DiffusionRate(double diffusion_coefficient, double grain_radius)
{
	double diffusion_rate(0.0); // (1/s)
	
	diffusion_rate = diffusion_coefficient / pow(grain_radius, 2.0);
	
	return sf_diffusion_rate * diffusion_rate;
}

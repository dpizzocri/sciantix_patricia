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

/// DiffusionRate
/// This function contains the calculation of the
/// fission gas atoms diffusion rate (1/s)

#include "DiffusionRate.h"

double DiffusionRate(double diffusion_coefficient, double grain_radius)
{
	double diffusion_rate(0.0); // (1/s)
	
	diffusion_rate = diffusion_coefficient / pow(grain_radius, 2.0);
	
	return sf_diffusion_rate * diffusion_rate;
}

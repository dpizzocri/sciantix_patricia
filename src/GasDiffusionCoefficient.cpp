///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 0.1                         //
//  Year   : 2016                        //
//  Authors: D. Pizzocri and T. Barani   //
//                                       //
///////////////////////////////////////////

#include "GasDiffusionCoefficient.h"

double GasDiffusionCoefficient(double T, double fission_rate, int option)
{
	double diffusion_coefficient(0.0);
	
	switch(option) {
		case 0 : diffusion_coefficient = pow(10, - 20);
		case 1 : diffusion_coefficient = 5.0 * pow(10, - 8) * exp(- 40262 / T);
	}
	
	return diffusion_coefficient;
}

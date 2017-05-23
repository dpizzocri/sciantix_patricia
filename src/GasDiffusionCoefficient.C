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

/// GasDiffusionCoefficient
/// This function contains a choice among possible
/// expressions for the diffusion coefficient of fission gas
/// inside the fuel grain.
/// [1] Matzke, Radiation Effects, 53 (1980), 219-242

#include "GasDiffusionCoefficient.h"

double GasDiffusionCoefficient(double temperature, double fission_rate)
{
	double diffusion_coefficient(0.0); // (m2/s)

	switch(igas_diffusion_coefficient)
	{
		case 0 :
   		  // constant value for trial
		  diffusion_coefficient = 1.0e-20;
		  break;

		case 1 :
		  // effective diffusion coefficient from [1]
		  diffusion_coefficient = 5.0e-08 * exp(- 40262.0 / temperature);
		  break;

        default :
          ErrorMessages::Switch("GasDiffusionCoefficient", "igas_diffusion_coefficient", igas_diffusion_coefficient);
          break;
	}

	return diffusion_coefficient;
}

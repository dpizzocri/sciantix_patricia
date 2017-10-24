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
/// [2] Turnbull, White, Wise, Proceedings of the Technical Committee Meeting on Water Reactor Fuel Element Computer Modelling in Steady-State, Transient and Accident Conditions (1988), 174-181

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
		  
		case 2 :
		{
		  // from [2]
		  double d1 = 7.6e-10 * exp(- 4.86e-19 / (Cons_bolt * temperature));
		  double d2 = 4.0 * 1.41e-25 * sqrt(fission_rate) * exp(- 1.91e-19 / (Cons_bolt * temperature));
		  double d3 = 2.0e-40 * fission_rate;
		  
		  diffusion_coefficient = d1 + d2 + d3;
		  break;
		}

        default :
          ErrorMessages::Switch("GasDiffusionCoefficient", "igas_diffusion_coefficient", igas_diffusion_coefficient);
          break;
	}

	return diffusion_coefficient;
}

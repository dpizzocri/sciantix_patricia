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

/// NucleationRate
/// This function contains the evaluation of the
/// nucleation rate of intragranular gas bubbles
/// inside the UO2 fuel grain.
/// [1] Olander, Wongsawaeng, Journal of Nuclear Materials, 354 (2006), 94-109

#include "NucleationRate.h"

double NucleationRate(double fission_rate)
{
	double nucleation_rate(0.0); // (bubbles/s m3)

	switch(inucleation_rate)
	{
		case 0 :
			// constant value for trial, from [1] table pag. 95
			nucleation_rate = 4.0e+20;
			break;

		case 1 :
        {
            // from [1]
			const double bubble_nucleated_per_ff(20.0);
			nucleation_rate = 2.0 * fission_rate * bubble_nucleated_per_ff;
			break;
        }

        default :
          ErrorMessages::Switch("NucleationRate", "inucleation_rate", inucleation_rate);
          break;
	}

	return nucleation_rate;
}


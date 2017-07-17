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

/// ResolutionRate
/// This function contains the evaluation of the
/// heterogeneous re-solution rate of gas atoms from
/// intragranular bubbles into the UO2 fuel matrix.
/// [1] Olander, Wongsawaeng, Journal of Nuclear Materials, 354 (2006), 94-109
/// [2] Olander, Nuclear Reactor Fuel Elements, Nat'l Tech. Info. Services, Document No. 26711, 1976, Section 13.7
/// [3] Turnbull, Journal of Nuclear Materials, 38 (1971), 203
/// [4] Losonen, Journal of Nuclear Materials, (2000) 

#include "ResolutionRate.h"

double ResolutionRate(double bubble_radius, double fission_rate)
{
	double resolution_rate(0.0); // (atoms/s)

	switch(iresolution_rate)
	{
		case 0 :
			// constant value for trial, from [1] table pag. 95
			resolution_rate = 1.0e-05;
			break;

		case 1 :
        {
            // from Olander model, [2], built on [3]
			const double ff_influence_radius = 1.0e-09; // (m)
			const double ff_range = 6.0e-06; // (m)

			resolution_rate = 2.0 * Pi * ff_range * pow((ff_influence_radius + bubble_radius), 2) * fission_rate;
			break;
        }
        
        case 2 :
        	// from [4]
        	resolution_rate = 3.0e-23 * fission_rate; // 3.0e-4
        	break;

        default :
          ErrorMessages::Switch("ResolutionRate", "iresolution_rate", iresolution_rate);
          break;
	}

	return sf_resolution_rate * resolution_rate;
}

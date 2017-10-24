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

/// DislocationDensity
/// This function contains possible models for
/// the estimation of the dislocation density
/// inside the fuel grain.

#include "DislocationDensity.h"

double DislocationDensity(double temperature, double burnup)
{
	double dislocation_density(0.0); // (m/m3)

	switch(idislocation_density)
	{
		case 0 :
			// constant value for trial
			dislocation_density = 4.0e+13;
			break;
			
		case 1 :
			// MODEL
			break;
			
		default :
          ErrorMessages::Switch("DislocationDensity", "idislocation_density", idislocation_density);
          break;
	}

	return sf_dislocation_density * dislocation_density;

}

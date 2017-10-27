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

/// DislocationRadiusOfInfluence
/// This function contains possible models for
/// the estimation of the dislocations radius
/// of influence with respect to intra-granular
/// gas bubbles inside the fuel grain.

#include "DislocationRadiusOfInfluence.h"

double DislocationRadiusOfInfluence( )
{
	double dislocation_radius_of_influence(0.0); // (m)

	switch(idislocation_radius_of_influence)
	{
		case 0 :
        {
          const int number_of_burger_vectors(5);
          dislocation_radius_of_influence = number_of_burger_vectors * Burger_vector[0];
          break;
        }

		default :
          ErrorMessages::Switch("DislocationRadiusOfInfluence", "idislocation_radius_of_influence", idislocation_radius_of_influence);
          break;
	}

	return sf_dislocation_radius_of_influence * dislocation_radius_of_influence;

}

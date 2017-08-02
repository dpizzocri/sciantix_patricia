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

/// TrappingRateAtDislocations
/// This routine contains the calculation
/// of the trapping rate at dislocations,
/// assumed as cylinders.
/// [1] F. Ham, J. Phys. Chem. Solids, 6 (1958), 335-351

#include "TrappingRateAtDislocations.h"

double TrappingRateAtDislocations(double diffusion_coefficient, double dislocation_radius)
{
  double trapping_rate_at_dislocations(0.0); // (atoms/s)

  switch(itrapping_rate_at_dislocations)
  {
	case 0 :
	  // constant value for trial
      trapping_rate_at_dislocations = 1.0e-08;
      break;

      case 1 :
      {
        // from [1]
		double dislocation_influence_radius = 1.0 / sqrt(Pi * Dislocation_density[0]);
        double geometric_factor = log(dislocation_influence_radius/dislocation_radius) - (3.0/5.0);
        if (geometric_factor == 0)
          trapping_rate_at_dislocations = 1.0e-08;
        else
          trapping_rate_at_dislocations = 2.0*Pi * diffusion_coefficient * Dislocation_density[0] / geometric_factor;
		break;
	  }

      default :
        ErrorMessages::Switch("TrappingRateAtDislocations", "itrapping_rate_at_dislocations", itrapping_rate_at_dislocations);
        break;
  }

  return sf_trapping_rate_at_dislocations * trapping_rate_at_dislocations;
}


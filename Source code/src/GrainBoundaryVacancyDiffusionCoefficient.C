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

/// GrainBoundaryVacancyDiffusionCoefficient
/// This function contains a choice among possible
/// expressions for the diffusion coefficient of vacancies
/// in the fuel grain.
/// [1] G.L.Reynolds and B.Burton, JNM, 82 (1979) 22-25
/// [2] G. Pastore et al., JNM, 456 (2015) 156.

#include "GrainBoundaryVacancyDiffusionCoefficient.h"

double GrainBoundaryVacancyDiffusionCoefficient(double temperature)
{
  double diffusion_coefficient(0.0); // (m2/s)

  switch(igrain_boundary_vacancy_diffusion_coefficient)
  {
    case 0 :
     	// constant value for trial
  	  diffusion_coefficient = 1.0e-30;
	    break;

	  case 1 :
	    // from [1]
	    diffusion_coefficient = 6.9e-04 * exp(- 3.88e+04 / temperature);
  	  break;

	  case 2 :
      // from [2]
      // the factor 3.5/5 accounts for different thickness of the samples
      diffusion_coefficient = (3.5/5.0) * 8.86e-6 * exp(- 4.17e+04 / temperature);
      break;

    default :
      ErrorMessages::Switch("GrainBoundaryVacancyDiffusionCoefficient", "igrain_boundary_vacancy_diffusion_coefficient", igrain_boundary_vacancy_diffusion_coefficient);
      break;
  }
  return diffusion_coefficient;
}

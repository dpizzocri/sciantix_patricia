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

/// GrainBoundaryVacancyDiffusionCoefficient
/// This function contains a choice among possible
/// expressions for the diffusion coefficient of vacancies
/// in the fuel grain.

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
	// at grain boundaries Reynolds and Burton, 1979
	diffusion_coefficient = 6.9e-04 * exp(- 3.88e+04 / temperature);
	break;

	case 2 :
    // at grain boundaries Pastore et al., 2015
    // the factor 3.5/5 accounts for different thickness of the samples
    diffusion_coefficient = (3.5/5.0) * 8.86e-6 * exp(- 4.17e+04 / temperature);
    break;

    default :
    ErrorMessages::Switch("GrainBoundaryVacancyDiffusionCoefficient", "igrain_boundary_vacancy_diffusion_coefficient", igrain_boundary_vacancy_diffusion_coefficient);
    break;
  }
  return diffusion_coefficient;
}


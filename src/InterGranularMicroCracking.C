///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.0                         //
//  Year   : 2018                        //
//  Authors: D. Pizzocri and T. Barani   //
//                                       //
///////////////////////////////////////////

#include "InterGranularMicroCracking.h"

// Based on
// Barani et al., JNM, 486 (2017) 96-110

void InterGranularMicroCracking( )
{
  if(!igrain_boundary_micro_cracking) return;

  const double dTemperature = Temperature[1] - Temperature[0];
  const double dBurn_up = Burn_up[1] - Burn_up[0];
  const bool heating = (dTemperature > 0.0) ? 1 : 0;
  const double transient_type = heating ? +1.0 : -1.0;
  const double span = 10.0;
  const double inflection = 1773.0 + 520.0 * exp(- Burn_up[1] / (10.0*U_UO2));
  const double exponent = 33.0;
  const double arg = (transient_type/span) * (Temperature[1] - inflection);
  const double microcracking_parameter = (transient_type/span) * exp(arg) * pow((exponent * exp(arg) +1), -1.0/exponent-1.0);
  const double healing_parameter = 1.0 / (1.0*U_UO2);

  Intergranular_fractional_intactness[1] = Solver::Decay(Intergranular_fractional_intactness[0], microcracking_parameter, 0.0, dTemperature);
  Intergranular_fractional_coverage[1] = Solver::Decay(Intergranular_fractional_coverage[0], microcracking_parameter*Intergranular_fractional_intactness[1], 0.0, dTemperature);
  Intergranular_saturation_fractional_coverage[1] = Solver::Decay(Intergranular_saturation_fractional_coverage[0], microcracking_parameter*Intergranular_fractional_intactness[1], 0.0, dTemperature);

  Intergranular_fractional_intactness[1] = Solver::Decay(Intergranular_fractional_intactness[1], healing_parameter, healing_parameter, dBurn_up);
  Intergranular_saturation_fractional_coverage[1] = Solver::Decay(Intergranular_saturation_fractional_coverage[1], healing_parameter*(1.0 - Intergranular_fractional_intactness[1]), 0.0, dBurn_up);

  const double similarity_ratio = sqrt(Intergranular_fractional_coverage[1] / Intergranular_fractional_coverage[0]);
  if(similarity_ratio < 1.0)
  {
    Intergranular_bubble_area[1] *= similarity_ratio;
    Intergranular_bubble_concentration[1] *= similarity_ratio;
    Intergranular_fractional_coverage[1] *= pow(similarity_ratio, 2);
    Intergranular_bubble_volume[1] *= pow(similarity_ratio, 1.5);
    Intergranular_bubble_radius[1] *= pow(similarity_ratio, 0.5);
    Intergranular_atoms_per_bubble[1] *= pow(similarity_ratio, 1.5);
    Intergranular_vacancies_per_bubble[1] *= pow(similarity_ratio, 1.5);
    Gas_boundary[1] *= pow(similarity_ratio, 2.5);
  }

  Gas_released[1] = Gas_produced[1] - Gas_grain[1] - Gas_boundary[1];
}

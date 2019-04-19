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

/// InterGranularGasRelease
/// This routine calculates the release of
/// gas from grain boundaries
/// occuring after bubble percolation.
/// [1] Pastore et al., NED, 256 (2013) 75-86

#include "InterGranularGasRelease.h"

void InterGranularGasRelease( )
{
  //                          F0
  //   ___________A0____________
  //   |_________A1__________  |
  //   |                    |  |
  //   |          F1        N1 N0
  //   |                    |  |
  //   |____________________|__|

  const double similarity_ratio = sqrt(Intergranular_saturation_fractional_coverage[1] / Intergranular_fractional_coverage[1]);
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

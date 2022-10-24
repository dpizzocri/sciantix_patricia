//////////////////////////////////////////////////////////////////////////////////////
//       _______.  ______  __       ___      .__   __. .___________. __  ___   ___  //
//      /       | /      ||  |     /   \     |  \ |  | |           ||  | \  \ /  /  //
//     |   (----`|  ,----'|  |    /  ^  \    |   \|  | `---|  |----`|  |  \  V  /   //
//      \   \    |  |     |  |   /  /_\  \   |  . `  |     |  |     |  |   >   <    //
//  .----)   |   |  `----.|  |  /  _____  \  |  |\   |     |  |     |  |  /  .  \   //
//  |_______/     \______||__| /__/     \__\ |__| \__|     |__|     |__| /__/ \__\  //
//                                                                                  //
//  Originally developed by D. Pizzocri & T. Barani                                 //
//                                                                                  //
//  Version: 2.0                                                                    //
//  Year: 2022                                                                      //
//  Authors: D. Pizzocri, G. Zullo.                                                 //
//                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////

#include "He_in_UO2.h"

/// He_in_UO2

void He_in_UO2( )
{
  sciantix_system.emplace_back();
  int index = sciantix_system.size() - 1;

  sciantix_system[index].setName("He in UO2");
  sciantix_system[index].setGasName("He");
  sciantix_system[index].setYield(0.0022); // ternary fission
  sciantix_system[index].setRadiusInLattice(4.73e-11);
  sciantix_system[index].setVolumeInLattice(matrix[sma["UO2"]].getOIS());

  // HENRY CONSTANT
  std::string ref_henry_constant = "The best estimate correlation for the helium Henry's constant in the UO2-single crystal samples from L. Cognini, et al., NED. 340, (2018).";
  double henry_constant(4.1e+24 * exp(- 7543.5 / history_variable[hv["Temperature"]].getFinalValue()));
  sciantix_system[index].setHenryConstant(henry_constant);

  // DIFFUSIVITY
  double diff_value(0.0);
  std::string ref_diffusivity;
  switch(input_variable[iv["iGasDiffusionCoefficient"]].getValue())
  {
    case 0 :
    {
      ref_diffusivity = "Test case: constant diffusivity";
      diff_value = 7e-19;
      break;
    }

    case 1 :
    {
      // The best estimate correlation for the cluster data available in literature with no or very limited lattice damage.
      // This correlation is recommended for sample in which INFUSION technique has been adopted.
      ref_diffusivity = "diffusivity from L. Luzzi et al., Nuclear Engineering and Design, 330 (2018) 265-271";
      diff_value = 2.0e-10 * exp(- 24603.4 / history_variable[hv["Temperature"]].getFinalValue());      
      break;
    }

    case 2 :
    {
      ref_diffusivity = "single gas-atom diffusivity from Talip et al. (2017)";
      diff_value = 1.0e-7 * exp(- 30057.9 /  history_variable[hv["Temperature"]].getFinalValue());
      break;
    }

    case 99 :
    {
      ref_diffusivity = "Test case: zero diffusion coefficient";
      diff_value = 0.0;
      break;
    }

    default :
      ErrorMessages::Switch("GasDiffusionCoefficient", "igas_diffusion_coefficient", input_variable[iv["iGasDiffusionCoefficient"]].getValue());
      break;
  }
  diff_value *= sf_diffusion_coeff;
  sciantix_system[index].setDiffusivity(diff_value);

  // Re-solution of the gas in the fuel matrix
  double resolution_rate(0.0);
  std::string ref_resolution_rate;
  switch(input_variable[iv["iResolutionRate"]].getValue())
  {
    case 0 :
    {
      ref_resolution_rate = "Constant resolution rate from Olander, Wongsawaeng, Journal of Nuclear Materials, 354 (2006), 94-109, table pag. 95";
      resolution_rate = 1.0e-4;
      break;
    }

    case 1 :
    {
      ref_resolution_rate = "Resolution rate from J.A. Turnbull, Journal of Nuclear Materials, 38 (1971), 203";
      resolution_rate = 2.0 * M_PI * matrix[sma["UO2"]].getFFrange() * pow(matrix[sma["UO2"]].getFFinfluenceRadius()
                        + sciantix_variable[sv["Intragranular bubble radius"]].getFinalValue(), 2) * history_variable[hv["Fission rate"]].getFinalValue();
      break;
    }

    case 2 :
    {
      ref_resolution_rate = "Resolution rate from Losonen, Journal of Nuclear Materials, (2000)";
      resolution_rate = 3.0e-23 * history_variable[hv["Fission rate"]].getFinalValue();
      break;
    }

    case 3 :
    {
      ref_resolution_rate = "J.A. Turnbull, Journal of Nuclear Materials, 38 (1971), 203 & thermal resolution rate";
      double irradiation_resolution_rate = 2.0 * M_PI * matrix[sma["UO2"]].getFFrange() * pow(matrix[sma["UO2"]].getFFinfluenceRadius()
        + sciantix_variable[sv["Intragranular bubble radius"]].getFinalValue(), 2) * history_variable[hv["Fission rate"]].getFinalValue();
            
      // compressibility factor (Z)
      double helium_hard_sphere_diameter = 2.973e-10 * (0.8414 - 0.05 * log (history_variable[hv["Temperature"]].getFinalValue() / 10.985)); // (m)
      double helium_volume_in_bubble = matrix[sma["UO2"]].getOIS(); // 7.8e-30, approximation of saturated nanobubbles
      double y = M_PI * pow(helium_hard_sphere_diameter, 3) / (6.0 * helium_volume_in_bubble);
      double compressibility_factor = (1.0 + y + pow(y, 2) - pow(y, 3)) / (pow(1.0 - y, 3));

      // The thermal resolution rate is written according to Cognini et al. 2021
      // + thermal_resolution_rate * m (m is the concentration of helium trapped in intra-granular bubbles)
      //   thermal_resolution_rate = 3 D k_H k_B T Z / R_b^2
      double thermal_resolution_rate;

      if(sciantix_variable[sv["Intragranular bubble radius"]].getFinalValue() > 0.0)
        thermal_resolution_rate = 3 * diff_value * henry_constant * physics_constant[pc["Boltzmann constant"]].getValue() * history_variable[hv["Temperature"]].getFinalValue() * compressibility_factor / pow(sciantix_variable[sv["Intragranular bubble radius"]].getFinalValue(), 2);
      else
        thermal_resolution_rate = 0.0;

      resolution_rate = irradiation_resolution_rate + thermal_resolution_rate;

      break;
    }

    default :
      ErrorMessages::Switch("Resolution rate", "iresolution_rate", input_variable[iv["iResolutionRate"]].getValue());
      break;
  }
  resolution_rate *= sf_resolution_rate;
  sciantix_system[index].setResolutionRate(resolution_rate);

  // Trapping of the gas in the fuel matrix
  double trapping_rate(0.0);
  std::string ref_trapping_rate;
  switch(input_variable[iv["iTrappingRate"]].getValue())
  {
    case 0 :
    {
      ref_trapping_rate = "Constant trapping rate from Olander, Wongsawaeng, Journal of Nuclear Materials, 354 (2006), 94-109, table pag. 95.";
      trapping_rate = 9.35e-6;
      break;
    }

    case 1 :
    {
      ref_trapping_rate = "F.S. Ham, Journal of Physics and Chemistry of Solids, 6 (1958) 335-351.";

      if(sciantix_variable[sv["Intragranular bubble concentration"]].getFinalValue() == 0.0)
        trapping_rate = 0.0;

      else
        trapping_rate = 4.0 * M_PI * diff_value *
          (sciantix_variable[sv["Intragranular bubble radius"]].getFinalValue() + sciantix_system[index].getRadiusInLattice()) *
          sciantix_variable[sv["Intragranular bubble concentration"]].getFinalValue();

      break;
    }

    case 99 :
    {
      ref_trapping_rate = "zero trapping rate - test case";
      break;
    }

    default :
      ErrorMessages::Switch("Trapping rate", "itrapping_rate", input_variable[iv["iTrappingRate"]].getValue());
      break;
  }
  trapping_rate *= sf_trapping_rate;
  sciantix_system[index].setTrappingRate(trapping_rate);

  std::string ref1 = "Donald R. Olander, & Motta, A. T. (2021). Light Water reactor Materials Volume II: Applications. In American Nuclear Society.";
  sciantix_system[index].setRef(ref1 + "\n" + ref_diffusivity + "\n" + ref_resolution_rate + "\n" + ref_henry_constant + "\n" + ref_trapping_rate);
}

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

#include "Xe_in_UO2.h"

/// Xe_in_UO2

void Xe_in_UO2( )
{
  sciantix_system.emplace_back();
  int index = sciantix_system.size() - 1;

  sciantix_system[index].setName("Xe in UO2");
  sciantix_system[index].setGasName("Xe");
  sciantix_system[index].setYield(0.24); // from Motta & Olander 2021 vol. 2
  sciantix_system[index].setRadiusInLattice(0.21e-9);     // (m), number from experimental results, assumed equal for Xe and Kr
  sciantix_system[index].setVolumeInLattice(matrix[sma["UO2"]].getSchottkyVolume());

  double diff_value(0.0);
  switch(input_variable[iv["iGasDiffusionCoefficient"]].getValue())
  {
    case 0 :
    {
      diff_value = 7e-19;
      break;
    }

    case 1 :
    {
      //std::string reference = "from J. A. Turnbull et al (1988), IWGFPT-32, Preston, UK, Sep 18-22.";
      double temperature = history_variable[hv["Temperature"]].getFinalValue();
      double fission_rate = history_variable[hv["Fission rate"]].getFinalValue();
      double d1 = 7.6e-10 * exp(- 4.86e-19 / (physics_constant[pc["Boltzmann constant"]].getValue() * temperature));
      double d2 = 4.0 * 1.41e-25 * sqrt(fission_rate) * exp(- 1.91e-19 / (physics_constant[pc["Boltzmann constant"]].getValue() * temperature));
      double d3 = 2.0e-40 * fission_rate;
      diff_value = d1 + d2 + d3;
      break;
    }

    case 2 :
    {
      //std::string reference = "from Matzke (1980), Radiation Effects, 53, 219-242.";
      diff_value = 5.0e-08 * exp(- 40262.0 / history_variable[hv["Temperature"]].getFinalValue());

      break;
    }

    case 3 :
    {
      //std::string reference = "from J. A. Turnbull et al., (2010), Background and Derivation of ANS-5.4 Standard Fission Product Release Model.";
      double temperature = history_variable[hv["Temperature"]].getFinalValue();
      double fission_rate = history_variable[hv["Fission rate"]].getFinalValue();
      double d1 = 7.6e-11 * exp(- 4.86e-19 / (physics_constant[pc["Boltzmann constant"]].getValue() * temperature));
      double d2 = 1.41e-25 * sqrt(fission_rate) * exp(- 1.91e-19 / (physics_constant[pc["Boltzmann constant"]].getValue() * temperature));
      double d3 = 2.0e-40 * fission_rate;
      diff_value = d1 + d2 + d3;

      break;
    }

    case 99 :
    {
      //std::string reference = "Test case: zero diffusion coefficient";
      diff_value = 0.0;
      break;
    }

    default :
      ErrorMessages::Switch("GasDiffusionCoefficient", "igas_diffusion_coefficient", input_variable[iv["iGasDiffusionCoefficient"]].getValue());
      break;
  }

  diff_value *= sf_diffusion_coeff;
  sciantix_system[index].setDiffusivity(diff_value);

  std::string ref1 = "Donald R. Olander, & Motta, A. T. (2021). Light Water reactor Materials Volume II: Applications. In American Nuclear Society.";
  std::string ref2 = "Diffusivity from J. A. Turnbull et al (1988), Preston, UK.";

  sciantix_system[index].setRef(ref1 + "\n" + ref2);
}
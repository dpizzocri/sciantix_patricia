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
  sciantix_system[index].setYield(0.24);
  sciantix_system[index].setRadiusInLattice(0.21e-9);     // (m), number from experimental results, assumed equal for Xe and Kr
  sciantix_system[index].setVolumeInLattice(matrix[sma["UO2"]].getSchottkyVolume());
  sciantix_system[index].setHenryConstant(0.0);

  double diff_value(0.0);
  std::string ref_diffusivity;
  switch(input_variable[iv["iGasDiffusionCoefficient"]].getValue())
  {
    case 0 :
    {
      diff_value = 7e-19;
      break;
    }

    case 1 :
    {
      ref_diffusivity = "Diffusivity from J. A. Turnbull et al (1988), IWGFPT-32, Preston, UK, Sep 18-22.";
      double temperature = history_variable[hv["Temperature"]].getFinalValue();
      double fission_rate = history_variable[hv["Fission rate"]].getFinalValue();
      double d1 = 7.6e-10 * exp(- 4.86e-19 / (physics_constant[pc["Boltzmann constant"]].getValue() * temperature));
      double d2 = 4.0 * 1.41e-25 * sqrt(fission_rate) * exp(- 1.91e-19 / (physics_constant[pc["Boltzmann constant"]].getValue() * temperature));
      double d3 = 8.0e-40 * fission_rate;
      diff_value = d1 + d2 + d3;
      break;
    }

    case 2 :
    {
      ref_diffusivity = "Diffusivity from Matzke (1980), Radiation Effects, 53, 219-242.";
      diff_value = 5.0e-08 * exp(- 40262.0 / history_variable[hv["Temperature"]].getFinalValue());

      break;
    }

    case 3 :
    {
      ref_diffusivity = "Diffusivity from J. A. Turnbull et al., (2010), Background and Derivation of ANS-5.4 Standard Fission Product Release Model.";
      double temperature = history_variable[hv["Temperature"]].getFinalValue();
      double fission_rate = history_variable[hv["Fission rate"]].getFinalValue();
      double d1 = 7.6e-11 * exp(- 4.86e-19 / (physics_constant[pc["Boltzmann constant"]].getValue() * temperature));
      double d2 = 1.41e-25 * sqrt(fission_rate) * exp(- 1.91e-19 / (physics_constant[pc["Boltzmann constant"]].getValue() * temperature));
      double d3 = 2.0e-40 * fission_rate;
      diff_value = d1 + d2 + d3;

      break;
    }

    case 4 :
    {
      ref_diffusivity = "diff che dipendeda x";
      double temperature = history_variable[hv["Temperature"]].getFinalValue();
      double x = sciantix_variable[sv["Stoichiometry deviation"]].getFinalValue();
      double fission_rate = history_variable[hv["Fission rate"]].getFinalValue();
      // metti double f con coeff di diff che dipende da x 
      double d1 = 7.6e-10 * exp(- 4.86e-19 / (physics_constant[pc["Boltzmann constant"]].getValue() * temperature));
      double d2 = 5.64e-25 * sqrt(fission_rate) * exp(- 1.91e-19 / (physics_constant[pc["Boltzmann constant"]].getValue() * temperature));
      double d3 = 8.0e-40 * fission_rate;
      diff_value = d1 + d2 + d3;

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
      // b = 2 F * L * pi (az + r_ig)^2
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
      resolution_rate = 2.0 * M_PI * matrix[sma["UO2"]].getFFrange() * pow(matrix[sma["UO2"]].getFFinfluenceRadius()
        + sciantix_variable[sv["Intragranular bubble radius"]].getFinalValue(), 2) * history_variable[hv["Fission rate"]].getFinalValue();
      
      // the thermal re-solution is null for xenon (equal to case 1)

      break;
    }

    default :
      ErrorMessages::Switch("Resolution rate", "iresolution_rate", input_variable[iv["iResolutionRate"]].getValue());
      break;
  }
  resolution_rate *= sf_resolution_rate;
  sciantix_system[index].setResolutionRate(resolution_rate);

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
  sciantix_system[index].setRef(ref1 + "\n" + ref_diffusivity + "\n" + ref_resolution_rate + "\n" + ref_trapping_rate);
}

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
  sciantix_system[index].setRef("Romano, M., Pizzocri, D., & Luzzi, L. (2021). On the intra-granular behaviour of a cocktail of inert gases in oxide nuclear fuel: Methodological recommendation for accelerated experimental investigation. Nuclear Engineering and Technology. https://doi.org/10.1016/J.NET.2021.11.020.");
  sciantix_system[index].setYield(0.0022); // ternary fission
  sciantix_system[index].setRadiusInLattice(4.73e-11);
  sciantix_system[index].setVolumeInLattice(matrix[sma["UO2"]].getOIS());

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
      // Single gas-atom diffusivity from Talip et al. (2017)
      diff_value = 1.0e-7 * exp(- 30057.9 /  history_variable[hv["Temperature"]].getFinalValue());
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
}

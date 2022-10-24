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

#include "GasDiffusion.h"

/// Model: (Intragranular) Gas diffusion
/// This function calls the solver SpectralDiffusion
/// to evaluate the fission gas concentration
/// inside the single grain after a fixed time step.
/// Typical numerical values for UO2 fuel are taken from:
/// [1] Olander, Wongsawaeng, Journal of Nuclear Materials, 354 (2006), 94-109
/// [2] Lassmann, Benk, JNM, 280 (2000), 127-135
/// [3] Van Uffelen et al., NET, vol.43, N.6, (2011)

void GasDiffusion( )
{

  switch(input_variable[iv["iGasDiffusionSolver"]].getValue())
  {
    case 1 :
    {
      int model_index;
      std::vector<double> parameter;
      for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
      {
        model.emplace_back();
        model_index = model.size() - 1;
        model[model_index].setName("Gas diffusion - " + sciantix_system[i].getName());
        model[model_index].setRef("Booth, A. H. (1957), Speight 1969.");

        parameter.push_back(n_modes);
        parameter.push_back(
          ( sciantix_system[i].getResolutionRate() + gas[ga[sciantix_system[i].getGasName()]].getDecayRate()) /
          ( sciantix_system[i].getResolutionRate() + sciantix_system[i].getTrappingRate() + gas[ga[sciantix_system[i].getGasName()]].getDecayRate()) * sciantix_system[i].getDiffusivity());
        parameter.push_back(sciantix_variable[sv["Grain radius"]].getFinalValue());
        parameter.push_back(sciantix_system[i].getYield() * history_variable[hv["Fission rate"]].getFinalValue());
        parameter.push_back(gas[ga[sciantix_system[i].getGasName()]].getDecayRate());

        model[model_index].setParameter(parameter);
        parameter.clear();
      }
      break;
    }

    case 2 :
    {
      // parameter --> N
      //               diffusion_coefficient
      //               resolution_rate
      //               trapping_rate
      //               decay rate 
      //               domain_radius 
      //               source_term 
      //               source_term_bubbles
      int model_index;
      std::vector<double> parameter;

      for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
      {
        model.emplace_back();
        model_index = model.size() - 1;
        model[model_index].setName("Gas diffusion - " + sciantix_system[i].getName());
        model[model_index].setRef("Booth, A. H. (1957), Speight (1969) withouth quasi-stationary hypothesis.");

        parameter.push_back(n_modes);
        parameter.push_back(sciantix_system[i].getDiffusivity());
        parameter.push_back(sciantix_system[i].getResolutionRate());
        parameter.push_back(sciantix_system[i].getTrappingRate());
        parameter.push_back(gas[ga[sciantix_system[i].getGasName()]].getDecayRate());
        parameter.push_back(sciantix_variable[sv["Grain radius"]].getFinalValue());
        parameter.push_back(sciantix_system[i].getYield() * history_variable[hv["Fission rate"]].getFinalValue());
        parameter.push_back(0.0);

        model[model_index].setParameter(parameter);
        parameter.clear();
      }
      break;
    }

    default :
      ErrorMessages::Switch("GasDiffusion", "iGasDiffusionSolver", input_variable[iv["iGasDiffusionSolver"]].getValue());
      break;
  }
}

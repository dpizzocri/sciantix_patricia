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

#include "ReleaseFromDefectiveFuelRods.h"

/// ReleaseFromDefectiveFuelRods
/// Mechanistic model for mass exchange in defective fuel rods and release 
/// of fission gas radionuclides into the water coolant under steady-state operating
/// conditions of nuclear power reactors, based on the first-order rate theory.

void ReleaseFromDefectiveFuelRods( )
{
  model.emplace_back();
  int model_index = model.size() - 1;
  model[model_index].setName("Release from defective fuel rods");
  switch(input_variable[iv["iDefectiveFuelRod"]].getValue())
  {
    case 0 :
    {   
      std::vector<double> parameter;
      std::string reference = "No model for defective fuel rods";
      parameter.push_back(0.);
      parameter.push_back(0.);
      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);
      break;
    }

    case 1 :
    {
      // dn/dt = q - (epsilon + lambda)n
      // -> dR / dt = - epsilon R

      std::vector<double> parameter;
      std::string reference = "M. S. Veshchunov et al. NED 343 (2019) 57-62.";
      parameter.push_back(0.);
      parameter.push_back(0.);
      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);

      break;
    }

    default :
      ErrorMessages::Switch("Release from defective fuel rods", "idefective_fuel_rods", input_variable[iv["iDefectiveFuelRod"]].getValue());
      break;
  }
}



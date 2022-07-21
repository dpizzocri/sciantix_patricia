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

/// Burnup model
/// This routine sets the objects that represent the models used by Sciantix during the simulation
/// Each Model contains its own parameters which are used by the solver

#include "Burnup.h"

void Burnup( )
{
  model.emplace_back();
  int model_index = model.size() - 1;
  model[model_index].setName("Burnup");

  double specific_power = (history_variable[hv["Fission rate"]].getFinalValue()
    * 3.611111e-22 / sciantix_variable[sv["Fuel density"]].getFinalValue());
  
  std::string reference = "Burnup evolution.";
  std::vector<double> parameter;
  parameter.push_back(specific_power);

  model[model_index].setParameter(parameter);
  model[model_index].setRef(reference);
}

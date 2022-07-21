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

#include "GrainBoundaryVenting.h"

void GrainBoundaryVenting( )
{
  if(!input_variable[iv["iGrainBoundaryVenting"]].getValue()) return;
 
  model.emplace_back();
  int model_index = model.size() - 1;
  model[model_index].setName("Grain-boundary venting");
  
  std::vector<double> parameter;
  
  // screw parameter
  const double screw_parameter = 0.1;
  parameter.push_back(screw_parameter);

  // span parameter
  const double span_parameter = 12.0;
  parameter.push_back(span_parameter);

  // cent parameter
  const double cent_parameter = 0.43;
  parameter.push_back(cent_parameter);
  
  model[model_index].setParameter(parameter);
  model[model_index].setRef("from Pizzocri et al., D6.1 (2020), H2020 Project INSPYRE");
}


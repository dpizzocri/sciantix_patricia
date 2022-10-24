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

#include "GrainBoundarySweeping.h"

/// GrainBoundarySweeping
/// This model describe the treatment of the grain-boundary sweeping phenomenon

void GrainBoundarySweeping( )
{
  model.emplace_back();

  int model_index = model.size() - 1;

  model[model_index].setName("Grain-boundary sweeping");

  switch(input_variable[iv["iGrainBoundarySweeping"]].getValue())
  {
    case 0 :
    {
      std::vector<double> parameter;
      parameter.push_back(0.0);
      model[model_index].setParameter(parameter);
      model[model_index].setRef("No grain-boundary sweeping");

      break;
    }

    case 1 :
    {
      // fraction of sweeped volume = dV/V = 3 dr / r
      // fraction of intra-granular gas concentration sweeped = dC / C = - 3 dr / r
      
      std::vector<double> parameter;
      parameter.push_back(3 * sciantix_variable[sv["Grain radius"]].getIncrement() / sciantix_variable[sv["Grain radius"]].getFinalValue());
      model[model_index].setParameter(parameter);
      model[model_index].setRef("Model for grain-boundary sweeping.");

      break;
    }

    default :
      ErrorMessages::Switch("GrainBoundarySweeping", "igrain_boundary_sweeping", input_variable[iv["iGrainBoundarySweeping"]].getValue());
      break;
  }
}

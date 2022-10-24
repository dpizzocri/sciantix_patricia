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

#include "NucleationRate.h"

/// Nucleation rate
/// This function contains the evaluation of the nucleation rate of intragranular gas bubble inside the UO2 fuel grain.

void NucleationRate( )
{
  model.emplace_back();
  int model_index = model.size() - 1;
  model[model_index].setName("Nucleation rate");
  switch(input_variable[iv["iNucleationRate"]].getValue())
  {
    case 0 :
    {
      std::string reference = "constant value for trial, from [1] table pag. 95";
      double nucleation_rate = 4e20;
      nucleation_rate *= sf_nucleation_rate;

      std::vector<double> parameter;
      parameter.push_back(nucleation_rate);
      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);

      break;
    }

    case 1 :
    {
      std::string reference = "Olander, Wongsawaeng, Journal of Nuclear Materials, 354 (2006), 94-109, table pag. 95";
      double nucleation_rate = 2.0 * history_variable[hv["Fission rate"]].getFinalValue() * 25;
      nucleation_rate *= sf_nucleation_rate;

      std::vector<double> parameter;
      parameter.push_back(nucleation_rate);
      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);
      break;
    }

    default :
      ErrorMessages::Switch("NucleationRate", "inucleation_rate", input_variable[iv["iNucleationRate"]].getValue());
      break;
  }
}



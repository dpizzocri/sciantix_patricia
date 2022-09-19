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

#include "ResolutionRate.h"

/// ResolutionRate
/// This model contains the evaluation of the heterogeneous re-solution rate of gas atoms from intragranular bubbles into the UO2 fuel matrix.

void ResolutionRate( )
{
  model.emplace_back();
  int model_index = model.size() - 1;
  model[model_index].setName("Resolution rate");
  switch(input_variable[iv["iResolutionRate"]].getValue())
  {
    case 0 :
    {
      std::string reference = "Constant resolution rate from Olander, Wongsawaeng, Journal of Nuclear Materials, 354 (2006), 94-109, table pag. 95";
      double resolution_rate = 1.0e-4;
      resolution_rate *= sf_resolution_rate;

      std::vector<double> parameter;
      parameter.push_back(resolution_rate);
      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);
      break;
    }

    case 1 :
    {
      // The irradiation-induced resolution rate is here the same for all the fission gas
      std::string reference = "J.A. Turnbull, Journal of Nuclear Materials, 38 (1971), 203";
      double resolution_rate = 2.0 * M_PI * matrix[sma["UO2"]].getFFrange() * pow(matrix[sma["UO2"]].getFFinfluenceRadius()
                        + sciantix_variable[sv["Intragranular bubble radius"]].getFinalValue(), 2) * history_variable[hv["Fission rate"]].getFinalValue();
      resolution_rate *= sf_resolution_rate;
      
      std::vector<double> parameter;
      parameter.push_back(resolution_rate);
      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);
      break;
    }

    case 2 :
    {
      std::string reference = "Losonen, Journal of Nuclear Materials, (2000)";
      double resolution_rate = 3.0e-23 * history_variable[hv["Fission rate"]].getFinalValue();
      resolution_rate *= sf_resolution_rate;
      
      std::vector<double> parameter;
      parameter.push_back(resolution_rate);
      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);

      break;
    }
    
    default :
      ErrorMessages::Switch("model for resolution rate", "iresolution_rate", input_variable[iv["iResolutionRate"]].getValue());
      break;
  }
}



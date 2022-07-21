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

#include "TrappingRate.h"

/// Trapping rate
/// This model contains the evaluation of the trapping rate of gas atoms dissolved in the fuel matrix into intagranular bubbles.

void TrappingRate( )
{
  model.emplace_back();
  int model_index = model.size() - 1;
  model[model_index].setName("Trapping rate");
  switch(input_variable[iv["iTrappingRate"]].getValue())
  {
    case 0 :
    {
      std::string reference = "Constant trapping rate from Olander, Wongsawaeng, Journal of Nuclear Materials, 354 (2006), 94-109, table pag. 95.";
      double trapping_rate = 9.35e-6;
      trapping_rate *= sf_trapping_rate;

      std::vector<double> parameter;
      parameter.push_back(trapping_rate);
      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);

      break;
    }

    case 1 :
    {
      std::string reference = "F.S. Ham, Journal of Physics and Chemistry of Solids, 6 (1958) 335-351.";

      double trapping_rate = 4.0 * M_PI * sciantix_system[sy["Xe in UO2"]].getDiffusivity() *
        (sciantix_variable[sv["Intragranular bubble radius"]].getFinalValue() + sciantix_system[sy["Xe in UO2"]].getRadiusInLattice()) *
        sciantix_variable[sv["Intragranular bubble concentration"]].getFinalValue();
      trapping_rate *= sf_trapping_rate;

      std::vector<double> parameter;
      parameter.push_back(trapping_rate);
      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);
      break;
    }

    case 99 :
    {
      std::string reference = "zero trapping rate - test case";
      std::vector<double> parameter;
      parameter.push_back(0.0);
      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);
      break;
    }

    default :
      ErrorMessages::Switch("model for trapping rate", "itrapping_rate", input_variable[iv["iTrappingRate"]].getValue());
      break;
  }
}

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

#include "GrainGrowth.h"

/// GrainGrowth
/// This model describes grain growth as a temperature controlled mechanism.
void GrainGrowth( )
{
  model.emplace_back();

  int model_index = model.size() - 1;

  model[model_index].setName("Grain growth");
  switch (input_variable[iv["iGrainGrowth"]].getValue())
  {
    case 0 :
    // no grain growth
    {
      const std::string reference = "No grain growth.";
      std::vector<double> parameter;
      parameter.push_back(0);
      parameter.push_back(0);

      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);

      break;
		}

    case 1 :
    // from [1]
    // The grain growth kinetic is described by Ainscough et al.,
    // by means of the following equation:
    // dD/dt = k * (1/D - f(BU)/Dm)
    // where
    // D = grain size (um)
    // k, the rate constant, is
    // k = 5.24e+7 * exp(-2.67e+5 / (R*T)) (um^2/h)
    // R = 8.314 (J/K mol)
    // T = temperature (K)
    // Dm, the limiting grain size, is a function of temperature such that
    // Dm = 2.23e+3 * exp(-7620 / T) (um)
    // f(Bu) = 1 + 0.002e-03 * Burnup (GWd/teU)
    // In detail, the presence of this last term in the rate equation
    // allows to take into account the effect of irradiation on grain growth
    // (consisting in the increasing retarding effect of fission products)
    {
      const std::string reference = "Ainscough et al., Journal of Nuclear Materials, 49 (1973) 117-128";
      std::vector<double> parameter;
      double grain_diameter_limit(0.0); // (m)
      double burnup_factor(0.0); // (/)

      grain_diameter_limit = 2.23e-03 * exp(-7620.0 / history_variable[hv["Temperature"]].getFinalValue());
      burnup_factor = 1.0 + 0.002 * sciantix_variable[sv["Burnup"]].getFinalValue() / 0.88 * 1.0e-03;

      parameter.push_back(matrix[sma["UO2"]].getGrainBoundaryMobility()); // parameter[0] = growth rate
      parameter.push_back(- (matrix[sma["UO2"]].getGrainBoundaryMobility() * burnup_factor) / grain_diameter_limit); // parameter[1] = source term

      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);

      break;
    }

    case 2 :
    // ANN
    {
      const std::string reference = "ANN fitting Ainscough data";
      std::vector<double> parameter;
      parameter.push_back(0);
      parameter.push_back(0);

      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);

      break;
		}

    default :
      ErrorMessages::Switch("model for grain growth", "igrain_growth", input_variable[iv["iGrainGrowth"]].getValue());
      break;
  }
}

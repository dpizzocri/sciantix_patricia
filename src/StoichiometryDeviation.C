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

#include "StoichiometryDeviation.h"

/// Stoichiometry deviation
/// scrivi descrizione cane maledetto
void StoichiometryDeviation( )
{
  model.emplace_back();

  int model_index = model.size() - 1;

  model[model_index].setName("Stoichiometry deviation");
  switch (input_variable[iv["iStoichiometry"]].getValue())
  {
    case 0 :
    // no deviation 
    {
      const std::string reference = "No stoichiometry deviation.";
      std::vector<double> parameter;
      parameter.push_back(0);
      
      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);

      break;
		}

    case 1 : 
    // The oxidation model described by Carter-Lay
    // They found that the oxidation rates are proportional to
    // the surface-to-volume ratio of the specimens and to the (CO2+CO) partial pressure in a (CO2+CO+inert gas) environment.
    // dx/dt = alpha*(S/V)*[x_eq - x]
    // alpha is the reaction rate alpha = A*exp(-Q/T) where A and Q ara constants. 
    // in this case the correlation use 
    // S/V = 437 1/m and x_eq = 0.25
    {
      const std::string reference = "Carter and Lay, JNM (1970)";
      std::vector<double> parameter;
      double coeff(0.0);
      double beta(0.0);
      //double alpha(0.0);

      coeff = 0.365 * exp(-23500/history_variable[hv["Temperature"]].getFinalValue())*600000/437;
      beta = 0.365 * exp(-23500/history_variable[hv["Temperature"]].getFinalValue()) * 0.1 * 600000/437;
      //alpha = 0.365 * exp(-23500/history_variable[hv["Temperature"]].getFinalValue());
      parameter.push_back(coeff); // x_eq
      parameter.push_back(beta);
      //std::cout << alpha << std::endl; //fa output su terminale
      //parameter.push_back(0.0);

      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);

      break;
    }
    
    default :
      ErrorMessages::Switch("Stoichiometry Deviation", "istoichiometry_deviation", input_variable[iv["iStoichiometry"]].getValue());
      break;
  }
}

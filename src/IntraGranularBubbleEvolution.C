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

#include "IntraGranularBubbleEvolution.h"

/// IntraGranularBubbleEvolution
/// This model contains a choice among possible
/// expressions for the bubble number density and
/// the bubble radius inside the fuel grain.

void IntraGranularBubbleEvolution( )
{
  model.emplace_back();
  int model_index = model.size() - 1;
  model[model_index].setName("Intragranular bubble evolution");
  switch(input_variable[iv["iIntraGranularBubbleEvolution"]].getValue())
  {
    case 0 :
    {
      std::string reference = "Constant trial values.";

      sciantix_variable[sv["Intragranular bubble concentration"]].setInitialValue(7.0e23);
      sciantix_variable[sv["Intragranular bubble radius"]].setInitialValue(1.0e-9);

      sciantix_variable[sv["Intragranular bubble concentration"]].setFinalValue(7.0e23);
      sciantix_variable[sv["Intragranular bubble radius"]].setFinalValue(1.0e-9);

      for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
      {
        sciantix_variable[sv["Intragranular " + sciantix_system[i].getGasName() + " atoms per bubble"]].setFinalValue(
          sciantix_variable[sv[sciantix_system[i].getGasName() + " at grain boundary"]].getFinalValue() /
          sciantix_variable[sv["Intragranular bubble concentration"]].getFinalValue()
        );

        sciantix_variable[sv["Intragranular atoms per bubble"]].setFinalValue(
          sciantix_variable[sv["Intragranular " + sciantix_system[i].getGasName() + " atoms per bubble"]].getFinalValue() + 
          sciantix_variable[sv["Intragranular atoms per bubble"]].getFinalValue()
        );
      }
      
      std::vector<double> parameter;
      parameter.push_back(0.);
      parameter.push_back(0.);
      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);
      break;
    }

    case 1 :
    {
      // The evolution of small intra-granular bubbles in fuel grains is controlled by
      // bubble nucleation, gas atom trapping, and irradiation-induced gas atom re-solution back in the lattice

      std::string reference = "Pizzocri et al., JNM, 502 (2018) 323-330";
      std::vector<double> parameter;
      parameter.push_back(sciantix_system[sy["Xe in UO2"]].getResolutionRate()); // decay rate
      parameter.push_back(model[sm["Nucleation rate"]].getParameter().front()); // source rate

      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);

      break;
    }

    case 2 :
    {
      std::string reference = "White, Tucker, Journal of Nuclear Materials, 118 (1983), 1-38";
      sciantix_variable[sv["Intragranular bubble concentration"]].setFinalValue((1.52e+27 / history_variable[hv["Temperature"]].getFinalValue() ) - 3.3e+23);
      sciantix_variable[sv["Intragranular bubble radius"]].setFinalValue(5.0e-10 * (1.0 + 106.0 * exp(- 5.43222789e22 * history_variable[hv["Temperature"]].getFinalValue())));
      
      for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
      {
        sciantix_variable[sv["Intragranular " + sciantix_system[i].getGasName() + " atoms per bubble"]].setFinalValue(
          sciantix_variable[sv[sciantix_system[i].getGasName() + " at grain boundary"]].getFinalValue() /
          sciantix_variable[sv["Intragranular bubble concentration"]].getFinalValue());

        sciantix_variable[sv["Intragranular atoms per bubble"]].setFinalValue(
          sciantix_variable[sv["Intragranular " + sciantix_system[i].getGasName() + " atoms per bubble"]].getFinalValue() + 
          sciantix_variable[sv["Intragranular atoms per bubble"]].getFinalValue());
      }

      std::vector<double> parameter;
      parameter.push_back(0.);
      parameter.push_back(0.);

      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);

      break;
    }

    case 3 :
    {
      // Evolution of intra-granular bubbles with helium (only helium considered)

      std::string reference = "Model for evolution of intra-granular bubbles with helium.";

      sciantix_variable[sv["Intragranular bubble concentration"]].setInitialValue(2.08e+20);
      sciantix_variable[sv["Intragranular bubble radius"]].setInitialValue(1.0e-9);
      sciantix_variable[sv["Intragranular atoms per bubble"]].setInitialValue(400);
      
      sciantix_variable[sv["Intragranular bubble concentration"]].setFinalValue(2.08e+20);
      sciantix_variable[sv["Intragranular bubble radius"]].setFinalValue(1.0e-9);
      sciantix_variable[sv["Intragranular atoms per bubble"]].setFinalValue(400);

      std::vector<double> parameter;
      parameter.push_back(0.);
      parameter.push_back(0.);
      model[model_index].setParameter(parameter);
      model[model_index].setRef(reference);

      break;
    }

    default :
      ErrorMessages::Switch("model for intragranular bubble evolution", "iintra_bubble_evolution", input_variable[iv["iIntraGranularBubbleEvolution"]].getValue());
      break;
  }
}



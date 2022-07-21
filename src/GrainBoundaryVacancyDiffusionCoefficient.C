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

#include "GrainBoundaryVacancyDiffusionCoefficient.h"

/// GrainBoundaryVacancyDiffusionCoefficient
/// This function contains a choice among possible
/// expressions for the diffusion coefficient of vacancies
/// in the fuel grain.

void GrainBoundaryVacancyDiffusionCoefficient( )
{
  model.emplace_back();

  int model_index = model.size() - 1;

  model[model_index].setName("Grain boundary vacancy diffusion coefficient");

  switch(input_variable[iv["iGrainBoundaryVacancyDiffusionCoefficient"]].getValue())
  {
    case 0 :
    {
      std::vector<double> parameter;
      parameter.push_back(1e-30);
      model[model_index].setParameter(parameter);
      model[model_index].setRef("constant value for trial");

      break;
    }

    case 1 :
    {
      std::vector<double> parameter;
      parameter.push_back(6.9e-04 * exp(- 3.88e+04 / history_variable[hv["Temperature"]].getFinalValue()));
      model[model_index].setParameter(parameter);
      model[model_index].setRef("from G. L. Reynolds and B. Burton, JNM, 82 (1979) 22-25");

      break;
    }

    case 2 :
    {
      // the factor 3.5/5 accounts for different thickness of the samples
      std::vector<double> parameter;
      parameter.push_back((3.5/5.0) * 8.86e-6 * exp(- 4.17e+04 / history_variable[hv["Temperature"]].getFinalValue()));
      model[model_index].setParameter(parameter);
      model[model_index].setRef("from G. Pastore et al., JNM, 456 (2015) 156");

      break;
    }

    default :
      ErrorMessages::Switch("GrainBoundaryVacancyDiffusionCoefficient", "igrain_boundary_vacancy_diffusion_coefficient", input_variable[iv["iGrainBoundaryVacancyDiffusionCoefficient"]].getValue());
      break;
  }
}

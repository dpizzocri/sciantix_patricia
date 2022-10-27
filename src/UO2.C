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

#include "UO2.h"

/// UO2

void UO2( )
{
  matrix.emplace_back();
  int index = matrix.size() - 1;
  matrix.emplace_back();

  matrix[index].setName("UO2");
  matrix[index].setDensity(sciantix_variable[sv["Fuel density"]].getFinalValue());
  matrix[index].setGrainBoundaryMobility(1.455e-8 * exp(-32114.5 / history_variable[hv["Temperature"]].getFinalValue()));
  matrix[index].setSurfaceTension(0.7); // (N/m)
  matrix[index].setFFinfluenceRadius(1.0e-9);    // (m)
  matrix[index].setFFrange(6.0e-6);              // (m)
  matrix[index].setSchottkyVolume(4.09e-29);
  matrix[index].setOIS(7.8e-30);
  matrix[index].setSemidihedralAngle(0.872664626); // (rad)
  matrix[index].setGrainBoundaryThickness(5.0e-10); // (m)
  matrix[index].setLenticularShapeFactor(0.168610764); // 1.0 - 1.5*cos(0.872664626) + 0.5*pow(cos(0.872664626), 3)

  std::string ref1 = "Grain-boundary mobility from: Ainscough, J. B., Oldfield, B. W., Ware, J. O. (1973). JNM, 49 (2), 117-128.";
  std::string ref2 = "Data from: Koo et al. (2000); White (2004), Kogai (1997)";
  std::string ref3; 

  // Nucleation rate
  // Evaluation of the nucleation rate of intragranular gas bubble inside the UO2 fuel grain
  double nucleation_rate(0.0);
  switch(input_variable[iv["iNucleationRate"]].getValue())
  {
    case 0 :
    {
      ref3 = "Nucleation rate: constant value for trial.";
      nucleation_rate = 4e20 * sf_nucleation_rate;

      break;
    }

    case 1 :
    {
      ref3 = "Nucleation rate from Olander, Wongsawaeng, JNM, 354 (2006), 94-109, table pag. 95";      
      nucleation_rate = 2.0 * history_variable[hv["Fission rate"]].getFinalValue() * 25 * sf_nucleation_rate;

      break;
    }

    default :
      ErrorMessages::Switch("UO2", "inucleation_rate", input_variable[iv["iNucleationRate"]].getValue());
      break;
  }
  matrix[index].setNucleationRate(nucleation_rate);
  matrix[index].setRef(ref1 + "\n" + ref2 + "\n" + ref3);
}


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
  matrix[index].setRef("Grain-boundary mobility from: Ainscough, J. B., Oldfield, B. W., Ware, J. O. (1973). JNM, 49 (2), 117-128.");
  matrix[index].setDensity(sciantix_variable[sv["Fuel density"]].getFinalValue());
  matrix[index].setGrainBoundaryMobility(1.455e-8 * exp(-32114.5 / history_variable[hv["Temperature"]].getFinalValue()));
  matrix[index].setSurfaceTension(0.7); // (N/m)
  matrix[index].setFFinfluenceRadius(1.0e-9);    // (m)
  matrix[index].setFFrange(6.0e-6);              // (m)
  matrix[index].setSchottkyVolume(4.09e-29);
  matrix[index].setOIS(7.8e-30);
  matrix[index].setSemidihedralAngle(0.872664626); // (rad), 50 deg, Koo et al., 2000; White, 2004
  matrix[index].setGrainBoundaryThickness(5.0e-10); // (m) Kogai, 1997
  matrix[index].setLenticularShapeFactor(0.168610764); // 1.0 - 1.5*cos(0.872664626) + 0.5*pow(cos(0.872664626), 3)
// matrix index set stoichiometry
}


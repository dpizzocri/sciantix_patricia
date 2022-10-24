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

#include "SetPhysicsConstant.h"

void SetPhysicsConstant( )
{
  int index(0);

  physics_constant.emplace_back();
  physics_constant[index].setName("Boltzmann constant");
  physics_constant[index].setUOM("J/K");
  physics_constant[index].setValue(1.380651e-23);

  ++index;

  physics_constant.emplace_back();
  physics_constant[index].setName("U_UO2");
  physics_constant[index].setUOM("(/)");
  physics_constant[index].setValue(0.8815);

  MapPhysicsConstant();
}

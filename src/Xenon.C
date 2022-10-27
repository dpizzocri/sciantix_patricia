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

#include "Xenon.h"

/// Xenon

void Xenon( )
{
  // Stable xenon
  gas.emplace_back();
  int index = gas.size() - 1;
  gas[index].setName("Xe");
  gas[index].setAtomicNumber(54);
  gas[index].setVanDerWaalsVolume(8.48e-29);
  gas[index].setDecayRate(0.0);
  ++index;

  // 133-xenon
  gas.emplace_back();
  gas[index].setName("Xe133");
  gas[index].setAtomicNumber(54);
  gas[index].setMassNumber(133);
  gas[index].setVanDerWaalsVolume(8.48e-29);
  gas[index].setDecayRate(1.53e-6);
  ++index;
}

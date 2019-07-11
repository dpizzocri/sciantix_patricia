///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.4                         //
//  Year   : 2019                        //
//  Authors: L. Cognini                  //
//           D. Pizzocri and T. Barani   //
///////////////////////////////////////////

/// HeliumProduction
/// This routine calculates the concentration of helium
/// produced by ternary fissions, 16O(n,alpha) recations and a-decays of actinides in the fuel.

#include "HeliumProduction.h"

void HeliumProduction( )
{
  Helium_produced[1] = Solver::Integrator(He4[1], Fission_yield_He * Fissionrate[1], dTime_s);
  He4[1] = Helium_produced[1];
}

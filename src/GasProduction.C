///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 0.1                         //
//  Year   : 2016                        //
//  Authors: D. Pizzocri and T. Barani   //
//                                       //
///////////////////////////////////////////

/// GasProduction
/// This routine calculates the concentration of inert gas
/// produced by fission reactions in the fuel.

#include "GasProduction.h"

void GasProduction( )
{
  const double fission_yield = Fission_yield_Xe + Fission_yield_Kr;

  Gas_produced[0] = Gas_produced[1];
  Gas_produced[1] = Solver::Integrator(Gas_produced[0], fission_yield * Fissionrate[1], dTime_s);
}

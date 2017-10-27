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

/// GasAtDislocations
/// This function contains the evaluation of the inert
/// fission gas which is subtracted from the fuel grain
/// matrix and trapped by the bubbles at dislocations.
/// This model can be switched on/off.

#include "GasAtDislocations.h"

void GasAtDislocations( )
{
  double trapping_rate_at_dislocations(1.0e-08);
  double initial_gas_grain_solution = Gas_grain_solution[1];
  
  Gas_grain_solution[1]  = Solver::Decay(initial_gas_grain_solution, trapping_rate_at_dislocations, 0.0, dTime_s);
  double dGas_precipitated_at_dislocations = Gas_grain_solution[1] - initial_gas_grain_solution;
  
  Gas_grain_dislocations[1] = Solver::Integrator(Gas_grain_dislocations[0], - dGas_precipitated_at_dislocations, 1.0);
  
}


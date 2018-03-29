///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.0                         //
//  Year   : 2018                        //
//  Authors: D. Pizzocri and T. Barani   //
//                                       //
///////////////////////////////////////////

#include "Burnup.h"

void Burnup( )
{
  const double specific_power = (Fissionrate[1] * Ener_fiss / Fuel_density[1]) / (M_1*h_d*s_h);
  Burn_up[1] = Solver::Integrator(Burn_up[0], specific_power, dTime_s);

  const double temperature_threshold(1273.0);
  double time_below_threshold = 1.0;
  if(temperature_threshold > Temperature[0] && temperature_threshold > Temperature[1]) time_below_threshold = 1.0;
  if(temperature_threshold < Temperature[0] && temperature_threshold < Temperature[1]) time_below_threshold = 0.0;
  if(temperature_threshold > Temperature[0] && temperature_threshold < Temperature[1])
    time_below_threshold = (temperature_threshold - Temperature[0])/(Temperature[1] - Temperature[0]);
  if(temperature_threshold < Temperature[0] && temperature_threshold > Temperature[1])
    time_below_threshold = (temperature_threshold - Temperature[1])/(Temperature[1] - Temperature[0]);

  Effective_burn_up[1] = Solver::Integrator(Effective_burn_up[0], time_below_threshold*specific_power, dTime_s);
}

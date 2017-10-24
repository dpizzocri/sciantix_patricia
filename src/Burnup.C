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

#include "Burnup.h"

void Burnup( )
{
  const double burning_rate = 1.0e-06 * Fissionrate[1] * Ener_fiss / (Fuel_density[1] * U_UO2); // (GW/tU)
  const double dtime_d = dTime_s / (s_h * h_d);

  dBurn_up = burning_rate * dtime_d;
  Burn_up[1] = Solver::Integrator(Burn_up[0], burning_rate, dtime_d);

  const double temperature_threshold(1273.0);
  double fraction_below_threshold(0.0);

  if ((Temperature[1] < temperature_threshold) &&
      (Temperature[0] < temperature_threshold))
    fraction_below_threshold = 1.0;
  else if ((Temperature[1] < temperature_threshold) ||
           (Temperature[0] < temperature_threshold))
    fraction_below_threshold = (temperature_threshold - Temperature[0]) / (Temperature[1] - Temperature[0]);

  dEffective_burn_up = fraction_below_threshold * dBurn_up;
  Effective_burn_up[1] = Solver::Integrator(Effective_burn_up[0], burning_rate, fraction_below_threshold * dtime_d);
}

///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.4                         //
//  Year   : 2019                        //
//  Authors: D. Pizzocri and T. Barani   //
//                                       //
///////////////////////////////////////////

/// TimeStepCalculation
/// This routine calculates the time step length
/// by dividing the time intervals provided in input
/// in a fixed number of time steps (also set by input).

#include "TimeStepCalculation.h"

double TimeStepCalculation( )
{
  double time_step(0.0);

  // Find the current time interval
  double lower_bound(0.0), upper_bound(0.0);
  for (int n=0; n<Input_history_points-1; n++)
    if (Time_h >= Time_input[n] && Time_h < Time_input[n+1])
    {
      lower_bound = Time_input[n];
      upper_bound = Time_input[n+1];
    }

  // Divide the interval in time steps
  time_step = (upper_bound - lower_bound) / Number_of_time_steps_per_interval;

  if ((Time_h+time_step) > upper_bound)
    time_step = upper_bound - Time_h;

  return time_step;
}

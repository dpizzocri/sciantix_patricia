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

#include "GrainRecrystallization.h"

// Based on
// Pizzocri et al., JNM, 487 (2019) 23-29

void GrainRecrystallization( )
{
  if (!igrain_recrystallization) return;

  const double effective_burn_up_threshold(50.0);
  double dEffective_burn_up = 0.0;
  if(Effective_burn_up[1] >= effective_burn_up_threshold && Effective_burn_up[0] < effective_burn_up_threshold)
    dEffective_burn_up = Effective_burn_up[1] - effective_burn_up_threshold;
  if(Effective_burn_up[1] >= effective_burn_up_threshold && Effective_burn_up[0] >= effective_burn_up_threshold)
    dEffective_burn_up = Effective_burn_up[1] - Effective_burn_up[0];

  const double recrystallization_rate = 1.0/(7.0*U_UO2);
  const double asymptotic_grain_radius = 150.0e-09;
  const double source_term = recrystallization_rate*asymptotic_grain_radius;
  Grain_radius[1] = Solver::Decay(Grain_radius[0], recrystallization_rate, source_term, dEffective_burn_up);
}

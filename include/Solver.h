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

#include <cmath>
#include <vector>
#include "GlobalVariables.h"

namespace Solver
{
  double Integrator(double initial_condition, double source_term, double time_step);

  double Decay(double initial_condition, double deacy_rate, double source_term, double time_step);

  double LimitedGrowth(double initial_condition, double growth_rate, double source_term, double time_step);

  double SpectralDiffusion(std::vector<double>& initial_condition, int N, double diffusion_coefficient, double domain_radius, double source_term, double time_step);

  double FORMAS(double initial_condition[], double diffusion_coefficient, double domain_radius, double source_term, double time_step);
};

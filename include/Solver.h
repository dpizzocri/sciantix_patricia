//////////////////////////////////////////////////
//                                              //
//           S C I A N T I X                    //
//           ---------------                    //
//                                              //
//  Version: 0.1                                //
//  Year   : 2016                               //
//  Authors: D. Pizzocri, T. Barani, A. Magni   //
//                                              //
//////////////////////////////////////////////////

#include <cmath>
#include <vector>

namespace Solver
{
  double Integrator(double initial_condition, double source_term, double time_step);

  double Decay(double initial_condition, double decay_rate, double source_term, double time_step);

  double LimitedGrowth(double initial_condition, double growth_rate, double source_term, double time_step);

  double BinaryInteraction(double initial_condition, double geometric_coefficient, double source_term, double time_step);

  double SpectralDiffusion(std::vector<double>& initial_condition, int N, double diffusion_coefficient, double trapping_rate_spectral, double domain_radius, double source_term, double time_step);

  double FORMAS(double initial_condition[], double diffusion_coefficient, double domain_radius, double source_term, double time_step);
};


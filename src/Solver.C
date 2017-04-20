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

/// Solver
/// This a namespace collecting all the solvers
/// for ODEs and PDEs used in SCIANTIX.
/// In general, the ODEs and PDEs are solved
/// by the Backward Euler (BE) method.
/// For non-linear problems, BE is paired
/// with Newton method.

#include <iostream>
#include "Solver.h"
#include "GlobalVariables.h"
using namespace std;

namespace Solver
{
  // Integrator
  // Solver for the ODE [y' = + S]
  double Integrator(double initial_condition, double source_term, double time_step)
  {
    return initial_condition + source_term * time_step;
  }
  
  // Decay
  // Solver for the ODE [y' = - L y + S]
  double Decay(double initial_condition, double decay_rate, double source_term, double time_step)
  {
    return (initial_condition + source_term * time_step) / (1.0 + decay_rate * time_step);
  }

  // LimitedGrowth
  // Solver for the ODE [y' = k / y + S ]
  double LimitedGrowth(double initial_condition, double growth_rate, double source_term, double time_step)
  {
    return 0.5 * ((initial_condition + source_term * time_step) + sqrt(pow(initial_condition + source_term * time_step, 2) + 4.0 * growth_rate * time_step));
  }

  // SpectralDiffusion
  // Solver for the spatially averaged solution of the PDE [dy/dt = D div grad y + S]
  // We apply a spectral approach in space, projecting the equation on the eigenfunctions of the laplacian operator.
  // We use the first order backward Euler solver in time.
  // The number of terms in the expansion, N, is fixed a priori.
  double SpectralDiffusion(std::vector<double>& initial_condition, int N, double diffusion_coefficient, double domain_radius, double source_term, double time_step)
  {   
    unsigned short int n(0);
    unsigned short int np1(1);

    double diffusion_rate_coeff(0.0);
    double diffusion_rate(0.0);
    double source_rate_coeff(0.0);
    double source_rate(0.0);
	std::vector<double> time_coefficient(N, 0.0);
	double projection_coeff(0.0);
	double solution(0.0);

    diffusion_rate_coeff = pow(Pi, 2) * diffusion_coefficient / pow(domain_radius, 2);
    projection_coeff = - 2.0 * domain_radius * sqrt(2.0 * domain_radius / Pi);
    source_rate_coeff = projection_coeff * source_term;
    

    for (n = 0; n < N; n++)
    {
      np1 = n + 1;
      const double n_coeff = pow(- 1.0, np1) / np1;

      diffusion_rate = diffusion_rate_coeff * pow(np1, 2);
      source_rate = source_rate_coeff * n_coeff;

      time_coefficient[n] = Solver::Decay(initial_condition[n], diffusion_rate, source_rate, time_step);
      initial_condition[n] = time_coefficient[n];

      solution += projection_coeff * n_coeff * time_coefficient[n] / ((4./3.) * Pi * pow(domain_radius, 3));
    }
    
    return solution;
  }
  
  // FORMAS
  // Solver for the spatially average solution of the PDE [dy/dt = D div grad y + S]
  // designed for time-varying conditions [1,2]
  // [1] Forsberg and Massih, Journal of Nuclear Materials, 127 (1985) 141-145
  // [2] Lassmann and Benk, Journal of Nuclear Materials, 280 (2000) 127-135
  double FORMAS(double initial_condition[], double diffusion_coefficient, double domain_radius, double source_term, double time_step)
  {
    // Constants derived from a priori linear approximation of the diffusion kernel
    // Some are not needed and reported for the sake of completeness
    //const double a_coeff[4];
    //a_coeff[0] = 0.2315450;
    //a_coeff[1] = 0.0948453;
    //a_coeff[2] = 0.0282898;
    //a_coeff[3] = 0.6453200;

    double b_coeff[4];
    b_coeff[0] = 72.5968;
    b_coeff[1] = 796.773;
    b_coeff[2] = 29083.0;
    b_coeff[3] = 10.2469;

    double a_over_b[4];
    a_over_b[0] = 3.18947e-03;
    a_over_b[1] = 1.19037e-04;
    a_over_b[2] = 9.72726e-07;
    a_over_b[3] = 6.29771e-02;

    // Non-dimensional (diffusion) time
    const double dtau = time_step * diffusion_coefficient / pow(domain_radius, 2);

    double term[4];
    double t1 = 0.0;
    for (int n = 0; n < 4; n++)
    {
      double arg = b_coeff[n] * dtau;
      if (arg < 1.0e-04)
        term[n] = - arg;
      else if (arg > 70.0)
        term[n] = - 1.0;
      else
        term[n] = exp(- arg) - 1.0;

      t1 += term[n] * a_over_b[n];
    }

    double t2 = 0.0;
    if (dtau < 0.1)
      t2 = 2.25675833 * pow(dtau, 1.5) - 1.5 * pow(dtau, 2);
    else
      t2 = dtau - 0.06159589 * (1.0 - exp( -9.86960440 * dtau));

    // Non-dimensional source
    const double source = source_term * time_step / (t2 - t1);

    for (int n = 0; n < 4; n++)
      initial_condition[n] += term[n] * (initial_condition[n] - source * a_over_b[n]);

    return (initial_condition[0] + initial_condition[1] + initial_condition[2] + initial_condition[3]);
  }
}

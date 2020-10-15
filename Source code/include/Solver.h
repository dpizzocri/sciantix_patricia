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

#include <cmath>
#include <vector>

namespace Solver
{
  double Integrator(double initial_condition, double source_term, double time_step);

  double Decay(double initial_condition, double decay_rate, double source_term, double time_step);

  double BinaryInteraction(double initial_condition, double interaction_coefficient, double time_step);

  double LimitedGrowth(double initial_condition, double growth_rate, double source_term, double time_step);

  double SpectralDiffusion(std::vector<double>& initial_condition, int N, double diffusion_coefficient, double domain_radius, double source_term, double time_step);

  double FORMAS(double initial_condition[], double diffusion_coefficient, double domain_radius, double source_term, double time_step);

  void ConjugateGradient(int N, double A[], double b[]);

  void PBiCG(int N, double A[], double b[]);

  void PBiCGSTAB(int N, double A[], double b[]);

  void LUGauss(int N, double * A, double * b);

  void Laplace2x2(double A[], double b[]);

  void Laplace3x3(double A[], double b[]);

  double det(int N, double A[]);

  void Laplace(int  N, double A[], double b[]);
};

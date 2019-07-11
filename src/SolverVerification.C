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

/// SolverVerification
/// The method of manufactured solutions (MMS)
/// is a state-of-the-art verification method [1].
/// It is applied to verify the numerical solvers
/// of ODEs and PDEs.
/// The method is characterized by the following steps:
/// (1) a manufactured solution of the problem
/// is assumed a priori, then (2) the source/coefficients
/// generating this solution are found analytically.
/// Then, (3) the problem with artificial source/coefficients
/// is solved numerically. At last, (4) the numerical
/// solution is compared to the manufactured one.
/// The process is repeated twice, using time-step of arbitrary
/// length and time-step of half the same arbitrary length.
/// This allows estimating the order of convergence
/// of the solver being verified.
/// A specific output file (.csv) is produced
/// for every solver being verified.
/// [1] Salari and Knupp, 2000, SAND2000-1444

#include "SolverVerification.h"
#include <iostream>
using namespace std;

void SolverVerification( )
{
  int number_of_constants(5);
  double constants[number_of_constants];
  for (int n = 0; n < number_of_constants; n++)
    constants[n] = 1.0;
  double manufactured_decay_rate(0.0);
  double manufactured_growth_rate(0.0);
  double manufactured_diffusion_rate(0.0);
  double manufactured_source_term(0.0);
  double manufactured_solution(0.0);
  double manufactured_solution_first_derivative(0.0);

  double initial_condition(0.0);
  double numerical_solution_1[2];
  double numerical_solution_2[2];
  double absolute_error_1(0.0);
  double absolute_error_2(0.0);
  double order_of_convergence(0.0);

  int time_step_number(22); // from 0 to 1
  double time(0.0);
  double time_step(0.05);

  bool n_is_even(0);

  int Matrix_dimension_Laplace(4);

  // We recommend replicating the lines between "// ---"
  // to introduce the verification of another solver.
  // Modifications of these lines should be straightforward.
  // We recommend using the related namespaces for the calculation
  // of manufactured solutions and manufactured coefficients.
  // On the other hand, it is preferable to calculate the source term here,
  // since it is related to the specific solver to be verified.

  // ---
  // Integrator
  // Verification of the solver for the ODE [y' = + S]
  std::ofstream verification_integrator_out;
  verification_integrator_out.open("verification_integrator_out.csv", std::ios::out);

  initial_condition = 0.0;
  numerical_solution_1[0] = initial_condition;
  numerical_solution_1[1] = initial_condition;
  numerical_solution_2[0] = initial_condition;
  numerical_solution_2[1] = initial_condition;
  for (int n = 0; n < time_step_number; n++)
  {
    n_is_even = !(n % 2);

    time = (double)n * time_step;

    // Manufactured coefficient and solution and corresponding manufactured source term
    ManufacturedSolution::
    SinExpPow(constants, time, manufactured_solution, manufactured_solution_first_derivative);

    manufactured_source_term =
    manufactured_solution_first_derivative;

    // Numerical solution with (time_step * 1.0)
    numerical_solution_1[0] = numerical_solution_1[1];

    if (n > 0)
    numerical_solution_1[1] =
    Solver::Integrator(numerical_solution_1[0], manufactured_source_term, time_step);

    // Numerical solution with (time_step * 2.0)
    if (n_is_even)
    {
      numerical_solution_2[0] = numerical_solution_2[1];

      if (n > 0)
      numerical_solution_2[1] =
      Solver::Integrator(numerical_solution_2[0], manufactured_source_term, 2.0*time_step);
    }

    // Numerical estimation of the order of convergence
    if (n_is_even)
    {
      absolute_error_1 = std::abs(numerical_solution_1[1] - manufactured_solution);
      absolute_error_2 = std::abs(numerical_solution_2[1] - manufactured_solution);

      order_of_convergence = 2.0 * absolute_error_1 / absolute_error_2;
    }

    // Output is dumped only at common steps, for the sake of comparison
    if (n_is_even)
      verification_integrator_out << time << ","
                                  << manufactured_solution << ","
                                  << numerical_solution_1[1] << ","
                                  << numerical_solution_2[1] << ","
                                  << order_of_convergence << ","
                                  << std::endl;

  }
  verification_integrator_out.close( );


  // ---
  // Decay
  // Verification of the solver for the ODE [y' = - L y + S]
  std::ofstream verification_decay_out;
  verification_decay_out.open("verification_decay_out.csv", std::ios::out);

  initial_condition = 0.0;
  numerical_solution_1[0] = initial_condition;
  numerical_solution_1[1] = initial_condition;
  numerical_solution_2[0] = initial_condition;
  numerical_solution_2[1] = initial_condition;

  for (int n = 0; n < time_step_number; n++)
  {
    n_is_even = !(n % 2);

    time = (double)n * time_step;

    // Manufactured coefficient and solution and corresponding manufactured source term
    ManufacturedCoefficient::
    Sin(constants, time, manufactured_decay_rate);

    ManufacturedSolution::
    SinExpPow(constants, time, manufactured_solution, manufactured_solution_first_derivative);

    manufactured_source_term =
    manufactured_solution_first_derivative + manufactured_decay_rate * manufactured_solution;

    // Numerical solution with (time_step * 1.0)
    numerical_solution_1[0] = numerical_solution_1[1];

    if (n > 0)
    numerical_solution_1[1] =
    Solver::Decay(numerical_solution_1[0], manufactured_decay_rate, manufactured_source_term, time_step);

    // Numerical solution with (time_step * 2.0)
    if (n_is_even)
    {
      numerical_solution_2[0] = numerical_solution_2[1];

      if (n > 0)
      numerical_solution_2[1] =
      Solver::Decay(numerical_solution_2[0], manufactured_decay_rate, manufactured_source_term, 2.0*time_step);
    }

    // Numerical estimation of the order of convergence
    if (n_is_even)
    {
      absolute_error_1 = std::abs(numerical_solution_1[1] - manufactured_solution);
      absolute_error_2 = std::abs(numerical_solution_2[1] - manufactured_solution);

      order_of_convergence = 2.0 * absolute_error_1 / absolute_error_2;
    }

    // Output is dumped only at common steps, for the sake of comparison
    if (n_is_even)
      verification_decay_out << time << ","
                             << manufactured_solution << ","
                             << numerical_solution_1[1] << ","
                             << numerical_solution_2[1] << ","
                             << order_of_convergence << ","
                             << std::endl;

  }
  verification_decay_out.close( );

  // ---
  // LimitedGrowth
  // Verification of the solver for the ODE [y' = k / y + S]
  std::ofstream verification_limitedgrowth_out;
  verification_limitedgrowth_out.open("verification_limitedgrowth_out.csv", std::ios::out);

  initial_condition = 1.0;
  numerical_solution_1[0] = initial_condition;
  numerical_solution_1[1] = initial_condition;
  numerical_solution_2[0] = initial_condition;
  numerical_solution_2[1] = initial_condition;

  for (int n = 0; n < time_step_number; n++)
  {
    n_is_even = !(n % 2);

    time = (double)n * time_step;

    // Manufactured coefficient and solution and corresponding manufactured source term
    ManufacturedCoefficient::
    Sin2(constants, time, manufactured_growth_rate);

    ManufacturedSolution::
    CosExp(constants, time, manufactured_solution, manufactured_solution_first_derivative);

    manufactured_source_term =
    manufactured_solution_first_derivative - manufactured_growth_rate / manufactured_solution;

    // Numerical solution with (time_step * 1.0)
    numerical_solution_1[0] = numerical_solution_1[1];

    if (n > 0)
    numerical_solution_1[1] =
    Solver::LimitedGrowth(numerical_solution_1[0], manufactured_growth_rate, manufactured_source_term, time_step);

    // Numerical solution with (time_step * 2.0)
    if (n_is_even)
    {
      numerical_solution_2[0] = numerical_solution_2[1];

      if (n > 0)
      numerical_solution_2[1] =
      Solver::LimitedGrowth(numerical_solution_2[0], manufactured_growth_rate, manufactured_source_term, 2.0*time_step);
    }

    // Numerical estimation of the order of convergence
    if (n_is_even)
    {
      absolute_error_1 = std::abs(numerical_solution_1[1] - manufactured_solution);
      absolute_error_2 = std::abs(numerical_solution_2[1] - manufactured_solution);

      order_of_convergence = 2.0 * absolute_error_1 / absolute_error_2;
    }

    // Output is dumped only at common steps, for the sake of comparison
    if (n_is_even)
      verification_limitedgrowth_out << time << ","
                                     << manufactured_solution << ","
                                     << numerical_solution_1[1] << ","
                                     << numerical_solution_2[1] << ","
                                     << order_of_convergence << ","
                                     << std::endl;

  }
  verification_limitedgrowth_out.close( );

  // ---
  // FORMAS
  // Verification of the solver for the spatially average solution of the PDE [dy/dt = D div grad y + S]
  std::ofstream verification_FORMAS_out;
  verification_FORMAS_out.open("verification_FORMAS_out.csv", std::ios::out);

  initial_condition = 0.0;
  static double initial_condition_term[4];
  initial_condition_term[0] = initial_condition;
  initial_condition_term[1] = initial_condition;
  initial_condition_term[2] = initial_condition;
  initial_condition_term[3] = initial_condition;
  numerical_solution_1[0] = initial_condition;
  numerical_solution_1[1] = initial_condition;
  numerical_solution_2[0] = initial_condition;
  numerical_solution_2[1] = initial_condition;

  for (int n = 0; n < time_step_number; n++)
  {
    n_is_even = !(n % 2);

    time = (double)n * time_step;

    // Manufactured coefficient and solution and corresponding manufactured source term
    manufactured_diffusion_rate = 1.0;

    ManufacturedSolution::
    SinExpPow(constants, time, manufactured_solution, manufactured_solution_first_derivative);

    manufactured_source_term =
    6.0/15.0 * manufactured_solution_first_derivative + 2.0 * manufactured_diffusion_rate * manufactured_solution;

    // Numerical solution with (time_step * 1.0)
    numerical_solution_1[0] = numerical_solution_1[1];

    // const double diffusion_coefficient(1.0);
    double diffusion_coefficient = 1.0;
    const double domain_radius(1.0);

    if (n > 0)
    numerical_solution_1[1] =
    Solver::FORMAS(initial_condition_term, diffusion_coefficient, domain_radius, manufactured_source_term, time_step);

    // Numerical solution with (time_step * 2.0)
    if (n_is_even)
    {
      numerical_solution_2[0] = numerical_solution_2[1];

      if (n > 0)
      numerical_solution_2[1] =
      Solver::FORMAS(initial_condition_term, diffusion_coefficient, domain_radius, manufactured_source_term, time_step);
    }

    // Numerical estimation of the order of convergence
    if (n_is_even)
    {
      absolute_error_1 = std::abs(numerical_solution_1[1] - manufactured_solution);
      absolute_error_2 = std::abs(numerical_solution_2[1] - manufactured_solution);

      order_of_convergence = 2.0 * absolute_error_1 / absolute_error_2;
    }

    // Output is dumped only at common steps, for the sake of comparison
    if (n_is_even)
      verification_FORMAS_out << time << ","
                                     << manufactured_solution << ","
                                     << numerical_solution_1[1] << ","
                                     << numerical_solution_2[1] << ","
                                     << order_of_convergence << ","
                                     << std::endl;

  }
  verification_FORMAS_out.close( );
  // ---

  // ---
  // SpectralDiffusion
  // Verification of the solver for the spatially average solution of the PDE [dy/dt = D div grad y + S]
  std::ofstream verification_SpectralDiffusion_out;
  verification_SpectralDiffusion_out.open("verification_SpectralDiffusion_out.csv", std::ios::out);

  initial_condition = 0.0;
  static std::vector<double> initial_condition_vector(10, initial_condition);
  numerical_solution_1[0] = initial_condition;
  numerical_solution_1[1] = initial_condition;
  numerical_solution_2[0] = initial_condition;
  numerical_solution_2[1] = initial_condition;

  for (int n = 0; n < time_step_number; n++)
  {
    n_is_even = !(n % 2);

    time = (double)n * time_step;

    // Manufactured coefficient and solution and corresponding manufactured source term
    manufactured_diffusion_rate = 1.0;

    ManufacturedSolution::
    SinExpPow(constants, time, manufactured_solution, manufactured_solution_first_derivative);

    manufactured_source_term =
    6.0/15.0 * manufactured_solution_first_derivative + 2.0 * manufactured_diffusion_rate * manufactured_solution;

    // Numerical solution with (time_step * 1.0)
    numerical_solution_1[0] = numerical_solution_1[1];

    // const double diffusion_coefficient(1.0);
    double diffusion_coefficient = 1.0;
    const double domain_radius(1.0);
    int N(1);

    if (n > 0)
    numerical_solution_1[1] =
    Solver::SpectralDiffusion(initial_condition_vector, N, diffusion_coefficient, domain_radius, manufactured_source_term, time_step);

    // Numerical solution with (time_step * 2.0)
    if (n_is_even)
    {
      numerical_solution_2[0] = numerical_solution_2[1];

      if (n > 0)
      numerical_solution_2[1] =
      Solver::SpectralDiffusion(initial_condition_vector, N, diffusion_coefficient, domain_radius, manufactured_source_term, 2.0*time_step);
    }

    // Numerical estimation of the order of convergence
    if (n_is_even)
    {
      absolute_error_1 = std::abs(numerical_solution_1[1] - manufactured_solution);
      absolute_error_2 = std::abs(numerical_solution_2[1] - manufactured_solution);

      order_of_convergence = 2.0 * absolute_error_1 / absolute_error_2;
    }

    // Output is dumped only at common steps, for the sake of comparison
    if (n_is_even)
      verification_SpectralDiffusion_out << time << ","
                                     << manufactured_solution << ","
                                     << numerical_solution_1[1] << ","
                                     << numerical_solution_2[1] << ","
                                     << order_of_convergence << ","
                                     << std::endl;

  }
  verification_SpectralDiffusion_out.close( );
  // ---

  // ---
  // Laplace2x2
  //Verification of the solver for 2x2 linear system [Ax = b]
  std::ofstream verification_Laplace2x2;
  verification_Laplace2x2.open("verification_Laplace2x2.csv", std::ios::out);
  {
  // creates manufactured matrix
  double A[4] = {0.0, 0.0, 0.0, 0.0};
  ManufacturedCoefficient::HilbertMatrix2x2(A);

  // creates manufactured solution
  double x[2] = {0.0, 0.0};
  ManufacturedSolution::Vector1x2(x);

  // calculates manufactured rhs
  double b[2] = {0.0, 0.0};
  b[0] = A[0]*x[0] + A[1]*x[1];
  b[1] = A[2]*x[0] + A[3]*x[1];

  // calculates the numerical solution
  double num_x[2] = {0.0, 0.0};
  Solver::Laplace2x2(A, b);
  num_x[0] = b[0];
  num_x[1] = b[1];

  // compares numx & x
  double err(0.0);
  err = x[0]-num_x[0] + x[1]-num_x[1];

  // writes Output
  verification_Laplace2x2 << err;
  }
  // ---

  // ---
  // Laplace3x3
  //Verification of the solver for 3x3 linear system [Ax = b]
  std::ofstream verification_Laplace3x3;
  verification_Laplace3x3.open("verification_Laplace3x3.csv", std::ios::out);
  {
  // creates manufactured matrix
  double A[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  ManufacturedCoefficient::HilbertMatrix3x3(A);

  // creates manufactured solution
  double x[3] = {0.0, 0.0, 0.0};
  ManufacturedSolution::Vector1x3(x);

  // calculates manufactured rhs
  double b[3] = {0.0, 0.0, 0.0};
  b[0] = A[0]*x[0] + A[1]*x[1] + A[2]*x[2];
  b[1] = A[3]*x[0] + A[4]*x[1] + A[5]*x[2];
  b[2] = A[6]*x[0] + A[7]*x[1] + A[8]*x[2];

  // calculates the numerical solution
  double num_x[3] = {0.0, 0.0, 0.0};
  Solver::Laplace3x3(A, b);
  num_x[0] = b[0];
  num_x[1] = b[1];
  num_x[2] = b[2];

  // compares num_x & x
  double err(0.0);
  err = x[0]-num_x[0] + x[1]-num_x[1] + x[2]-num_x[2];

  // writes Output
  verification_Laplace3x3 << err;
  }
  // ---

  // ---
  // Laplace
  //Verification of the solver for NxN linear system [Ax = b]
  std::ofstream verification_Laplace;
  verification_Laplace.open("verification_Laplace.csv", std::ios::out);
  {
    // creates manufactured matrix
    int N = Matrix_dimension_Laplace;
    double A[N*N];
    ManufacturedCoefficient::HilbertMatrix(N, A);

    // creates manufactured solutions
    double x[N];
    ManufacturedSolution::Vector1xN(N, x);

    // calculates manufactured rhs
    double b[N];
    for (int i = 0; i < N; i++) {
      b[i] = 0.0;
      for (int j = 0; j < N; j++) {
        b[i] += A[i*N + j]*x[j];
      }
    }

    // calculates the numerical solution
    double num_x[N];
    Solver::Laplace(N, A, b);
    for (int i = 0; i < N; i++) {
      num_x[i] = b[i];
    }

    // compare numerical solution with manufactured solutions
    double err(0.0);
    for (int i = 0; i < N; i++) {
      err += x[i] - num_x[i];
    }

  // writes Output
  verification_Laplace << err;
  }
  // ---
}

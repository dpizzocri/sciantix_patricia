//////////////////////////////////////////////////////////////////////////////////////
//       _______.  ______  __       ___      .__   __. .___________. __  ___   ___  //
//      /       | /      ||  |     /   \     |  \ |  | |           ||  | \  \ /  /  //
//     |   (----`|  ,----'|  |    /  ^  \    |   \|  | `---|  |----`|  |  \  V  /   //
//      \   \    |  |     |  |   /  /_\  \   |  . `  |     |  |     |  |   >   <    //
//  .----)   |   |  `----.|  |  /  _____  \  |  |\   |     |  |     |  |  /  .  \   //
//  |_______/     \______||__| /__/     \__\ |__| \__|     |__|     |__| /__/ \__\  //
//                                                                                  //
//  Originally developed by D. Pizzocri & T. Barani                                 //
//                                                                                  //
//  Version: 2.0                                                                    //
//  Year: 2022                                                                      //
//  Authors: D. Pizzocri, G. Zullo.                                                 //
//                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////

#ifndef SOLVER_h
#define SOLVER_h

#include <vector>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>

#include "InputVariable.h"

/// Derived class for the SCIANTIX solvers. They are communicated with models within the Simulation class.

class Solver : public InputVariable
{
  public:

    double Integrator(double initial_value, double parameter, double increment)
    {
      /// Solver for the ODE [y' = + S]
      // parameter = source term
      return initial_value + parameter * increment;
    }

    double LimitedGrowth(double initial_value, std::vector<double> parameter, double increment)
    {
      /// Solver for the ODE [y' = k / y + S]
      // parameter[0] = growth rate
      // parameter[1] = source term
      return 0.5 * ((initial_value + parameter[1] * increment) + sqrt(pow(initial_value + parameter[1] * increment, 2) + 4.0 * parameter[0] * increment));
    }

    //double Decay(double initial_condition, std::vector<double> parameter, double increment)
    double Decay(double initial_condition, double decay_rate, double source_term, double increment)
    {
      /// Solver for the ODE [y' = - L y + S]
      /// 1nd parameter = decay rate
      /// 2st parameter = source
      return (initial_condition + source_term * increment) / (1.0 + decay_rate * increment);
    }

    double BinaryInteraction(double initial_condition, double interaction_coefficient, double increment)
    /// Solver for the ODE [y' = -k y**2]
    {
      if(increment == 0.0)
        return initial_condition;
      else
        return initial_condition = 0.25 * (sqrt(1 + 8 * initial_condition * increment) - 1) / increment;
    }

    double SpectralDiffusion(double* initial_condition, std::vector<double> parameter, double increment)
    {
      /// Solver for the spatially averaged solution of the PDE [dy/dt = D div grad y + S - L y]
      /// We apply a spectral approach in space, projecting the equation on the eigenfunctions of the laplacian operator.
      /// We use the first order backward Euler solver in time.
      /// The number of terms in the expansion, N, is fixed a priori.

      // Parameters
      // 0) N_modes
      // 1) D
      // 2) r
      // 3) yF
      // 4) loss rate

      unsigned short int n(0);
      unsigned short int np1(1);

      double diffusion_rate_coeff(0.0);
      double diffusion_rate(0.0);
      double source_rate_coeff(0.0);
      double source_rate(0.0);
      double projection_coeff(0.0);
      double solution(0.0);

      diffusion_rate_coeff = pow(M_PI, 2) * parameter.at(1) / pow(parameter.at(2), 2);
      projection_coeff = - 2.0 * sqrt(2.0 / M_PI);
      source_rate_coeff = projection_coeff * parameter.at(3);

      for (n = 0; n < parameter.at(0); n++)
      {
        np1 = n + 1;
        const double n_coeff = pow(- 1.0, np1) / np1;

        diffusion_rate = diffusion_rate_coeff * pow(np1, 2) + parameter.at(4);
        source_rate = source_rate_coeff * n_coeff;

        initial_condition[n] = Solver::Decay(initial_condition[n], diffusion_rate, source_rate, increment);

        solution += projection_coeff * n_coeff * initial_condition[n] / ((4./3.) * M_PI);
      }

      return solution;
    }

    double dotProduct1D(double u[], double v[], int n)
    {
      /// Function to compute the dot product between two arrays (v and u) of size n
      double result = 0.0;
      for (int i = 0; i < n; ++i)
        result += u[i]*v[i];
      return result;
    }

    void dotProduct2D(double A[], double v[], int n_rows, int n_col, double result[])
    {
      /// Function to compute the dot product between a matrix and an array
      double a[n_col] = {};
      for (int i = 0; i < n_rows; ++i)
      {
        // create a vector from the i-th row of A
        for(int j = 0; j < n_col; ++j)
        {
          a[j] = A[i*n_col + j];
        }
        result[i] = dotProduct1D(a, v, n_col);
      }
    }

    void SpectralDiffusionNonEquilibrium(double& gas_solution, double& gas_bubble, double* initial_condition_gas_solution, double* initial_condition_gas_bubble, std::vector<double> parameter, double increment)
    {
      /// SpectralDiffusionNonEquilibrium
      /// Solver for the spatially averaged solution of the systems of PDEs:
      /// |dy1/dt = D div grad y1 - gy1 + by2 + S1 - Ly1
      /// |dy2/dt = 0             + gy1 - by2 + S2 - Ly2
      /// We apply a spectral approach in space, projecting the equation on the eigenfunctions of the laplacian operator.
      /// We use the first order backward Euler solver in time.
      /// The number of terms in the expansion, N, is fixed a priori.
      // ------------------------------------
      // parameter --> number of modes
      //               diffusion_coefficient (D)
      //               resolution_rate (b)
      //               trapping_rate (g)
      //               decay rate (L)
      //               domain_radius 
      //               source_term 
      //               source_term_bubbles

      unsigned short int n(0);
      unsigned short int np1(1);

      double diffusion_rate_coeff(0.0);
      double diffusion_rate(0.0);
      double source_rate_coeff_solution(0.0);
      double source_rate_coeff_bubbles(0.0);
      double source_rate_solution(0.0);
      double source_rate_bubble(0.0);
      double projection_coeff(0.0);
      double gas_solution_solution(0.);
      double gas_bubble_solution(0.);
      double coeff_matrix[4];
      double initial_conditions[2];

      
      diffusion_rate_coeff = pow(M_PI, 2) * parameter.at(1) / pow(parameter.at(5), 2); // pi^2 * D / a^2
      projection_coeff = - 2.0 * sqrt(2.0 / M_PI);
      source_rate_coeff_solution = projection_coeff * parameter.at(6); // - 2 sqrt(2/pi) * S1
      source_rate_coeff_bubbles  = projection_coeff * parameter.at(7); // - 2 sqrt(2/pi) * S2

      for (n = 0; n < parameter.at(0); n++)
      {
        np1 = n + 1;
        const double n_coeff = pow(- 1.0, np1) / np1;

        diffusion_rate = diffusion_rate_coeff * pow(np1, 2); // pi^2 * D * n^2 / a^2
        source_rate_solution = source_rate_coeff_solution * n_coeff; // - 2 sqrt(2/pi) * S * (-1)^n/n
        source_rate_bubble   = source_rate_coeff_bubbles  * n_coeff;

        coeff_matrix[0] = 1.0 + ( diffusion_rate + parameter.at(3) + parameter.at(4)) * increment; // 1 + (pi^2 * D * n^2 / a^2 + g + L) dt
        coeff_matrix[1] = - parameter.at(2) * increment; // - b
        coeff_matrix[2] = - parameter.at(3) * increment; // - g
        coeff_matrix[3] = 1.0 + (parameter.at(2) + parameter.at(4)) * increment; // 1 + (b + L) dt
        initial_conditions[0] = initial_condition_gas_solution[n] + source_rate_solution * increment;
        initial_conditions[1] = initial_condition_gas_bubble[n]   + source_rate_bubble   * increment;

        Solver::Laplace2x2(coeff_matrix, initial_conditions);

        initial_condition_gas_solution[n] = initial_conditions[0];
        initial_condition_gas_bubble[n] = initial_conditions[1];

        gas_solution_solution  += projection_coeff * n_coeff * initial_conditions[0] / ((4./3.) * M_PI );
        gas_bubble_solution    += projection_coeff * n_coeff * initial_conditions[1] / ((4./3.) * M_PI );
      }
      gas_solution = gas_solution_solution;
      gas_bubble   = gas_bubble_solution;
    }

    void Laplace2x2(double A[], double b[])
    {
      /// Laplace 2x2
      /// The function solve a system of two linear equations according to Cramer method.
      double detX(0.0), detY(0.0);
      double detA = A[0]*A[3] - A[1]*A[2];

      if (detA != 0.0)
      {
        detX = b[0]*A[3] - b[1]*A[1];
        detY = b[1]*A[0] - b[0]*A[2];
        b[0] = detX / detA;
        b[1] = detY / detA;
      }
    }

    Solver()  {}
    ~Solver() {}
};

#endif

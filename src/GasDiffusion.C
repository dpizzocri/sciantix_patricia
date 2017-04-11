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

#include <iostream>
using namespace std;
#include "GasDiffusion.h"

double GasDiffusion( )
{
  const unsigned short int N(5);
  const double gas_grain_initial(0.0);
  static std::vector<double> gas_grain_modes(N, gas_grain_initial);
  double diffusion_coefficient(1.0);
  // int option(0);
  double grain_radius(1.0);
  double source_term(15.0);
  double time_step(pow(10.0, 2));
  double gas_grain_concentration(gas_grain_initial);
  
  // double diffusion_coefficient = GasDiffusionCoefficient(T, fission_rate, option);
  
  for(int i=0; i<N; i++)
	  {
  		cout << "initial_condition_before[" << i << "] = " << gas_grain_modes[i] << endl;
	  }
  
  gas_grain_concentration = Solver::SpectralDiffusion(gas_grain_modes, N, diffusion_coefficient, grain_radius, source_term, time_step);
  
  cout << "N = " << N << endl;
  cout << "diffusion_coefficient = " << diffusion_coefficient << endl;
  cout << "grain_radius = " << grain_radius << endl;
  cout << "source_term = " << source_term << endl;
  cout << "time_step = " << time_step << endl;
  cout << "The asymptotic (high time step) gas concentration inside the grain is: " << gas_grain_concentration;
  
  std::ofstream prova;
  prova.open("prova.txt",std::ios::out);
  prova << gas_grain_concentration;
  prova.close();
  
  return gas_grain_concentration;
}

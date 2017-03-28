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

#include "GasDiffusion.h"

void GasDiffusion( )
{
  const unsigned short int N(10);
  const double gas_grain_initial(0.0);
  static std::vector<double> gas_grain_modes(N,gas_grain_initial);
  double diffusion_coefficient(0.0);
  double grain_radius(0.0);
}

///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.4                         //
//  Year   : 2019                        //
//  Authors: D. Pizzocri and T. Barani   //
//           G. Zullo, F. Rotea          //
///////////////////////////////////////////

/// GrainGrowth
/// This model describes grain growth as a temperature controlled mechanism.
/// [1] Ainscough et al., Journal of Nuclear Materials, 49 (1973) 117-128
/// [2] Olsen, Transactions of SMIRT, Analysis of Reactor fuel and cladding
/// materials, Vol. C, North Holland, Amsterdam, NL, (1979), p. C1/9 (1 - 10)
/// [3] Botazzoli, PhD Thesis, Politecnico di Milano (2011)

#include "GrainGrowth.h"

void GrainGrowth( )
{
  const double temperature = Temperature[1];
  const double burnup = Burn_up[1];
  double grain_diameter = Grain_radius[0] * 2.0; // (m)

  double grain_boundary_mobility(0.0); // (m^4/s)
  double grain_diameter_limit(0.0); // (m)
  double burnup_factor(0.0); // (/)
  double source_term(0.0);

  switch (igrain_growth)
  {
    case 0 :
			// no grain growth
      Grain_radius[1] = grain_diameter / 2.0;
      break;

    case 1 :
    // from [1]
    // The grain growth kinetic is described by Ainscough et al.,
    // by means of the following equation:
    // dD/dt = k * (1/D - f(BU)/Dm)
    // where
    // D = grain size (um)
    // k, the rate constant, is
    // k = 5.24e+7 * exp(-2.67e+5 / (R*T)) (um^2/h)
    // R = 8.314 (J/K mol)
    // T = temperature (K)
    // Dm, the limiting grain size, is a function of temperature such that
    // Dm = 2.23e+3 * exp(-7620 / T) (um)
    // f(Bu) = 1 + 0.002e-03 * Burnup (GWd/teU)
    // In detail, the presence of this last term in the rate equation
    // allows to take into account the effect of irradiation on grain growth
    // (consisting in the increasing retarding effect of fission products)
    {
      grain_boundary_mobility = 5.24e+07 * exp(-32114.5 / temperature) / (pow(um_m, 2) * s_h);
      grain_diameter_limit = 2.23e+03 * exp(-7620.0 / temperature) / um_m;
      burnup_factor = 1.0 + 2 * burnup / U_UO2;
      source_term = - (grain_boundary_mobility * burnup_factor) / grain_diameter_limit;
      
      if(grain_diameter < grain_diameter_limit / burnup_factor)
      {
        grain_diameter = Solver::LimitedGrowth(grain_diameter, grain_boundary_mobility, source_term, dTime_s);
        Grain_radius[1] = grain_diameter / 2.0;
      }
      else
        Grain_radius[1] = Grain_radius[0];

      break;
    }

    default :
      ErrorMessages::Switch("GrainGrowth", "igrain_growth", igrain_growth);
      break;
  }
}

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

/// GasDiffusionCoefficient
/// This function contains a choice among possible
/// expressions for the diffusion coefficient of fission gas
/// inside the fuel grain.
/// [1] J.A.Turnbull et al., The diffusion coefficient for fission gas atomsin uranium dioxide.
/// In Proc. of the International Working Group on Water Reactor Fuel Performance and Technology (IWGFPT–32), Preston, UK, Sep 18–22, 1988
/// [2] Matzke, Radiation Effects, 53 (1980), 219-242

#include "GasDiffusionCoefficient.h"

double GasDiffusionCoefficient(double temperature, double fission_rate)
{
  double diffusion_coefficient(0.0); // (m2/s)

  switch(igas_diffusion_coefficient)
  {
    case 0 :
         // constant value for trial
      diffusion_coefficient = 0.0e+00;
      break;

    case 1 :
      {
        // from [1]
        double d1 = 7.6e-10 * exp(- 4.86e-19 / (Cons_bolt * temperature));
        double d2 = 4.0 * 1.41e-25 * sqrt(fission_rate) * exp(- 1.91e-19 / (Cons_bolt * temperature));
        double d3 = 2.0e-40 * fission_rate;

        diffusion_coefficient = d1 + d2 + d3;
        break;
      }

    case 2 :
      // effective diffusion coefficient from [2]
      diffusion_coefficient = 5.0e-08 * exp(- 40262.0 / temperature);
      break;


    default :
      ErrorMessages::Switch("GasDiffusionCoefficient", "igas_diffusion_coefficient", igas_diffusion_coefficient);
      break;
  }

  return diffusion_coefficient;
}

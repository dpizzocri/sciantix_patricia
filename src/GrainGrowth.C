///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.0                         //
//  Year   : 2018                        //
//  Authors: D. Pizzocri and T. Barani   //
//                                       //
///////////////////////////////////////////

/// GrainGrowth
/// This model describes grain growth as a temperature controlled mechanism.
/// The grain boundary mobility is derived from the data in Ref [1].
/// Botazzoli corrected the mobility [2], including the stereologic
/// correction due to Mendelson [3].
/// [1] Ainscough et al., Journal of Nuclear Materials, 49 (1973) 117-128
/// [2] Botazzoli, 2001, PhD Thesis, Politecnico di Milano
/// [3] Mendelson, Journal of the American Ceramic Society, 52 (1969) 443-446

#include "GrainGrowth.h"

void GrainGrowth( )
{
  const double temperature = Temperature[1];
  const double um_m = 1.0e+06; // (um/m)

  const double grain_boundary_mobility = 3.1347e+14 * exp(-46524.0 / temperature);
  const double grain_diameter_limit = 3345.0 * exp(-7620.0 / temperature);

  double grain_diameter_um = Grain_radius[0] * (2.0 * um_m);
  double dgrain_diameter_um;

  if (grain_diameter_um < grain_diameter_limit)
  {
    dgrain_diameter_um = grain_boundary_mobility / (4.0 * pow(grain_diameter_um, 3))  * dTime_s / s_h;
    grain_diameter_um += dgrain_diameter_um;

    if (grain_diameter_um > grain_diameter_limit)
    {
      grain_diameter_um = grain_diameter_limit;
      dgrain_diameter_um = grain_diameter_limit - grain_diameter_um;
	  }
  }

  Grain_radius[1] = grain_diameter_um / (2.0 * um_m);
}

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

/// Initialization
/// This routine initializes Sciantix internal variables with
/// initial conditions/interface variables

#include "Initialization.h"

void Initialization( )
{
  Sciantix_history[0] = Temperature_input[0];
  Sciantix_history[1] = Temperature_input[0];
  Sciantix_history[2] = Fissionrate_input[0];
  Sciantix_history[3] = Fissionrate_input[0];
  Sciantix_history[4] = Hydrostaticstress_input[0];
  Sciantix_history[5] = Hydrostaticstress_input[0];
  Sciantix_history[6] = 0.0;

  Sciantix_variables[7] = 0.0;
  Sciantix_variables[8] = 0.0;
  Sciantix_variables[9] = 0.0;
  Sciantix_variables[10] = 4.0e+13;
  Sciantix_variables[11] = 0.0;
  Sciantix_variables[12] = 0.0;
  Sciantix_variables[13] = 1.0e-08;
  Sciantix_variables[14] = 0.0;
  Sciantix_variables[15] = 0.0;
  Sciantix_variables[16] = 0.0;
  Sciantix_variables[17] = 0.5;
  Sciantix_variables[18] = 0.0;
  Sciantix_variables[19] = 1.0;
  Sciantix_variables[20] = 0.0;
  Sciantix_variables[21] = 0.0;

  double Mmol_HM = 0.01 * (
                Sciantix_variables[61] * 234.04 + Sciantix_variables[62] * 235.04 + Sciantix_variables[63] * 236.05 + Sciantix_variables[64] * 237.05 + Sciantix_variables[65] * 238.05 +
                Sciantix_variables[66] * 237.04 + Sciantix_variables[67] * 238.05 + Sciantix_variables[68] * 239.05 +
                Sciantix_variables[69] * 238.05 + Sciantix_variables[70] * 239.05 + Sciantix_variables[71] * 240.05 + Sciantix_variables[72] * 241.06 + Sciantix_variables[72] * 242.06 + Sciantix_variables[73] * 243.06 +
                Sciantix_variables[75] * 241.06 + Sciantix_variables[76] * 242.06 + Sciantix_variables[77] * 242.06 + Sciantix_variables[78] * 243.06 + Sciantix_variables[78] * 244.06 +
                Sciantix_variables[80] * 242.06 + Sciantix_variables[81] * 243.06 + Sciantix_variables[82] * 244.06 + Sciantix_variables[83] * 245.07
                );

  double HM_HMO2 = Mmol_HM / (Mmol_HM + 32.0); // Heavy Metals over Heavy Metal Oxides in mass

  double HM_m3 = 1000. * Sciantix_variables[84] * 6.022e+23 / (Mmol_HM + 32.0);

  for (int i = 24; i < 61; i++)
    Sciantix_variables[i] = 0.0;

  for (int j = 61; j < 83; j++)
    Sciantix_variables[j] *= 0.01 * HM_m3;

  Sciantix_variables[23] = HM_m3 * Sciantix_variables[85];

//  CrossSectionChooser( );
}

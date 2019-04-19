///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.4                         //
//  Year   : 2019                        //
//  Authors: D. Pizzocri and T. Barani   //
//           L. Cognini                  //
///////////////////////////////////////////

/// OutputWriting
/// This routine writes the output file

#include "OutputWriting.h"

void OutputWriting( )
{
  if (Time_step_number == 0)
  {
    Output_file << "Time (h)" << "\t"
                << "Temperature (K)" << "\t"
                << "Fission rate (fiss/m3-s)" << "\t"
                << "Hydrostatic stress (MPa)" << "\t"
                << "Grain radius (m)" << "\t"
                << "Gas produced (at/m3)" << "\t"
                << "Gas in grains (at/m3)" << "\t"
                << "Gas in intra-granular solution (at/m3)" << "\t"
                << "Gas in intra-granular bubbles (at/m3)" << "\t"
                << "Gas at grain boundaries (at/m3)" << "\t"
                << "Gas released (at/m3)" << "\t"
                << "Intra-granular bubble density (bubble/m3)" << "\t"
                << "Intra-granular bubble radius (m)" << "\t"
                << "Intra-granular gas swelling (/)" << "\t"
                << "Inter-granular bubble concentration (bubble/m2)" << "\t"
                << "Inter-granular atoms per bubble (at/bubble)" << "\t"
                << "Inter-granular vacancies per bubble (vac/bubble)" << "\t"
                << "Inter-granular bubble radius (m)" << "\t"
                << "Inter-granular bubble area (m2)" << "\t"
                << "Inter-granular bubble volume (m3)" << "\t"
                << "Inter-granular fractional coverage (/)" << "\t"
                << "Inter-granular saturation fractional coverage (/)" << "\t"
                << "Inter-granular gas swelling (/)" << "\t"
                << "Inter-granular fractional intactness (/)" << "\t"
                << "Burnup (GWd/tUO2)" << "\t"
                << "Effective burnup (GWd/tUO2)" << "\t"
                << "He4 (at/m3)" << "\t"
                << "O16 (at/m3)" << "\t"
                << "Tl207 (at/m3)" << "\t"
                << "Tl208 (at/m3)" << "\t"
                << "Pb206 (at/m3)" << "\t"
                << "Pb207 (at/m3)" << "\t"
                << "Pb208 (at/m3)" << "\t"
                << "Pb210 (at/m3)" << "\t"
                << "Pb211 (at/m3)" << "\t"
                << "Pb212 (at/m3)" << "\t"
                << "Pb214 (at/m3)" << "\t"
                << "Bi210 (at/m3)" << "\t"
                << "Bi211 (at/m3)" << "\t"
                << "Bi212 (at/m3)" << "\t"
                << "Bi214 (at/m3)" << "\t"
                << "Po210 (at/m3)" << "\t"
                << "Po212 (at/m3)" << "\t"
                << "Po214 (at/m3)" << "\t"
                << "Po215 (at/m3)" << "\t"
                << "Po216 (at/m3)" << "\t"
                << "Po218 (at/m3)" << "\t"
                << "Rn219 (at/m3)" << "\t"
                << "Rn220 (at/m3)" << "\t"
                << "Rn222 (at/m3)" << "\t"
                << "Fr223 (at/m3)" << "\t"
                << "Ra223 (at/m3)" << "\t"
                << "Ra224 (at/m3)" << "\t"
                << "Ra226 (at/m3)" << "\t"
                << "Ra228 (at/m3)" << "\t"
                << "Ac227 (at/m3)" << "\t"
                << "Ac228 (at/m3)" << "\t"
                << "Th227 (at/m3)" << "\t"
                << "Th228 (at/m3)" << "\t"
                << "Th230 (at/m3)" << "\t"
                << "Th231 (at/m3)" << "\t"
                << "Th232 (at/m3)" << "\t"
                << "Th234 (at/m3)" << "\t"
                << "Pa231 (at/m3)" << "\t"
                << "Pa234 (at/m3)" << "\t"
                << "U234 (at/m3)" << "\t"
                << "U235 (at/m3)" << "\t"
                << "U236 (at/m3)" << "\t"
                << "U237 (at/m3)" << "\t"
                << "U238 (at/m3)" << "\t"
                << "Np237 (at/m3)" << "\t"
                << "Np238 (at/m3)" << "\t"
                << "Np239 (at/m3)" << "\t"
                << "Pu238 (at/m3)" << "\t"
                << "Pu239 (at/m3)" << "\t"
                << "Pu240 (at/m3)" << "\t"
                << "Pu241 (at/m3)" << "\t"
                << "Pu242 (at/m3)" << "\t"
                << "Pu243 (at/m3)" << "\t"
                << "Am241 (at/m3)" << "\t"
                << "Am242 (at/m3)" << "\t"
                << "Am242m (at/m3)" << "\t"
                << "Am243 (at/m3)" << "\t"
                << "Am244 (at/m3)" << "\t"
                << "Cm242 (at/m3)" << "\t"
                << "Cm243 (at/m3)" << "\t"
                << "Cm244 (at/m3)" << "\t"
                << "Cm245 (at/m3)" << "\t"
                << "Fuel density (kg/m3)" << "\t"
                << "Oxygen-to-metal ratio (/)" << "\t"
                << "Helium produced (at/m3)" << "\t"
                << "Helium in grains (at/m3)" << "\t"
                << "Helium in intra-granular solution (at/m3)" << "\t"
                << "Helium in intra-granular bubbles (at/m3)" << "\t"
                << "Helium at grain boundaries (at/m3)" << "\t"
                << "Helium released (at/m3)" << "\n";
  }

if (Time_step_number%1 == 0) {

  Output_file << Time_h;

  const int index_history_max(3);
  for (int index_history = 0; index_history < index_history_max; index_history++)
    Output_file << "\t" << Sciantix_history[2*index_history+1];

  const int index_variables_max(92);
  for (int index_variables = 0; index_variables < index_variables_max; index_variables++)
    Output_file << "\t" << Sciantix_variables[index_variables];

  Output_file << "\n";
}


}

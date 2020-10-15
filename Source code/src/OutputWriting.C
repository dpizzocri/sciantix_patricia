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
                << "Effective burnup (GWd/tUO2)" << "\n";
  }

if (Time_step_number%1 == 0) {

  Output_file << Time_h;

  const int index_history_max(3);
  for (int index_history = 0; index_history < index_history_max; index_history++)
    Output_file << "\t" << Sciantix_history[2*index_history+1];

  const int index_variables_max(22);
  for (int index_variables = 0; index_variables < index_variables_max; index_variables++)
    Output_file << "\t" << Sciantix_variables[index_variables];

  Output_file << "\n";
}


}

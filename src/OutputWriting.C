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

/// OutputWriting
/// This routine writes the output file

#include "OutputWriting.h"

void OutputWriting( )
{
  if (Time_step_number == 0)
    Output << "Time (h)" << ","
           << "Temperature (K)" << ","
           << "Fission rate (fiss/m3-s)" << ","
           << "Hydrostatic stress (MPa)" << ","
           << "Grain radius (m)" << ","
           << "Gas produced (at/m3)" << ","
           << "Gas in grains (at/m3)" << ","
           << "Gas in intra-granular solution (at/m3)" << ","
           << "Gas in intra-granular bubbles (at/m3)" << ","
           << "Gas at grain boundaries (at/m3)" << ","
           << "Intra-granular bubble density (bubble/m3)" << ","
           << "Intra-granular bubble radius (m)" << ","
           << "Intra-granular atoms per bubble (at/bubble)" << std::endl;

  Output << Time_h << ","
         << Temperature[1] << ","
         << Fissionrate[1] << ","
         << Hydrostaticstress[1] << ","
         << Grain_radius[1] << ","
         << Gas_produced[1] << ","
         << Gas_grain[1] << ","
         << Gas_grain_solution[1] << ","
         << Gas_grain_bubbles[1] << ","
         << Gas_boundary[1] << ","
         << Intragranular_bubble_concentration[1] << ","
         << Intragranular_bubble_radius[1] << ","
         << Atoms_per_bubble[1] << std::endl;
}

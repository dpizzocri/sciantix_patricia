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
  switch(iformat_output)
  {
  		case 0 :
  		{
  			// output.csv
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
           			<< "Intra-granular atoms per bubble (at/bubble)" << ","
           			<< "Burnup (GWd/tU)" << ","
           			<< "Effective burnup (GWd/tU)" << std::endl;

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
         			<< Atoms_per_bubble[1] << ","
         			<< Burn_up[1] << ","
         			<< Effective_burn_up[1] << std::endl;
         	break;
		}

    	case 1 :
    	{
    		// output.txt
    		if (Time_step_number == 0)
    		Output << "Time (h)" << "\t"
           			<< "Temperature (K)" << "\t"
           			<< "Fission rate (fiss/m3-s)" << "\t"
           			<< "Hydrostatic stress (MPa)" << "\t"
           			<< "Grain radius (m)" << "\t"
           			<< "Gas produced (at/m3)" << "\t"
           			<< "Gas in grains (at/m3)" << "\t"
           			<< "Gas in intra-granular solution (at/m3)" << "\t"
           			<< "Gas in intra-granular bubbles (at/m3)" << "\t"
           			<< "Gas at grain boundaries (at/m3)" << "\t"
           			<< "Intra-granular bubble density (bubble/m3)" << "\t"
           			<< "Intra-granular bubble radius (m)" << "\t"
           			<< "Intra-granular atoms per bubble (at/bubble)" << "\t"
           			<< "Burnup (GWd/tU)" << "\t"
           			<< "Effective burnup (GWd/tU)" <<std::endl;

  			Output << Time_h << "\t"
         			<< Temperature[1] << "\t"
         			<< Fissionrate[1] << "\t"
         			<< Hydrostaticstress[1] << "\t"
         			<< Grain_radius[1] << "\t"
         			<< Gas_produced[1] << "\t"
         			<< Gas_grain[1] << "\t"
         			<< Gas_grain_solution[1] << "\t"
         			<< Gas_grain_bubbles[1] << "\t"
         			<< Gas_boundary[1] << "\t"
         			<< Intragranular_bubble_concentration[1] << "\t"
         			<< Intragranular_bubble_radius[1] << "\t"
         			<< Atoms_per_bubble[1] << "\t"
         			<< Burn_up[1] << "\t"
         			<< Effective_burn_up[1] << std::endl;
         	break;
		}

    	default :
          ErrorMessages::Switch("OutputWriting", "iformat_output", iformat_output);
          break;
  }

}

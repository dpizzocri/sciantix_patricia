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

/// IntraGranularBubbleEvolution
/// This function contains a choice among possible
/// expressions for the bubble number density and
/// the bubble radius inside a fuel grain.
/// [1] White, Tucker, Journal of Nuclear Materials, 118 (1983), 1-38
/// [2] Olander, Wongsawaeng, Journal of Nuclear Materials, 354 (2006), 94-109

#include "IntraGranularBubbleEvolution.h"

void IntraGranularBubbleEvolution( )
{
	switch(iintra_bubble_evolution)
	{
		case 0 :
			// constant values for trial
			Intragranular_bubble_concentration[1] = 7.0e+23;
			Intragranular_bubble_radius[1] = 1.0e-9;
			Atoms_per_bubble[1] = Gas_grain_bubbles[1] / Intragranular_bubble_concentration[1];
			break;

		case 1 :
			// from [1]
			Intragranular_bubble_concentration[1] = (1.52e+27 / Temperature[0]) - 3.3e+23;
			Intragranular_bubble_radius[1] = 5.0e-10 * (1.0 + 106.0 * exp(- 0.75 / (Cons_bolt * Temperature[0])));
			Atoms_per_bubble[1] = Gas_grain_bubbles[1] / Intragranular_bubble_concentration[1];
			break;

		case 2 :
        {
			// from [2]
			if (Intragranular_bubble_concentration[0] > 0.0)
	  		  Atoms_per_bubble[0] = Gas_grain_bubbles[0] / Intragranular_bubble_concentration[0];
			else
              Atoms_per_bubble[0] = 0.0;

            Intragranular_bubble_radius[0] = BubbleRadius(Temperature[0], Atoms_per_bubble[0]);

			double resolution_rate = ResolutionRate(Intragranular_bubble_radius[0], Fissionrate[0]);
			double nucleation_rate = NucleationRate(Fissionrate[0]);

			Intragranular_bubble_concentration[1] = Solver::Decay(Intragranular_bubble_concentration[0], resolution_rate, nucleation_rate, dTime_s);
			if (Intragranular_bubble_concentration[1] > 0.0)
	  		  Atoms_per_bubble[1] = Gas_grain_bubbles[1] / Intragranular_bubble_concentration[1];
			else
              Atoms_per_bubble[1] = 0.0;

            Intragranular_bubble_radius[1] = BubbleRadius(Temperature[1], Atoms_per_bubble[1]);

			break;
        }

        default :
          ErrorMessages::Switch("IntraGranularBubbleEvolution", "iintra_bubble_evolution", iintra_bubble_evolution);
          break;
	}
}

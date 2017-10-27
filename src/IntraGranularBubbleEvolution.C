//////////////////////////////////////////////////
//                                              //
//           S C I A N T I X                    //
//           ---------------                    //
//                                              //
//  Version: 0.1                                //
//  Year   : 2016                               //
//  Authors: D. Pizzocri, T. Barani, A. Magni   //
//                                              //
//////////////////////////////////////////////////

/// IntraGranularBubbleEvolution
/// This function contains a choice among possible
/// models with the aim of evaluating the behaviour
/// of intra-granular bubbles, in terms of
/// bubble number density and bubble radius.
/// The bubble coarsening model is built adapting the model from [3].
/// [1] White, Tucker, Journal of Nuclear Materials, 118 (1983), 1-38
/// [2] Olander, Wongsawaeng, Journal of Nuclear Materials, 354 (2006), 94-109
/// [3] Speight, Beere, Metal Science, 9 (1975), 190-191

#include "IntraGranularBubbleEvolution.h"
#include <iostream>

void IntraGranularBubbleEvolution( )
{
	switch(iintra_bubble_evolution)
	{
		case 0 :
			// constant values for trial
			Intragranular_bubble_concentration[1] = 7.0e+23;
			Intragranular_bubble_radius[1] = 1.0e-9;
			Intragranular_atoms_per_bubble[1] = Gas_grain_bubbles[1] / Intragranular_bubble_concentration[1];
			break;

		case 1 :
			// from [1]
			Intragranular_bubble_concentration[1] = (1.52e+27 / Temperature[0]) - 3.3e+23;
			Intragranular_bubble_radius[1] = 5.0e-10 * (1.0 + 106.0 * exp(- 0.75 / (Cons_bolt * Temperature[0])));
			Intragranular_atoms_per_bubble[1] = Gas_grain_bubbles[1] / Intragranular_bubble_concentration[1];
			break;

		case 2 :
        {
			// from [2]

			double resolution_rate = ResolutionRate(Intragranular_bubble_radius[0], Fissionrate[0]);
			double nucleation_rate = NucleationRate(Fissionrate[0]);

			Intragranular_bubble_concentration[1] = Solver::Decay(Intragranular_bubble_concentration[0], resolution_rate, nucleation_rate, dTime_s);

			if (Intragranular_bubble_concentration[1] > 0.0)
	  		  Intragranular_atoms_per_bubble[1] = Gas_grain_bubbles[1] / Intragranular_bubble_concentration[1];
			else
              Intragranular_atoms_per_bubble[1] = 0.0;

            Intragranular_bubble_radius[1] = IntraGranularBubbleRadius(Temperature[1], Intragranular_atoms_per_bubble[1]);

			break;
        }

        case 3 :
        {
        	// from [2], extended according to [3]

			double dislocation_influence_radius = DislocationRadiusOfInfluence( );
			Dislocation_density[1] = DislocationDensity(Temperature[1], Burn_up[1]);
			double fraction_of_bubbles_at_dislocations = Dislocation_density[1] * Pi * pow(dislocation_influence_radius, 2);

			double resolution_rate = ResolutionRate(Intragranular_bubble_radius[0], Fissionrate[0]);
			double intragranular_bubble_atomic_radius = IntraGranularBubbleRadius(Temperature[1], Intragranular_atoms_per_bubble_at_dislocations[0]);
			double resolution_rate_bubble_at_dislocations = ResolutionRate(intragranular_bubble_atomic_radius, Fissionrate[0]);
			double nucleation_rate = NucleationRate(Fissionrate[0]);

			Intragranular_bubble_concentration[1] = Solver::Decay(Intragranular_bubble_concentration[0], resolution_rate, (1.0-fraction_of_bubbles_at_dislocations)*nucleation_rate, dTime_s);
			Intragranular_bubble_concentration_at_dislocations[1] = Solver::Decay(Intragranular_bubble_concentration_at_dislocations[0], resolution_rate_bubble_at_dislocations, fraction_of_bubbles_at_dislocations*nucleation_rate, dTime_s);

			if (Intragranular_bubble_concentration[1] > 0.0)
		      Intragranular_atoms_per_bubble[1] = Gas_grain_bubbles[1] / (Intragranular_bubble_concentration[1] + Intragranular_bubble_concentration_at_dislocations[1]);
			else
			  Intragranular_atoms_per_bubble[1] = 0.0;

            if (Intragranular_bubble_concentration_at_dislocations[1] > 0.0)
		      Intragranular_atoms_per_bubble_at_dislocations[1] = Gas_grain_bubbles[1] / (Intragranular_bubble_concentration[1] + Intragranular_bubble_concentration_at_dislocations[1])
			                                      				+ Gas_grain_dislocations[1] / Intragranular_bubble_concentration_at_dislocations[1];
            else
              Intragranular_atoms_per_bubble_at_dislocations[1] = 0.0;

            // Radius of intra-granular bubble related to gas atoms (accounting for previous vacancies contribution for bubbles at dislocations)
            Intragranular_bubble_radius[1] = IntraGranularBubbleRadius(Temperature[1], Intragranular_atoms_per_bubble[1]);
			Intragranular_bubble_radius_at_dislocations[1] = IntraGranularBubbleRadius(Temperature[1], Intragranular_atoms_per_bubble_at_dislocations[1]);
			Intragranular_bubble_volume_at_dislocations[1] = (4.0/3.0) * Pi * pow(Intragranular_bubble_radius_at_dislocations[1],3)
			                                               + Intragranular_vacancies_per_bubble_at_dislocations[0] * Vacancy_volume;
			Intragranular_bubble_radius_at_dislocations[1] = pow(3.0*Intragranular_bubble_volume_at_dislocations[1]/(4.0*Pi),(1.0/3.0));

            if (Intragranular_vacancies_per_bubble_at_dislocations[1] > 0.0)
              Group_bubble_growth[1] = (Cons_bolt * Temperature[1] * Intragranular_bubble_radius_at_dislocations[1] * Intragranular_atoms_per_bubble_at_dislocations[1]) / (2.0 * Vacancy_volume * Surface_tension * Intragranular_vacancies_per_bubble_at_dislocations[1]);
			else
			  Group_bubble_growth[1] = (Cons_bolt * Temperature[1] * Intragranular_bubble_radius_at_dislocations[1]) / (2.0 * Surface_tension * Vacancy_volume);

			// Contribution of vacancies is accounted for bubbles at dislocations
			if (iintragranular_bubble_coarsening)
			{
			  if (Group_bubble_growth[1] > 1.0)
			  {
  			    if (Intragranular_bubble_concentration_at_dislocations[1] > 0.0)
			    {
			  	  double dislocation_length_per_bubble = Dislocation_density[1] / (2.0 * Intragranular_bubble_concentration_at_dislocations[1]);
                  double dislocation_bubble_coverage = Intragranular_bubble_radius_at_dislocations[1] / dislocation_length_per_bubble;
            	  double geometric_factor = (1.0/3.0) - dislocation_bubble_coverage + pow(dislocation_bubble_coverage,2) - (1.0/3.0)*pow(dislocation_bubble_coverage,3);
   			      double vacancy_diffusion_coefficient = sf_diffusion_rate_vacancy * 1.0e-15;
				  double growth_rate = (4.0/3.0) * Pi * dislocation_influence_radius * vacancy_diffusion_coefficient * Intragranular_atoms_per_bubble_at_dislocations[1] / (Vacancy_volume * geometric_factor);
				  double source_factor = pow(Intragranular_bubble_radius_at_dislocations[1],2) + pow(dislocation_influence_radius,2)*(1.0-dislocation_bubble_coverage) / dislocation_bubble_coverage;
				  double source_rate = - 4.0 * Pi * dislocation_influence_radius * vacancy_diffusion_coefficient * Surface_tension * source_factor / (Cons_bolt * Temperature[1] * pow(dislocation_length_per_bubble,3) * geometric_factor);

                  Intragranular_vacancies_per_bubble_at_dislocations[1] = Solver::LimitedGrowth(Intragranular_vacancies_per_bubble_at_dislocations[0], growth_rate, source_rate, dTime_s);

   			      // Hypotesis: bubble at dislocation can absorb a max number of vacancies corresponding to equilibrium, without going out of equilibrium
   			      double equilibrium_vacancies_per_bubble = (Cons_bolt * Temperature[1] * Intragranular_atoms_per_bubble_at_dislocations[1] * pow(dislocation_length_per_bubble,3)) / (3.0 * Vacancy_volume * Surface_tension * source_factor);

				  if (Intragranular_vacancies_per_bubble_at_dislocations[1] > equilibrium_vacancies_per_bubble)
				  	Intragranular_vacancies_per_bubble_at_dislocations[1] = equilibrium_vacancies_per_bubble;

				  // Hypotesis: dislocation can only trap vacancies without re-solving (bubble at dislocation can only grow and can not shrink)
				  if(Intragranular_vacancies_per_bubble_at_dislocations[1] < Intragranular_vacancies_per_bubble_at_dislocations[0])
   			        Intragranular_vacancies_per_bubble_at_dislocations[1] = Intragranular_vacancies_per_bubble_at_dislocations[0];

				}
                else
  			      Intragranular_vacancies_per_bubble_at_dislocations[1] = 0.0;

                // extra-volume contribution due to vacancies is considered
                Intragranular_bubble_volume_at_dislocations[1] += Intragranular_vacancies_per_bubble_at_dislocations[1] * Vacancy_volume;
                Intragranular_bubble_radius_at_dislocations[1] = pow(3.0*Intragranular_bubble_volume_at_dislocations[1]/(4.0*Pi),(1.0/3.0));

                // Update of G
                if (Intragranular_vacancies_per_bubble_at_dislocations[1] > 0.0)
                  Group_bubble_growth[1] = (Cons_bolt * Temperature[1] * Intragranular_bubble_radius_at_dislocations[1] * Intragranular_atoms_per_bubble_at_dislocations[1]) / (2.0 * Vacancy_volume * Surface_tension * Intragranular_vacancies_per_bubble_at_dislocations[1]);

		      }
			}

			break;
		}

        default :
          ErrorMessages::Switch("IntraGranularBubbleEvolution", "iintra_bubble_evolution", iintra_bubble_evolution);
          break;
	}
}

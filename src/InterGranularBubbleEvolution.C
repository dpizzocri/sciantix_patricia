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

/// InterGranularBubbleEvolution
/// This function contains a choice among possible
/// expressions for the bubble number density and
/// the bubble radius at grain boundaries.
/// The model considers one-off nucleation,
/// growth of lenticular bubbles by vacancy absorption
/// and coalescence of bubbles.
/// [1] Pastore et al., NED, 256 (2013) 75-86
/// [2] White, JNM, 325 (2004) 61-77

#include "InterGranularBubbleEvolution.h"

void InterGranularBubbleEvolution( )
{
  // One-off nucleation
  // The bubble concentration is set during Initialization
  Intergranular_bubble_concentration[1] = Intergranular_bubble_concentration[0];

  // Gas is distributed among bubbles
  const double grain_surface_to_volume_ratio = 3.0 / Grain_radius[0];
  Intergranular_atoms_per_bubble[1] = Gas_boundary[1] / (Intergranular_bubble_concentration[1] * grain_surface_to_volume_ratio);

  // Bubble growth
  // Vacancies per bubbles are updated to over/under equilibrium bubble pressure
  const double semidihedral_angle = 50.0 * Pi / 180.0; // (rad) Koo et al., 2000; White, 2004
  const double grain_boundary_thickness(5.0e-10); // (m) Kogai, 1997
  if (Intergranular_bubble_radius[0] <= 0.0)
    // radius is initialized assuming the bubble as a circle of atoms with no vacancies
    // C = 1.46e-10 (m)
    // where C = sqrt(Xenon_volume_in_the_lattice / (pi * grain_boundary_thickness))
  {
    Intergranular_bubble_radius[0] = 1.46e-10*sqrt(Intergranular_atoms_per_bubble[1])/sin(semidihedral_angle);
    Intergranular_bubble_area[0] = Pi*pow(Intergranular_bubble_radius[1]*sin(semidihedral_angle), 2);
  }

  if (Intergranular_atoms_per_bubble[1] > 0.0)
  {
    const double vacancy_diffusion_coefficient = GrainBoundaryVacancyDiffusionCoefficient(Temperature[0]);
    Intergranular_fractional_coverage[0] = Intergranular_bubble_concentration[0] * Intergranular_bubble_area[0];
    const double sink_strength = -0.25*((3.0-Intergranular_fractional_coverage[0])*(1.0-Intergranular_fractional_coverage[0])+2.0*log(Intergranular_fractional_coverage[0])); // (/)
    const double volume_flow_rate = 2.0*Pi*grain_boundary_thickness*vacancy_diffusion_coefficient/sink_strength; // (m3)
    const double growth_rate = volume_flow_rate * Intergranular_atoms_per_bubble[1] / Vacancy_volume;

    const double equilibrium_pressure = 2.0 * Surface_tension / Intergranular_bubble_radius[0] - Hydrostaticstress[0] * M_1; // GZ

    const double equilibrium_term = - volume_flow_rate * equilibrium_pressure / (Cons_bolt * Temperature[0]);
    Intergranular_vacancies_per_bubble[1] = Solver::LimitedGrowth(Intergranular_vacancies_per_bubble[0], growth_rate, equilibrium_term, dTime_s);

    //std::cout << growth_rate << std::endl;
    //std::cout << equilibrium_term << std::endl;
  }
  else
    Intergranular_vacancies_per_bubble[1] = 0.0;

  // Bubble growth (shrink) due to vacancy inflow (outflow), all geometrical quantities are updated
  const double lenticular_shape_factor = 1.0 - 1.5*cos(semidihedral_angle) + 0.5*pow(cos(semidihedral_angle), 3);
  Intergranular_bubble_volume[1] = Intergranular_atoms_per_bubble[1] * Xenon_covolume + Intergranular_vacancies_per_bubble[1] * Vacancy_volume;
  Intergranular_bubble_radius[1] = pow(3.0*Intergranular_bubble_volume[1]/(4.0*Pi*lenticular_shape_factor),1.0/3.0);
  Intergranular_bubble_area[1] = Pi*pow(Intergranular_bubble_radius[1]*sin(semidihedral_angle), 2);

  //std::cout << "dopo vacanze\n";
  //std::cout << Intergranular_bubble_area[0] << std::endl;
  //std::cout << Intergranular_bubble_area[1] << std::endl;
  //std::cout << Intergranular_bubble_area[1] - Intergranular_bubble_area[0] << std::endl;

  // Bubble interconnection decreases the number of bubbles

  const double geometric_coefficient(2.0);
  const double dbubble_area = Intergranular_bubble_area[1] - Intergranular_bubble_area[0];
  Intergranular_bubble_concentration[1] = Solver::BinaryInteraction(Intergranular_bubble_concentration[0], geometric_coefficient, dbubble_area);

  //std::cout << dbubble_area << std::endl;
  //std::cout << Intergranular_bubble_area[1] << std::endl;
  //std::cout << Intergranular_bubble_concentration[1] << std::endl;

  Intergranular_atoms_per_bubble[1] *= Intergranular_bubble_concentration[0] / Intergranular_bubble_concentration[1];
  Intergranular_vacancies_per_bubble[1] *= Intergranular_bubble_concentration[0] / Intergranular_bubble_concentration[1];
  Intergranular_bubble_volume[1] = Intergranular_atoms_per_bubble[1] * Xenon_covolume + Intergranular_vacancies_per_bubble[1] * Vacancy_volume;
  Intergranular_bubble_radius[1] = pow(3.0*Intergranular_bubble_volume[1]/(4.0*Pi*lenticular_shape_factor),1.0/3.0);
  Intergranular_bubble_area[1] = Pi*pow(Intergranular_bubble_radius[1]*sin(semidihedral_angle), 2);

  // Fractional coverage
  Intergranular_fractional_coverage[1] = Intergranular_bubble_concentration[1] * Intergranular_bubble_area[1];
}

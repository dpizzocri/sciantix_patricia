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

/// GlobalVariables
/// This routine collects all the global variables.
/// Local variables always start with non-capital letters.
/// On the other hand, global variables are preferably
/// defined with capital letters.
/// Input variables used for selecting models and options
/// are defined with an initial "i".

#include "GlobalVariables.h"

// u.o.m. conversions
const double s_h(3600.0); // (s/h)
const double h_d(24.0);   // (h/d)
const double M_1(1.0e-06);// (M/1)

// physical constants
const double Cons_bolt(1.380651e-23); 		   // (J/K)
const double Numb_avog(6.022e+23);    		   // (at/mol)
const double Ener_fiss(312.0e-13);    		   // (J/fiss)
const double Xenon_covolume(8.5e-29);          // (m3)
const double Surface_tension(0.7);    		   // (N/m)
const double Xenon_radius_in_lattice(0.2e-09); // (m)
const double U_UO2(0.8815);                    // (kgU/kgUO2)
const double Vacancy_volume(4.09e-29);		   // (m3)

// mathematical constants
const double Pi(3.141592653589793);

// files
std::ofstream Output;
std::ofstream Error_log;

// time
long long int Time_step_number(0);
double  Time_h(0.0), dTime_h(0.0), Time_end_h(0.0); // (h)
double  Time_s(0.0), dTime_s(0.0), Time_end_s(0.0); // (s)

// input variables - options
unsigned short int iverification(0);
unsigned short int igrain_growth(0);
unsigned short int iinert_gas_behavior(1);
unsigned short int igas_diffusion_coefficient(0);
unsigned short int iintra_bubble_evolution(2);
unsigned short int ibubble_radius(0);
unsigned short int iresolution_rate(0);
unsigned short int itrapping_rate(0);
unsigned short int inucleation_rate(0);
unsigned short int idiffusion_solver(0);
unsigned short int iformat_output(0);
unsigned short int igas_precipitation_at_dislocations(0);
unsigned short int idislocation_density(0);
unsigned short int itrapping_rate_at_dislocations(0);
unsigned short int iintragranular_bubble_coarsening(0);
unsigned short int idislocation_radius_of_influence(0);
unsigned short int igrain_boundary_vacancy_diffusion_coefficient(0);

// input variables - history
int Input_history_points(1000);
std::vector<double> Time_input(1000,0.0);
std::vector<double> Temperature_input(1000,0.0);
std::vector<double> Fissionrate_input(1000,0.0);
std::vector<double> Hydrostaticstress_input(1000,0.0);
double Temperature[2] = {300.0, 300.0};   // (K)
double Fissionrate[2] = {0.0, 0.0};       // (fiss/m3-s)
double Hydrostaticstress[2] = {0.0, 0.0}; // (MPa)

// initial values and parameters
double Initial_grain_radius(0.0); // (m)
double Initial_intergranular_bubble_concentration(4.0e+13); // (bubble/m2)
double Number_of_time_steps_per_interval(0.0); // (#)

// properties
double Fuel_density[2] = {10970.0, 10970.0}; // (kg/m3)
double Grain_radius[2] = {0.0, 0.0}; // (m)

// gas concentrations
double Gas_produced[2] = {0.0, 0.0}; // (at/m3)
double Gas_grain[2] = {0.0, 0.0};    // (at/m3)
double Gas_grain_solution[2] = {0.0, 0.0}; 	 // (at/m3)
double Gas_grain_bubbles[2] = {0.0, 0.0}; 	 // (at/m3)
double Gas_grain_dislocations[2] = {0.0, 0.0}; // (at/m3)
double Gas_boundary[2] = {0.0, 0.0}; // (at/m3)
double Gas_released[2] = {0.0, 0.0}; // (at/m3)
double dGas_produced(0.0);           // (at/m3)
double dGas_grain(0.0);              // (at/m3)
double dGas_boundary(0.0);           // (at/m3)
double dGas_released(0.0);           // (at/m3)
double dGas_bubble(0.0); 	 		 // (at/m3)
int fannealing[2] = {0, 0};

// bubble concentration
double Intragranular_bubble_concentration[2] = {0.0, 0.0}; // (bubbles/m3)
double Intragranular_bubble_radius[2] = {0.0, 0.0};        // (m)
double Intragranular_atoms_per_bubble[2] = {0.0, 0.0};     // (at/bubble)
double Intragranular_bubble_concentration_at_dislocations[2] = {0.0, 0.0}; // (bubbles/m3)
double Intragranular_bubble_radius_at_dislocations[2] = {0.0, 0.0};        // (m)
double Intragranular_atoms_per_bubble_at_dislocations[2] = {0.0, 0.0};     // (at/bubble)
double Intragranular_bubble_volume_at_dislocations[2] = {0.0, 0.0};        // (m3)
double Group_bubble_growth[2] = {0.0, 0.0};                                // (/)
double Intragranular_gas_swelling[2] = {0.0, 0.0};                         // (/)
double Intragranular_vacancies_per_bubble_at_dislocations[2] = {0.0, 0.0}; // (vac/bubble)
double Intergranular_bubble_concentration[2] = {0.0, 0.0}; // (bubbles/m2)
double Intergranular_atoms_per_bubble[2] = {0.0, 0.0};     // (at/bubbles)
double Intergranular_vacancies_per_bubble[2] = {0.0, 0.0}; // (vac/bubbles)
double Intergranular_bubble_radius[2] = {0.0, 0.0};        // (m)
double Intergranular_bubble_area[2] = {0.0, 0.0};          // (m2)
double Intergranular_bubble_volume[2] = {0.0, 0.0};        // (m3)
double Intergranular_fractional_coverage[2] = {0.0, 0.0};  // (/)
double Intergranular_gas_swelling[2] = {0.0, 0.0};         // (/)

// burnup
double Burn_up[2] = {0.0, 0.0};           // (GWd/tU)
double Effective_burn_up[2] = {0.0, 0.0}; // (GWd/tU)
double dBurn_up(0.0);                     // (GWd/tU)
double dEffective_burn_up(0.0);           // (GWd/tU)

// dislocations
double Dislocation_density[2] = {4.0e+13, 4.0e+13}; // (m/m3)
double Burger_vector[2] = {3.85e-10, 3.85e-10};	  // (m)

// scaling factors
double sf_trapping_rate(1.0);
double sf_resolution_rate(1.0);
double sf_nucleation_rate(1.0);
double sf_diffusion_rate(1.0);
double sf_dislocation_density(1.0);
double sf_dislocation_radius_of_influence(1.0);
double sf_trapping_rate_at_dislocations(1.0);
double sf_diffusion_rate_vacancy(1.0);

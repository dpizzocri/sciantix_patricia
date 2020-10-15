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

/// GlobalVariables
/// This routine collects all the global variables.
/// Local variables always start with non-capital letters.
/// On the other hand, global variables are preferably
/// defined with capital letters.
/// Input variables used for selecting models and options
/// are defined with an initial "i".

#include "GlobalVariables.h"

// u.o.m. conversions
const double um_m(1.0e+06); // (um/m)
const double s_h(3600.0); // (s/h)
const double h_d(24.0); // (h/d)
const double M_1(1.0e+06); // (M/1)
const double U_UO2(0.8815); // (mU/mUO2)

// physical constants
const double Cons_bolt(1.380651e-23); 		 // (J/K)
const double Numb_avog(6.022e+23);    		 // (at/mol)
const double Ener_fiss(312.0e-13);    		 // (J/fiss)
const double Xenon_covolume(8.50e-29);     // (m3)
const double Vacancy_volume(4.09e-29);     // (m3)
const double Surface_tension(0.7);    		 // (N/m)
const double Xenon_radius_in_lattice(0.2e-09);		 // (m)

// mathematical constants
const double Pi(3.141592653589793);

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
unsigned short int isolver(0);
unsigned short int ioutput(0);
unsigned short int igrain_boundary_vacancy_diffusion_coefficient(0);
unsigned short int igrain_boundary_behaviour(1);
unsigned short int igrain_boundary_micro_cracking(1);
unsigned short int igrain_recrystallization(1);
unsigned short int ifuel_reactor_type(1);

// input variables - history
double dTime_s(0.0); // (s)
double Temperature[2] = {300.0, 300.0};   // (K)
double Fissionrate[2] = {0.0, 0.0};       // (fiss/m3-s)
double Hydrostaticstress[2] = {0.0, 0.0}; // (MPa)

// input variables - initial values and parameters
double Initial_U235_enrichment(0.0);
double Initial_Pu239_enrichment(0.0);

// Properties
double Burn_up[2] = {0.0, 0.0}; // (GWd/t)
double Effective_burn_up[2] = {0.0, 0.0}; // (GWd/t)
double Grain_radius[2] = {0.0, 0.0}; // (m)
double Fuel_density[2] = {0.0, 0.0}; // (kg/m3)
double Oxygen_to_metal_ratio[2] = {0.0, 0.0}; // (at/at)

// gas concentrations
double Gas_produced[2] = {0.0, 0.0}; // (at/m3)
double Gas_grain[2] = {0.0, 0.0};    // (at/m3)
double Gas_grain_solution[2] = {0.0, 0.0}; 	 // (at/m3)
double Gas_grain_bubbles[2] = {0.0, 0.0}; 	 // (at/m3)
double Gas_boundary[2] = {0.0, 0.0}; // (at/m3)
double Gas_released[2] = {0.0, 0.0}; // (at/m3)
double dGas_produced(0.0);           // (at/m3)
double dGas_grain(0.0);              // (at/m3)
double dGas_boundary(0.0);           // (at/m3)
double dGas_released(0.0);           // (at/m3)
double dGas_bubble(0.0); 	 		 // (at/m3)

// helium concentrations both as single gas atoms and bubbles
double Helium_produced[2] = {0.0, 0.0}; // (at/m3)
double Helium_grain_solution[2] = {0.0, 0.0}; // (at/m3)
double Helium_grain_bubbles[2] = {0.0, 0.0}; // (at/m3)
double Helium_grain[2] = {0.0, 0.0}; // (at/m3)
double Helium_boundary[2] = {0.0, 0.0}; // (at/m3)
double Helium_released[2] = {0.0, 0.0}; // (at/m3)
double dHelium_produced(0.0);           // (at/m3)
double dHelium_grain(0.0);              // (at/m3)
double dHelium_boundary(0.0);           // (at/m3)
double dHelium_released(0.0);           // (at/m3)
double dHelium_bubble(0.0); 	 		      // (at/m3)

// helium diffusion coefficient
//double Helium_diffusion_coefficient(0.0); // (m2/s)

// bubble concentration
double Intragranular_bubble_concentration[2] = {0.0, 0.0}; // (bubbles/m3)
double Intragranular_bubble_radius[2] = {0.0, 0.0};        // (m)
double Intragranular_atoms_per_bubble[2] = {0.0, 0.0};
double Intragranular_gas_swelling[2] = {0.0, 0.0};
double Intergranular_bubble_concentration[2] = {0.0, 0.0}; // (bubbles/m2)
double Intergranular_atoms_per_bubble[2] = {0.0, 0.0};
double Intergranular_vacancies_per_bubble[2] = {0.0, 0.0};
double Intergranular_bubble_radius[2] = {0.0, 0.0}; // (m)
double Intergranular_bubble_area[2] = {0.0, 0.0}; // (m2)
double Intergranular_bubble_volume[2] = {0.0, 0.0}; // (m3)
double Intergranular_fractional_coverage[2] = {0.0, 0.0};
double Intergranular_saturation_fractional_coverage[2] = {0.5, 0.5};
double Intergranular_gas_swelling[2] = {0.0, 0.0};
double Intergranular_fractional_intactness[2] = {1.0, 1.0};

// isotopes concentrations (at/m3)
double He4[2] = {0.0, 0.0};
double O16[2] = {0.0, 0.0};
double Tl207[2] = {0.0, 0.0};
double Tl208[2] = {0.0, 0.0};
double Pb206[2] = {0.0, 0.0};
double Pb207[2] = {0.0, 0.0};
double Pb208[2] = {0.0, 0.0};
double Pb210[2] = {0.0, 0.0};
double Pb211[2] = {0.0, 0.0};
double Pb212[2] = {0.0, 0.0};
double Pb214[2] = {0.0, 0.0};
double Bi210[2] = {0.0, 0.0};
double Bi211[2] = {0.0, 0.0};
double Bi212[2] = {0.0, 0.0};
double Bi214[2] = {0.0, 0.0};
double Po210[2] = {0.0, 0.0};
double Po212[2] = {0.0, 0.0};
double Po214[2] = {0.0, 0.0};
double Po215[2] = {0.0, 0.0};
double Po216[2] = {0.0, 0.0};
double Po218[2] = {0.0, 0.0};
double Rn219[2] = {0.0, 0.0};
double Rn220[2] = {0.0, 0.0};
double Rn222[2] = {0.0, 0.0};
double Fr223[2] = {0.0, 0.0};
double Ra223[2] = {0.0, 0.0};
double Ra224[2] = {0.0, 0.0};
double Ra226[2] = {0.0, 0.0};
double Ra228[2] = {0.0, 0.0};
double Ac227[2] = {0.0, 0.0};
double Ac228[2] = {0.0, 0.0};
double Th227[2] = {0.0, 0.0};
double Th228[2] = {0.0, 0.0};
double Th230[2] = {0.0, 0.0};
double Th231[2] = {0.0, 0.0};
double Th232[2] = {0.0, 0.0};
double Th234[2] = {0.0, 0.0};
double Pa231[2] = {0.0, 0.0};
double Pa234[2] = {0.0, 0.0};
double U234[2] = {0.0, 0.0};
double U235[2] = {0.0, 0.0};
double U236[2] = {0.0, 0.0};
double U237[2] = {0.0, 0.0};
double U238[2] = {0.0, 0.0};
double Np237[2] = {0.0, 0.0};
double Np238[2] = {0.0, 0.0};
double Np239[2] = {0.0, 0.0};
double Pu238[2] = {0.0, 0.0};
double Pu239[2] = {0.0, 0.0};
double Pu240[2] = {0.0, 0.0};
double Pu241[2] = {0.0, 0.0};
double Pu242[2] = {0.0, 0.0};
double Pu243[2] = {0.0, 0.0};
double Am241[2] = {0.0, 0.0};
double Am242[2] = {0.0, 0.0};
double Am242m[2] = {0.0, 0.0};
double Am243[2] = {0.0, 0.0};
double Am244[2] = {0.0, 0.0};
double Cm242[2] = {0.0, 0.0};
double Cm243[2] = {0.0, 0.0};
double Cm244[2] = {0.0, 0.0};
double Cm245[2] = {0.0, 0.0};

// scaling factors
double sf_trapping_rate(1.0);
double sf_resolution_rate(1.0);
double sf_nucleation_rate(1.0);
double sf_diffusion_rate(1.0);

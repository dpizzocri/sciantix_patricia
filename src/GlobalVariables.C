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

// physical constants
const double Cons_bolt(1.380651e-23); 		 // (J/K)
const double Numb_avog(6.022e+23);    		 // (at/mol)
const double Ener_fiss(312.0e-13);    		 // (J/fiss)
const double Covolume_vdw(0.085*10e-27);     // (m3)
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
unsigned short int iformat_output(0);

// input variables - history
double dTime_s(0.0); // (s)
double Temperature[2] = {300.0, 300.0};   // (K)
double Fissionrate[2] = {0.0, 0.0};       // (fiss/m3-s)
double Hydrostaticstress[2] = {0.0, 0.0}; // (MPa)

// input variables - initial values and parameters
double Initial_grain_radius(0.0); // (m)
//double Number_of_time_steps_per_interval(0.0); // (#)

// Properties
double Grain_radius[2] = {0.0, 0.0}; // (m)

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

// bubble concentration
double Intragranular_bubble_concentration[2] = {0.0, 0.0}; // (bubbles/m3)
double Intragranular_bubble_radius[2] = {0.0, 0.0};        // (m)
double Atoms_per_bubble[2] = {0.0, 0.0};

// scaling factors
double sf_trapping_rate(1.0);
double sf_resolution_rate(1.0);
double sf_nucleation_rate(1.0);
double sf_diffusion_rate(1.0);

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

// physical constants
const double Cons_bolt(1.380651e-23); 		   // (J/K)
const double Numb_avog(6.022e+23);    		   // (at/mol)
const double Ener_fiss(312.0e-13);    		   // (J/fiss)
const double Covolume_vdw(0.085*10e-27);       // (m3)
const double Surface_tension(0.7);    		   // (N/m)
const double Xenon_radius_in_lattice(0.2e-09); // (m)
const double U_UO2(0.8815);                    // (kgU/kgUO2)

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
unsigned short int isolver(0);
unsigned short int iformat_output(0);

// input variables - history
int Input_history_points(1000);
std::vector<double> Time_input(1000,0.0);
std::vector<double> Temperature_input(1000,0.0);
std::vector<double> Fissionrate_input(1000,0.0);
std::vector<double> Hydrostaticstress_input(1000,0.0);
double Temperature[2] = {300.0, 300.0};   // (K)
double Fissionrate[2] = {0.0, 0.0};       // (fiss/m3-s)
double Hydrostaticstress[2] = {0.0, 0.0}; // (MPa)

// input variables - initial values and parameters
double Initial_grain_radius(0.0); // (m)
double Number_of_time_steps_per_interval(0.0); // (#)

// Properties
double Fuel_density[2] = {10970.0, 10970.0}; // (kg/m3)
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

// burnup
double Burn_up[2] = {0.0, 0.0};           // (GWd/tU)
double Effective_burn_up[2] = {0.0, 0.0}; // (GWd/tU)
double dBurn_up(0.0);                     // (GWd/tU)
double dEffective_burn_up(0.0);           // (GWd/tU)

// scaling factors
double sf_trapping_rate(1.0);
double sf_resolution_rate(1.0);
double sf_nucleation_rate(1.0);
double sf_diffusion_rate(1.0);

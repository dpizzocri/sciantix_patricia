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

#include <vector>
#include <iostream>
#include <fstream>

// u.o.m. conversions
extern const double s_h;

// physical constants
extern const double Cons_bolt;
extern const double Numb_avog;
extern const double Ener_fiss;
extern const double Covolume_vdw;
extern const double Surface_tension;
extern const double Xenon_radius_in_lattice;

// mathematical constants
extern const double Pi;

// file
extern std::ofstream Output;
extern std::ofstream Error_log;

// time
extern long long int Time_step_number;
extern double  Time_h, dTime_h, Time_end_h;
extern double  Time_s, dTime_s, Time_end_s;

// input variables - options
extern unsigned short int iverification;
extern unsigned short int igrain_growth;
extern unsigned short int iinert_gas_behavior;
extern unsigned short int igas_diffusion_coefficient;
extern unsigned short int iintra_bubble_evolution;
extern unsigned short int ibubble_radius;
extern unsigned short int iresolution_rate;
extern unsigned short int itrapping_rate;
extern unsigned short int inucleation_rate;
extern unsigned short int isolver;
extern unsigned short int iformat_output;

// input variables - history
extern int Input_history_points;
extern int Temperature_input_points;
extern int Fissionrate_input_points;
extern int Specificpower_input_points;
extern int Hydrostaticstress_input_points;
extern std::vector<double> Time_temperature_input;
extern std::vector<double> Time_fissionrate_input;
extern std::vector<double> Time_specificpower_input;
extern std::vector<double> Time_hydrostaticstress_input;
extern std::vector<double> Time_input;
extern std::vector<double> Temperature_input;
extern std::vector<double> Fissionrate_input;
extern std::vector<double> Specificpower_input;
extern std::vector<double> Hydrostaticstress_input;
extern double Temperature[2];
extern double Fissionrate[2];
extern double Specificpower[2];
extern double Hydrostaticstress[2];

// input variables - initial values and parameters
extern double Initial_grain_radius;
extern double Number_of_time_steps_per_interval;

// Properties
extern double Grain_radius[2];

// gas concentrations
extern double Gas_produced[2];
extern double Gas_grain[2];
extern double Gas_grain_solution[2];
extern double Gas_grain_bubbles[2];
extern double Gas_boundary[2];
extern double Gas_released[2];
extern double dGas_produced;
extern double dGas_grain;
extern double dGas_boundary;
extern double dGas_released;
extern double dGas_bubble;

// bubble concentration
extern double Intragranular_bubble_concentration[2];
extern double Intragranular_bubble_radius[2];
extern double Atoms_per_bubble[2];

// scaling factors
extern double sf_trapping_rate;
extern double sf_resolution_rate;
extern double sf_nucleation_rate;
extern double sf_diffusion_rate;

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

#include <vector>
#include <iostream>
#include <fstream>

// u.o.m. conversions
extern const double s_h;

// physical constants
extern const double Cons_bolt;
extern const double Numb_avog;
extern const double Ener_fiss;

// time
extern long long int Time_step_number;
extern double  Time_h, dTime_h, Time_end_h;
extern double  Time_s, dTime_s, Time_end_s;

// input variables - options
extern unsigned short int iverification;
extern unsigned short int igrain_growth;
extern unsigned short int iinert_gas_behavior;

// input variables - history
extern int Temperature_input_points;
extern int Fissionrate_input_points;
extern int Specificpower_input_points;
extern int Hydrostaticstress_input_points;
extern std::vector<double> Time_temperature_input;
extern std::vector<double> Time_fissionrate_input;
extern std::vector<double> Time_specificpower_input;
extern std::vector<double> Time_hydrostaticstress_input;
extern std::vector<double> Temperature_input;
extern std::vector<double> Fissionrate_input;
extern std::vector<double> Specificpower_input;
extern std::vector<double> Hydrostaticstress_input;
extern double Temperature[2];
extern double Fissionrate[2];
extern double Specificpower[2];
extern double Hydrostaticstress[2];

// input variables - initial values
extern double initial_grain_radius;

//
extern double Grain_radius[2];

// gas concentrations
extern double Gas_produced[2];
extern double Gas_grain[2];
extern double Gas_boundary[2];
extern double Gas_released[2];
extern double dGas_produced;
extern double dGas_grain;
extern double dGas_boundary;
extern double dGas_released;

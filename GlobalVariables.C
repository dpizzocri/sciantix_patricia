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

#include "GlobalVariables.h"

// u.o.m. conversions
const double s_h(3600.0);

// physical constants
const double Cons_bolt(1.380651e-23); // (J/K)
const double Numb_avog(6.022e+23);    // (at/mol)
const double Ener_fiss(312.0e-13);    // (J/fiss)

// time
long long int Time_step_number(0);
double  Time_h(0.0), dTime_h(0.0), Time_end_h(0.0);
double  Time_s(0.0), dTime_s(0.0), Time_end_s(0.0);

// input variables
int Temperature_input_points(1000);
int Fissionrate_input_points(1000);
int Specificpower_input_points(1000);
int Hydrostaticstress_input_points(1000);
std::vector<double> Time_temperature_input(1000,0.0);
std::vector<double> Time_fissionrate_input(1000,0.0);
std::vector<double> Time_specificpower_input(1000,0.0);
std::vector<double> Time_hydrostaticstress_input(1000,0.0);
std::vector<double> Temperature_input(1000,0.0);
std::vector<double> Fissionrate_input(1000,0.0);
std::vector<double> Specificpower_input(1000,0.0);
std::vector<double> Hydrostaticstress_input(1000,0.0);
double Temperature[2] = {300.0, 300.0};
double Fissionrate[2] = {0.0, 0.0};
double Specificpower[2] = {0.0, 0.0};
double Hydrostaticstress[2] = {0.0, 0.0};

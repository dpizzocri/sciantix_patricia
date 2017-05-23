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

/// SCIANTIX is a 0D code developed at Politecnico di Milano.
/// The objective of SCIANTIX is to represent the behaviour of a single grain of nuclear fuel.
/// The modelling of inert gas behaviour is the main aspect considered.
/// Engineering models are used, allowing for future integration in industrial fuel performance codes.
/// Nevertheless, physically-based model are preferred to empirical models.
/// This facilitates the incorporation of information from lower length scale calculations.

#include "GlobalVariables.h"
#include "SolverVerification.h"
#include "InputStorage.h"
#include "InputInterpolation.h"
#include "GrainGrowth.h"
#include "InertGasBehavior.h"
#include "InputReading.h"
#include "Initialization.h"
#include "OutputWriting.h"
#include "TimeStepCalculation.h"
#include <iostream>
using namespace std;

int main( )
{
  InputReading( );

  Initialization( );

  Output.open("output.csv", std::ios::out);
  Error_log.open("error_log.txt", std::ios::out);

  if (iverification) SolverVerification( );

  while (Time_h <= Time_end_h)
  {
    // Operations to set up the history
	InputStorage( );
    Temperature[1] = InputInterpolation(Time_h, Time_input, Temperature_input, Input_history_points);
    Fissionrate[1] = InputInterpolation(Time_h, Time_input, Fissionrate_input, Input_history_points);
    Hydrostaticstress[1] = InputInterpolation(Time_h, Time_input, Hydrostaticstress_input, Input_history_points);

	// Physical calculations
	if (igrain_growth) GrainGrowth( );

	if (iinert_gas_behavior) InertGasBehavior( );

    // Output writing
	OutputWriting( );

    // Time increment
    dTime_h = TimeStepCalculation( );
    dTime_s = dTime_h * s_h;

    if (Time_h < Time_end_h)
	{
	  Time_step_number++;
	  Time_h += dTime_h;
  	  Time_s += dTime_s;
	}
	else break;
  }

  Output.close( );
  Error_log.close( );

  return 0;
}

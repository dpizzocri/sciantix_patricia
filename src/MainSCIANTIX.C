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

/// SCIANTIX is a 0D code developed at Politecnico di Milano.
/// The objective of SCIANTIX is to represent the behaviour of a single grain of nuclear fuel.
/// The modelling of inert gas behaviour is the main aspect considered.
/// Engineering models are used, allowing for future integration in industrial fuel performance codes.
/// Nevertheless, physically-based model are preferred to empirical models.
/// This facilitates the incorporation of information from lower length scale calculations.

#include "MainVariables.h"
#include "Sciantix.h"
#include "SolverVerification.h"
#include "InputInterpolation.h"
#include "InputReading.h"
#include "Initialization.h"
//#include "OutputWriting.h"
#include "TimeStepCalculation.h"
#include <iostream>
using namespace std;

int main( )
{
  InputReading( );

  Initialization( );

  //if (iformat_output == 0) Output.open("output.csv", std::ios::out);
  //else Output.open("output.txt", std::ios::out);


  if (iverification) SolverVerification( );

  Sciantix_history[6] = 0.0;
  while (Time_h <= Time_end_h)
  {
    // Operations to set up the history
    //Temperature[1] = InputInterpolation(Time_h, Time_input, Temperature_input, Input_history_points);
    //Fissionrate[1] = InputInterpolation(Time_h, Time_input, Fissionrate_input, Input_history_points);
    //Hydrostaticstress[1] = InputInterpolation(Time_h, Time_input, Hydrostaticstress_input, Input_history_points);

    Sciantix_history[0] = Sciantix_history[1];
    Sciantix_history[1] = InputInterpolation(Time_h, Time_input, Temperature_input, Input_history_points);
    Sciantix_history[2] = Sciantix_history[3];
    Sciantix_history[3] = InputInterpolation(Time_h, Time_input, Fissionrate_input, Input_history_points);
    Sciantix_history[4] = Sciantix_history[5];
    Sciantix_history[5] = InputInterpolation(Time_h, Time_input, Hydrostaticstress_input, Input_history_points);

    Sciantix(Sciantix_options, Sciantix_history, Sciantix_variables, Sciantix_scaling_factors);

    dTime_h = TimeStepCalculation( );
    Sciantix_history[6] = dTime_h * s_h;

    if (Time_h < Time_end_h)
	  {
	    Time_step_number++;
	    Time_h += dTime_h;
  	  Time_s += Sciantix_history[6];
  	}
	  else break;
    //InputStorage( );
	  // Physical calculations
    // Output writing
	  //OutputWriting( );

    // Time increment

  }

  //Output.close( );
  //Error_log.close( );

  return 0;
}

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

#include "GlobalVariables.h"
#include "InputStorage.h"
#include "InputInterpolator.h"

int main( )
{

  while ( Time_h <= Time_end_h )
  {
	InputStorage( );
    Temperature[1] = InputInterpolator( Time_h, Time_temperature_input, Temperature_input, Temperature_input_points );

    if ( Time_h < Time_end_h )
	{
	  Time_step_number++;
	  Time_h += dTime_h;
  	  Time_s += dTime_s;
	}
	else break;
  }
	  
  return 0;
}

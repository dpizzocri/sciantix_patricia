///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.4                         //
//  Year   : 2019                        //
//  Authors: D. Pizzocri and T. Barani   //
//                                       //
///////////////////////////////////////////

#include "OxygenToMetalRatio.h"

/// OxygenToMetalRatio

void OxygenToMetalRatio( )
{
  Oxygen_to_metal_ratio[1] = O16[1] / (U235[1]+U236[1]+U238[1]+
                                       Np237[1]+Np238[1]+Np239[1]+
                                       Pu238[1]+Pu239[1]+Pu240[1]+Pu241[1]+Pu242[1]+Pu243[1]+
                                       Am241[1]+Am242[1]+Am242m[1]+Am243[1]+Am244[1]+
                                       Cm242[1]+Cm243[1]+Cm244[1]+Cm245[1]);
}

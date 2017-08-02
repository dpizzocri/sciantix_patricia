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

/// InertGasBehavior
/// This routine is a driver for the calculations related
/// to the behavior of inert gas gases.
/// It refers to Xe, Kr and He.
/// Several physical processes are described,
/// divided for convenience in two parts:
/// (1) a model for intra-granular behavior and
/// (2) a model for inter-granular behavior.
/// These sub-models include the treatment
/// peculiar gas behavior in the high burnup structure.

#include "InertGasBehavior.h"

void InertGasBehavior( )
{
  IntraGranularGasBehavior( );

  InterGranularGasBehavior( );
}

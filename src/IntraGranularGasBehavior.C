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

/// IntraGranularGasBehavior
/// This routine performs the evolution of
/// fission gas inside the fuel grain
/// during a time step.

#include "IntraGranularGasBehavior.h"

void IntraGranularGasBehavior( )
{
  GasProduction( );

  GasDiffusion( );

  IntraGranularBubbleEvolution( );

  IntraGranularGasSwelling( );
}

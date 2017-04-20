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

#include "IntraGranularGasBehavior.h"

void IntraGranularGasBehavior( )
{
  GasProduction( );

  GasDiffusion( );
  
  //IntraGranularBubbleEvolution( );
}

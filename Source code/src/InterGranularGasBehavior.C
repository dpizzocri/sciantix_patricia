///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 0.1                         //
//  Year   : 2019                        //
//  Authors: D. Pizzocri and T. Barani   //
//                                       //
///////////////////////////////////////////

#include "InterGranularGasBehavior.h"

void InterGranularGasBehavior( )
{
  if(!igrain_boundary_behaviour) return;

  InterGranularMicroCracking( );

  InterGranularBubbleEvolution( );

  InterGranularGasRelease( );

  InterGranularGasSwelling( );
}

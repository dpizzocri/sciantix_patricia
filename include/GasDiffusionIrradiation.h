//////////////////////////////////////////////////
//                                              //
//           S C I A N T I X                    //
//           ---------------                    //
//                                              //
//  Version: 0.1                                //
//  Year   : 2016                               //
//  Authors: D. Pizzocri, T. Barani, A. Magni   //
//                                              //
//////////////////////////////////////////////////

#include <cmath>
#include <vector>
#include "GlobalVariables.h"
#include "Solver.h"
#include "FissionYield.h"
#include "GasDiffusionCoefficient.h"
#include "ResolutionRate.h"
#include "IntraGranularBubbleRadius.h"
#include <iostream>

void GasDiffusionIrradiation(double diffusion_coefficient, double trapping_rate, double trapping_rate_bubble_at_dislocations, double trapping_rate_dislocations);

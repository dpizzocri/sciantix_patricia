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

#include "LocalNeutronFlux.h"

/// Computes local neutron flux based on a simple conversion
/// from the fission rate


double LocalNeutronFlux(  )
{
  double flux(0.); // (n/b-s)

  const double ni(1); // neutrons/fission
  const double effective_fission_probability =   U234[0] * xfU234  +
                                                 U235[0] * xfU235  +
                                                 U236[0] * xfU236  +
                                                 U237[0] * xfU237  +
                                                 U238[0] * xfU238  +
                                                Np237[0] * xfNp237 +
                                                Np238[0] * xfNp238 +
                                                Np239[0] * xfNp239 +
                                                Pu238[0] * xfPu238 +
                                                Pu239[0] * xfPu239 +
                                                Pu240[0] * xfPu240 +
                                                Pu241[0] * xfPu241 +
                                                Pu242[0] * xfPu242 +
                                                Pu243[0] * xfPu243 +
                                                Am241[0] * xfAm241 +
                                                Am242[0] * xfAm242 +
                                               Am242m[0] * xfAm242m+
                                                Am243[0] * xfAm243 +
                                                Am244[0] * xfAm244 +
                                                Cm242[0] * xfCm242 +
                                                Cm243[0] * xfCm243 +
                                                Cm244[0] * xfCm244 +
                                                Cm245[0] * xfCm245;

  flux = Fissionrate[1] * ni / effective_fission_probability;
  return flux;
};

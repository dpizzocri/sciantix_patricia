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

/// IntraGranularBubbleRadius
/// This function several different possible
/// correlations and EOS available in literature
/// for the calculation of the intra-granular bubble radius
/// in absence of vacancies (i.e., no bubble coarsening).
/// [1] J.A. Turnbull, Journal of Nuclear Materials, 38 (1971), 203
/// [2] C. Ronchi, H.J. Matzke, Journal of Nuclear Materials, 45 (1972/73), 15
/// [3] C. Dollins, F. Nichols, Journal of Nuclear Materials, 66 (1977), 143
/// [4] P. Losonen, Journal of Nuclear Materials, 304 (2002), 29
/// [5] J. Spino, J.Rest, W. Goll, C. Walker, Journal of Nuclear Materials, 346 (2005), 131-144
/// [6] D.R. Olander, D. Wongsawaeng, Journal of Nuclear Materials, 354 (2006), 98

#include "IntraGranularBubbleRadius.h"

double IntraGranularBubbleRadius(double temperature, double atoms_per_bubble)
{
	double bubble_radius(0.0); // (m)

	switch(ibubble_radius)
	{
		case 0 :
          // constant value for trial
          bubble_radius = 1.0e-09;
          break;

		case 1 :
          // from [1], [3]
          bubble_radius = pow(3.0*Xenon_covolume/(4.0*Pi),(1.0/3.0)) * pow(atoms_per_bubble,(1.0/3.0));
          break;

		case 2 :
          // from [2]
          bubble_radius = pow(3.0*Cons_bolt*temperature/(8.0*Pi*Surface_tension),0.5) * pow(atoms_per_bubble,0.5);
          break;

		case 3 :
          // from [4]
          bubble_radius = pow(3.0*0.4*Xenon_covolume/(4.0*Pi),(1.0/3.0)) * pow(atoms_per_bubble,(1.0/3.0));
          break;

		case 4 :
          // from [5]
          bubble_radius = pow(3.0*0.6*Xenon_covolume/(4.0*Pi),(1.0/3.0)) * pow(atoms_per_bubble,(1.0/3.0));
          break;

		case 5 :
		{
          // from [6]
          double Xenon_volume_in_lattice = 3.0e-29; // [m3]
          bubble_radius = pow(3.0*Xenon_volume_in_lattice/(4.0*Pi),(1.0/3.0)) * pow(atoms_per_bubble,(1.0/3.0));
          break;
		}

        default :
          ErrorMessages::Switch("BubbleRadius", "ibubble_radius", ibubble_radius);
          break;
	}

	return bubble_radius;
}


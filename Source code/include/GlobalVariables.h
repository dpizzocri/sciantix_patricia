///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.4                         //
//  Year   : 2019                        //
//  Authors: D. Pizzocri and T. Barani   //
//           L. Cognini                  //
///////////////////////////////////////////

// u.o.m. conversions
extern const double um_m;
extern const double s_h;
extern const double h_d;
extern const double M_1;
extern const double U_UO2;

// physical constants
extern const double Cons_bolt;
extern const double Numb_avog;
extern const double Ener_fiss;
extern const double Xenon_covolume;
extern const double Vacancy_volume;
extern const double Surface_tension;
extern const double Xenon_radius_in_lattice;

// mathematical constants
extern const double Pi;

// input variables - options
extern unsigned short int iverification;
extern unsigned short int igrain_growth;
extern unsigned short int iinert_gas_behavior;
extern unsigned short int igas_diffusion_coefficient;
extern unsigned short int iintra_bubble_evolution;
extern unsigned short int ibubble_radius;
extern unsigned short int iresolution_rate;
extern unsigned short int itrapping_rate;
extern unsigned short int inucleation_rate;
extern unsigned short int isolver;
extern unsigned short int ioutput;
extern unsigned short int igrain_boundary_vacancy_diffusion_coefficient;
extern unsigned short int igrain_boundary_behaviour;
extern unsigned short int igrain_boundary_micro_cracking;
extern unsigned short int igrain_recrystallization;
extern unsigned short int ifuel_reactor_type;

// input variables - history
extern double Time[2];
extern double Temperature[2];
extern double Fissionrate[2];
extern double Specificpower[2];
extern double Hydrostaticstress[2];
extern double dTime_s;

// input variables - initial values and parameters
extern double Initial_U235_enrichment;
extern double Initial_Pu239_enrichment;

// Properties
extern double Burn_up[2];
extern double Effective_burn_up[2];
extern double Grain_radius[2];
extern double Fuel_density[2];
extern double Oxygen_to_metal_ratio[2];

// gas concentrations
extern double Gas_produced[2];
extern double Gas_grain[2];
extern double Gas_grain_solution[2];
extern double Gas_grain_bubbles[2];
extern double Gas_boundary[2];
extern double Gas_released[2];
extern double dGas_produced;
extern double dGas_grain;
extern double dGas_boundary;
extern double dGas_released;
extern double dGas_bubble;

// helium concentrations both as single gas atoms and bubbles
extern double Helium_produced[2];
extern double Helium_grain[2];
extern double Helium_grain_solution[2];
extern double Helium_grain_bubbles[2];
extern double Helium_boundary[2];
extern double Helium_released[2];
extern double dHelium_produced;
extern double dHelium_grain;
extern double dHelium_boundary;
extern double dHelium_released;
extern double dHelium_bubble;

// bubble concentration
extern double Intragranular_bubble_concentration[2];
extern double Intragranular_bubble_radius[2];
extern double Intragranular_atoms_per_bubble[2];
extern double Intragranular_gas_swelling[2];
extern double Intergranular_bubble_concentration[2];
extern double Intergranular_atoms_per_bubble[2];
extern double Intergranular_vacancies_per_bubble[2];
extern double Intergranular_bubble_radius[2];
extern double Intergranular_bubble_area[2];
extern double Intergranular_bubble_volume[2];
extern double Intergranular_fractional_coverage[2];
extern double Intergranular_saturation_fractional_coverage[2];
extern double Intergranular_gas_swelling[2];
extern double Intergranular_fractional_intactness[2];

// isotopes concentrations (at/m3)
extern double He4[2];
extern double O16[2];
extern double Tl207[2];
extern double Tl208[2];
extern double Pb206[2];
extern double Pb207[2];
extern double Pb208[2];
extern double Pb210[2];
extern double Pb211[2];
extern double Pb212[2];
extern double Pb214[2];
extern double Bi210[2];
extern double Bi211[2];
extern double Bi212[2];
extern double Bi214[2];
extern double Po210[2];
extern double Po212[2];
extern double Po214[2];
extern double Po215[2];
extern double Po216[2];
extern double Po218[2];
extern double Rn219[2];
extern double Rn220[2];
extern double Rn222[2];
extern double Fr223[2];
extern double Ra223[2];
extern double Ra224[2];
extern double Ra226[2];
extern double Ra228[2];
extern double Ac227[2];
extern double Ac228[2];
extern double Th227[2];
extern double Th228[2];
extern double Th230[2];
extern double Th231[2];
extern double Th232[2];
extern double Th234[2];
extern double Pa231[2];
extern double Pa234[2];
extern double U234[2];
extern double U235[2];
extern double U236[2];
extern double U237[2];
extern double U238[2];
extern double Np237[2];
extern double Np238[2];
extern double Np239[2];
extern double Pu238[2];
extern double Pu239[2];
extern double Pu240[2];
extern double Pu241[2];
extern double Pu242[2];
extern double Pu243[2];
extern double Am241[2];
extern double Am242[2];
extern double Am242m[2];
extern double Am243[2];
extern double Am244[2];
extern double Cm242[2];
extern double Cm243[2];
extern double Cm244[2];
extern double Cm245[2];

// scaling factors
extern double sf_trapping_rate;
extern double sf_resolution_rate;
extern double sf_nucleation_rate;
extern double sf_diffusion_rate;

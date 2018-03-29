///////////////////////////////////////////
//                                       //
//           S C I A N T I X             //
//           ---------------             //
//                                       //
//  Version: 1.0                         //
//  Year   : 2018                        //
//  Authors: D. Pizzocri and T. Barani   //
//                                       //
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

// input variables - history
extern double Time[2];
extern double Temperature[2];
extern double Fissionrate[2];
extern double Specificpower[2];
extern double Hydrostaticstress[2];
extern double dTime_s;

// input variables - initial values and parameters
extern double Initial_grain_radius;
//extern double Number_of_time_steps_per_interval;

// Properties
extern double Burn_up[2];
extern double Effective_burn_up[2];
extern double Grain_radius[2];
extern double Fuel_density[2];

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

// scaling factors
extern double sf_trapping_rate;
extern double sf_resolution_rate;
extern double sf_nucleation_rate;
extern double sf_diffusion_rate;

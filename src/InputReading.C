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

/// InputReading
/// This routine reads the input files.
/// Sciantix requires two input files: (1) input_settings.txt
/// and (2) input_history.txt. The first contains all the
/// model selection variables, whereas the second contains
/// temperature, fission rate and hydrostatic stress
/// as a function of time.

#include "InputReading.h"

unsigned short int ReadOneSetting(std::string variable_name, std::ifstream& input_file, std::ofstream& output_file)
{
  char comment;
  unsigned short int variable;
  input_file >> variable;
  input_file >> comment;
  if(comment == '#') input_file.ignore(256,'\n');
  output_file << variable_name << " = " << variable << std::endl;
  return variable;
}

double ReadOneParameter(std::string variable_name, std::ifstream& input_file, std::ofstream& output_file)
{
  char comment;
  double variable;
  input_file >> variable;
  input_file >> comment;
  if(comment == '#') input_file.ignore(256,'\n');
  output_file << variable_name << " = " << variable << std::endl;
  return variable;
}

void InputReading( )
{
  /// Besides the two input files, this routines creates an input_check.txt file
  /// reporting all the inputs provided in the other files.
  /// It is highly recommended checking this file, since eventual errors
  /// are reported in it.

  std::ifstream input_settings;
  std::ifstream input_history;
  std::ifstream input_scaling_factors;
  std::ofstream input_check;

  input_check.open("input_check.txt", std::ios::out);
  input_settings.open("input_settings.txt");
  input_history.open("input_history.txt");
  input_scaling_factors.open("input_scaling_factors.txt");

  /// First, the file input_settings.txt is read,
  /// and all the inputs are assigned to the respective global variables.
  /// The sintax of the a single line of the input file is:
  /// <variable_value> # comment
  /// The variables currently considered are, in order:
  /// iverification         		range [0,1]   turns on (1) the verification of the solvers
  /// igrain_growth         		range [0,1]   selects the grain growth model
  ///                                     		  0 = no grain growth
  ///                                     		  1 = model from Ainscough et al., 1973
  /// iinert_gas_behavior   		range [0,1]   turns on (1) the inert gas behavior model
  /// igas_diffusion_coefficient	range [0,2]	  selects the diffusion coefficient model
  ///											  0 = typical constant value
  ///											  1 = model from Matzke, 1980
  ///											  2 = model from Turnbull, White, Wise, 1988
  /// iintra_bubble_evolution		range [0,2]	  selects the intra-granular bubbles evolution model
  ///											  0 = typical constant values
  ///											  1 = model from White and Tucker, 1983
  ///											  2 = model from Olander and Wongsawaeng, 2006
  /// ibubble_radius				range [0,5]	  selects the intra-granular bubbles radius model, among some models found in literature
  ///											  0 = typical constant value
  ///											  1 = model from Turnbull, 1971 and from Dollins and Nichols, 1977
  ///											  2 = model from Ronchi and Matzke, 1972/73
  ///											  3 = model from Losonen, 2002
  ///											  4 = model from Spino, Rest, Goll, Walker, 2005
  ///											  5 = model from Olander, Wongsawaeng, 2006
  /// iresolution_rate				range [0,2]	  selects the re-solution rate model
  ///											  0 = typical constant value
  ///											  1 = model from Olander, 1976
  ///											  2 = model from Losonen, 2000
  /// itrapping_rate				range [0,1]	  selects the trapping rate model
  ///											  0 = typical constant value
  ///											  1 = model from Olander and Wongsawaeng, 2006
  /// inucleation_rate				range [0,1]	  selects the nucleation rate model
  ///											  0 = typical constant value
  ///											  1 = model from Olander and Wongsawaeng, 2006
  /// isolver						range [0,1]   selects the solver for intra-granular gas diffusion
  ///											  0 = Spectral Diffusion solver
  ///								  			  1 = FORMAS solver
  /// iformat_output				range [0,1]	  selects the format for the output file
  ///											  0 = output.csv
  ///											  1 = output.txt
  ///
  /// In order to add a variable or a parameter, use the corresponding functions herein defined.
  /// It is recommended to define input variables as global variables.

  // input settings

  iverification = ReadOneSetting("iverification", input_settings, input_check);
  igrain_growth = ReadOneSetting("igrain_growth", input_settings, input_check);
  iinert_gas_behavior = ReadOneSetting("iinert_gas_behavior", input_settings, input_check);
  igas_diffusion_coefficient = ReadOneSetting("igas_diffusion_coefficient", input_settings, input_check);
  iintra_bubble_evolution = ReadOneSetting("iintra_bubble_evolution", input_settings, input_check);
  ibubble_radius = ReadOneSetting("ibubble_radius", input_settings, input_check);
  iresolution_rate = ReadOneSetting("iresolution_rate", input_settings, input_check);
  itrapping_rate = ReadOneSetting("itrapping_rate", input_settings, input_check);
  inucleation_rate = ReadOneSetting("inucleation_rate", input_settings, input_check);
  isolver = ReadOneSetting("isolver", input_settings, input_check);
  iformat_output = ReadOneSetting("iformat_output", input_settings, input_check);
  Initial_grain_radius = ReadOneParameter("Initial_grain_radius", input_settings, input_check);
  Number_of_time_steps_per_interval = ReadOneParameter("Number_of_time_steps_per_interval", input_settings, input_check);

  // input history

  int n = 0;
  while(!input_history.eof())
  {
    input_history >> Time_input[n];
    input_history >> Temperature_input[n];
    input_history >> Fissionrate_input[n];
    input_history >> Hydrostaticstress_input[n];

    input_check << Time_input[n] << "\t";
    input_check << Temperature_input[n] << "\t";
    input_check << Fissionrate_input[n] << "\t";
    input_check << Hydrostaticstress_input[n] << "\t";
    input_check << std::endl;

    n++;
    Input_history_points = n;
  }
  
  Time_input.resize(Input_history_points);
  Temperature_input.resize(Input_history_points);
  Fissionrate_input.resize(Input_history_points);
  Hydrostaticstress_input.resize(Input_history_points);

  Time_end_h = Time_input[Input_history_points-1];
  Time_end_s = Time_end_h * s_h;

  // input scaling factors
  
  if (!input_scaling_factors.fail())
  {
    sf_resolution_rate = ReadOneParameter("sf_resolution_rate", input_scaling_factors, input_check);
    sf_trapping_rate = ReadOneParameter("sf_trapping_rate", input_scaling_factors, input_check);
    sf_nucleation_rate = ReadOneParameter("sf_nucleation_rate", input_scaling_factors, input_check);
    sf_diffusion_rate = ReadOneParameter("sf_diffusion_rate", input_scaling_factors, input_check);
  }
  
  input_check.close();
  input_settings.close();
  input_history.close();
  input_scaling_factors.close();
}

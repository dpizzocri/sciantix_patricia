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

  // input settings
  Sciantix_options[0] = ReadOneSetting("iverification", input_settings, input_check);
  Sciantix_options[1] = ReadOneSetting("igrain_growth", input_settings, input_check);
  Sciantix_options[2] = ReadOneSetting("iinert_gas_behavior", input_settings, input_check);
  Sciantix_options[3] = ReadOneSetting("igas_diffusion_coefficient", input_settings, input_check);
  Sciantix_options[4] = ReadOneSetting("iintra_bubble_evolution", input_settings, input_check);
  Sciantix_options[5] = ReadOneSetting("ibubble_radius", input_settings, input_check);
  Sciantix_options[6] = ReadOneSetting("iresolution_rate", input_settings, input_check);
  Sciantix_options[7] = ReadOneSetting("itrapping_rate", input_settings, input_check);
  Sciantix_options[8] = ReadOneSetting("inucleation_rate", input_settings, input_check);
  Sciantix_options[9] = ReadOneSetting("isolver", input_settings, input_check);
  Sciantix_options[10] = ReadOneSetting("iformat_output", input_settings, input_check);
  Sciantix_options[11] = ReadOneSetting("igrain_boundary_vacancy_diffusion_coefficient", input_settings, input_check);
  Sciantix_options[12] = ReadOneSetting("igrain_boundary_behaviour", input_settings, input_check);
  Sciantix_options[13] = ReadOneSetting("igrain_boundary_micro_cracking", input_settings, input_check);
  Sciantix_options[14] = ReadOneSetting("igrain_recrystallization", input_settings, input_check);

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
  Time_end_s = Time_end_h * 3600.0;

  // input scaling factors
  if (!input_scaling_factors.fail())
  {
    Sciantix_scaling_factors[0] = ReadOneParameter("sf_resolution_rate", input_scaling_factors, input_check);
    Sciantix_scaling_factors[1] = ReadOneParameter("sf_trapping_rate", input_scaling_factors, input_check);
    Sciantix_scaling_factors[2] = ReadOneParameter("sf_nucleation_rate", input_scaling_factors, input_check);
    Sciantix_scaling_factors[3] = ReadOneParameter("sf_diffusion_rate", input_scaling_factors, input_check);
  }

  input_check.close();
  input_settings.close();
  input_history.close();
  input_scaling_factors.close();
}

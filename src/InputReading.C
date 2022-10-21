//////////////////////////////////////////////////////////////////////////////////////
//       _______.  ______  __       ___      .__   __. .___________. __  ___   ___  //
//      /       | /      ||  |     /   \     |  \ |  | |           ||  | \  \ /  /  //
//     |   (----`|  ,----'|  |    /  ^  \    |   \|  | `---|  |----`|  |  \  V  /   //
//      \   \    |  |     |  |   /  /_\  \   |  . `  |     |  |     |  |   >   <    //
//  .----)   |   |  `----.|  |  /  _____  \  |  |\   |     |  |     |  |  /  .  \   //
//  |_______/     \______||__| /__/     \__\ |__| \__|     |__|     |__| /__/ \__\  //
//                                                                                  //
//  Originally developed by D. Pizzocri & T. Barani                                 //
//                                                                                  //
//  Version: 2.0                                                                    //
//  Year: 2022                                                                      //
//  Authors: D. Pizzocri, T. Barani.                                                //
//                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////

/// InputReading
/// This routine reads the input files.
/// Sciantix requires three input files:
/// (1) input_settings.txt
/// (2) input_history.txt.
/// (3) input_initial_conditions.txt
/// The first contains all the model selection variables, whereas the second contains temperature, fission rate and hydrostatic stress as a function of time.
/// The third file contains the initial conditions for the physics variables.

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

std::vector<double> ReadSeveralParameters(std::string variable_name, std::ifstream& input_file, std::ofstream& output_file)
{
  char comment;
  double variable;
  short int K(0);

  std::vector<double> vector_read;
  std::string timestring("");
  std::getline(input_file, timestring);
  std::istringstream timestream(timestring);

  while ( timestream >> variable )
  {
    vector_read.push_back(variable);
    output_file << variable_name << K << " = " << vector_read[K] << std::endl;
    ++K;
  }

  input_file >> comment;

  if(comment == '#') input_file.ignore(256,'\n');

  return vector_read;
}

void InputReading( )
{
  /// Besides the two input files, this routines creates an input_check.txt file
  /// reporting all the inputs provided in the other files.
  /// It is highly recommended checking this file, since eventual errors
  /// are reported in it.

  std::ifstream input_settings;
  std::ifstream input_initial_conditions;
  std::ifstream input_history;
  std::ifstream input_scaling_factors;
  std::ofstream input_check;

  input_check.open("input_check.txt", std::ios::out);
  input_settings.open("input_settings.txt");
  input_initial_conditions.open("input_initial_conditions.txt");
  input_history.open("input_history.txt");
  input_scaling_factors.open("input_scaling_factors.txt");

  Sciantix_options[0] = ReadOneSetting("igrain_growth", input_settings, input_check);
  Sciantix_options[1] = ReadOneSetting("ifission_gas_diffusion_coefficient", input_settings, input_check);
  Sciantix_options[2] = ReadOneSetting("igas_diffusion_solver", input_settings, input_check);
  Sciantix_options[3] = ReadOneSetting("iintragranular_bubble_evolution", input_settings, input_check);
  Sciantix_options[4] = ReadOneSetting("iresolution_rate", input_settings, input_check);
  Sciantix_options[5] = ReadOneSetting("itrapping_rate", input_settings, input_check);
  Sciantix_options[6] = ReadOneSetting("inucleation_rate", input_settings, input_check);
  Sciantix_options[7] = ReadOneSetting("iformat_output", input_settings, input_check);
  Sciantix_options[8] = ReadOneSetting("igrain_boundary_vacancy_diffusion_coefficient", input_settings, input_check);
  Sciantix_options[9] = ReadOneSetting("igrain_boundary_behaviour", input_settings, input_check);
  Sciantix_options[10] = ReadOneSetting("igrain_boundary_micro_cracking", input_settings, input_check);
  Sciantix_options[11] = ReadOneSetting("ifuel_matrix", input_settings, input_check);
  Sciantix_options[12] = ReadOneSetting("igrain_boundary_venting", input_settings, input_check);
  Sciantix_options[13] = ReadOneSetting("iradioactive_fission_gas", input_settings, input_check);
  Sciantix_options[14] = ReadOneSetting("ihelium", input_settings, input_check);
  Sciantix_options[15] = ReadOneSetting("igrain_boundary_sweeping", input_settings, input_check);
  Sciantix_options[16] = ReadOneSetting("ihelium_diffusion_coefficient", input_settings, input_check);

  if (!input_initial_conditions.fail())
  {
    Sciantix_variables[0] = ReadOneParameter("Grain_radius[0]", input_initial_conditions, input_check);

    std::vector<double> initial_composition_Xe;
    initial_composition_Xe  = ReadSeveralParameters("Initial composition Xe", input_initial_conditions, input_check);
    Sciantix_variables[1] = initial_composition_Xe[0];    
    Sciantix_variables[2] = initial_composition_Xe[1];
    Sciantix_variables[3] = initial_composition_Xe[2];
    Sciantix_variables[4] = initial_composition_Xe[3];
    Sciantix_variables[5] = initial_composition_Xe[4];
    Sciantix_variables[6] = initial_composition_Xe[5];

    std::vector<double> initial_composition_Kr;
    initial_composition_Kr  = ReadSeveralParameters("Initial composition Kr", input_initial_conditions, input_check);
    Sciantix_variables[7] = initial_composition_Kr[0];    
    Sciantix_variables[8] = initial_composition_Kr[1];
    Sciantix_variables[9] = initial_composition_Kr[2];
    Sciantix_variables[10] = initial_composition_Kr[3];
    Sciantix_variables[11] = initial_composition_Kr[4];
    Sciantix_variables[12] = initial_composition_Kr[5];

    std::vector<double> initial_composition_He;
    initial_composition_He  = ReadSeveralParameters("Initial composition He", input_initial_conditions, input_check);
    Sciantix_variables[13] = initial_composition_He[0];    
    Sciantix_variables[14] = initial_composition_He[1];
    Sciantix_variables[15] = initial_composition_He[2];
    Sciantix_variables[16] = initial_composition_He[3];
    Sciantix_variables[17] = initial_composition_He[4];
    Sciantix_variables[18] = initial_composition_He[5];

    Sciantix_variables[38] = ReadOneParameter("Burn_up[0]", input_initial_conditions, input_check);
    Sciantix_variables[39] = ReadOneParameter("Effective_burn_up[0]", input_initial_conditions, input_check);
    Sciantix_variables[40] = ReadOneParameter("Fuel_density[0]", input_initial_conditions, input_check);

    std::vector<double> initial_composition_U;
    initial_composition_U  = ReadSeveralParameters("Initial composition U", input_initial_conditions, input_check);
    
    Sciantix_variables[41] = initial_composition_U[0]; // U-234
    Sciantix_variables[42] = initial_composition_U[1]; // U-235
    Sciantix_variables[43] = initial_composition_U[2]; // U-236
    Sciantix_variables[44] = initial_composition_U[3]; // U-237
    Sciantix_variables[45] = initial_composition_U[4]; // U-238

    std::vector<double> initial_composition_Xe133;
    initial_composition_Xe133  = ReadSeveralParameters("Initial composition Xe133", input_initial_conditions, input_check);
    
    Sciantix_variables[48] = initial_composition_Xe133[0];    
    Sciantix_variables[49] = initial_composition_Xe133[1];
    Sciantix_variables[50] = initial_composition_Xe133[2];
    Sciantix_variables[51] = initial_composition_Xe133[3];
    Sciantix_variables[52] = initial_composition_Xe133[4];
    Sciantix_variables[53] = initial_composition_Xe133[5];
    Sciantix_variables[54] = initial_composition_Xe133[6];

  }

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

  Time_end_h = Time_input[Input_history_points - 1];
  Time_end_s = Time_end_h * 3600.0;

  if (!input_scaling_factors.fail())
  {
    Sciantix_scaling_factors[0] = ReadOneParameter("sf_resolution_rate", input_scaling_factors, input_check);
    Sciantix_scaling_factors[1] = ReadOneParameter("sf_trapping_rate", input_scaling_factors, input_check);
    Sciantix_scaling_factors[2] = ReadOneParameter("sf_nucleation_rate", input_scaling_factors, input_check);
    Sciantix_scaling_factors[3] = ReadOneParameter("sf_diffusion_coeff", input_scaling_factors, input_check);
    Sciantix_scaling_factors[4] = ReadOneParameter("sf_screw_parameter", input_scaling_factors, input_check);
    Sciantix_scaling_factors[5] = ReadOneParameter("sf_span_parameter", input_scaling_factors, input_check);
    Sciantix_scaling_factors[6] = ReadOneParameter("sf_cent_parameter", input_scaling_factors, input_check);
  }
  else
  {
    Sciantix_scaling_factors[0] = 1.0;
    Sciantix_scaling_factors[1] = 1.0;
    Sciantix_scaling_factors[2] = 1.0;
    Sciantix_scaling_factors[3] = 1.0;
    Sciantix_scaling_factors[4] = 1.0;
    Sciantix_scaling_factors[5] = 1.0;
    Sciantix_scaling_factors[6] = 1.0;
  }

  input_check.close();
  input_settings.close();
  input_history.close();
  input_scaling_factors.close();
}

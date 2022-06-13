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
  Sciantix_options[15] = ReadOneSetting("ifuel_reactor_type", input_settings, input_check);

  // input initial conditions
  if (!input_initial_conditions.fail())
  {
    Sciantix_variables[0] = ReadOneParameter("Grain_radius[0]", input_initial_conditions, input_check);
    Sciantix_variables[1] = ReadOneParameter("Gas_produced[0]", input_initial_conditions, input_check);
    Sciantix_variables[2] = ReadOneParameter("Gas_grain[0]", input_initial_conditions, input_check);
    Sciantix_variables[3] = ReadOneParameter("Gas_grain_solution[0]", input_initial_conditions, input_check);
    Sciantix_variables[4] = ReadOneParameter("Gas_grain_bubbles[0]", input_initial_conditions, input_check);
    Sciantix_variables[5] = ReadOneParameter("Gas_boundary[0]", input_initial_conditions, input_check);
    Sciantix_variables[6] = ReadOneParameter("Gas_released[0]", input_initial_conditions, input_check);
    Sciantix_variables[20] = ReadOneParameter("Burn_up[0]", input_initial_conditions, input_check);
    Sciantix_variables[21] = ReadOneParameter("Effective_burn_up[0]", input_initial_conditions, input_check);
    Sciantix_variables[84] = ReadOneParameter("Fuel_density[0]", input_initial_conditions, input_check);
    Sciantix_variables[85] = ReadOneParameter("Oxygen_to_metal_ratio[0]", input_initial_conditions, input_check);
    Sciantix_variables[22] = Sciantix_variables[86] = ReadOneParameter("Helium_produced[0]", input_initial_conditions, input_check);
    Sciantix_variables[87] = ReadOneParameter("Helium_grain[0]", input_initial_conditions, input_check);
    Sciantix_variables[88] = ReadOneParameter("Helium_grain_solution[0]", input_initial_conditions, input_check);
    Sciantix_variables[89] = ReadOneParameter("Helium_grain_bubbles[0]", input_initial_conditions, input_check);
    Sciantix_variables[90] = ReadOneParameter("Helium_boundary[0]", input_initial_conditions, input_check);
    Sciantix_variables[91] = ReadOneParameter("Helium_released[0]", input_initial_conditions, input_check);

    std::vector<double> initial_composition_U;
    std::vector<double> initial_composition_Np;
    std::vector<double> initial_composition_Pu;
    std::vector<double> initial_composition_Am;
    std::vector<double> initial_composition_Cm;

    initial_composition_U  = ReadSeveralParameters("Initial composition U ", input_initial_conditions, input_check);
    initial_composition_Np = ReadSeveralParameters("Initial composition Np", input_initial_conditions, input_check);
    initial_composition_Pu = ReadSeveralParameters("Initial composition Pu", input_initial_conditions, input_check);
    initial_composition_Am = ReadSeveralParameters("Initial composition Am", input_initial_conditions, input_check);
    initial_composition_Cm = ReadSeveralParameters("Initial composition Cm", input_initial_conditions, input_check);

    Sciantix_variables[61] = initial_composition_U[0];
    Sciantix_variables[62] = initial_composition_U[1];
    Sciantix_variables[63] = initial_composition_U[2];
    Sciantix_variables[64] = initial_composition_U[3];
    Sciantix_variables[65] = initial_composition_U[4];
    Sciantix_variables[66] = initial_composition_Np[0];
    Sciantix_variables[67] = initial_composition_Np[1];
    Sciantix_variables[68] = initial_composition_Np[2];
    Sciantix_variables[69] = initial_composition_Pu[0];
    Sciantix_variables[70] = initial_composition_Pu[1];
    Sciantix_variables[71] = initial_composition_Pu[2];
    Sciantix_variables[72] = initial_composition_Pu[3];
    Sciantix_variables[73] = initial_composition_Pu[4];
    Sciantix_variables[74] = initial_composition_Pu[5];
    Sciantix_variables[75] = initial_composition_Am[0];
    Sciantix_variables[76] = initial_composition_Am[1];
    Sciantix_variables[77] = initial_composition_Am[2];
    Sciantix_variables[78] = initial_composition_Am[3];
    Sciantix_variables[79] = initial_composition_Am[4];
    Sciantix_variables[80] = initial_composition_Cm[0];
    Sciantix_variables[81] = initial_composition_Cm[1];
    Sciantix_variables[82] = initial_composition_Cm[2];
    Sciantix_variables[83] = initial_composition_Cm[3];

    Sciantix_variables[92] = initial_composition_U[1];
    Sciantix_variables[93] = initial_composition_Pu[1];

  }

  // input history
  int n = 0;
  while(!input_history.eof())
  {
    input_history >> Time_input[n];
    input_history >> Temperature_input[n];
    input_history >> Fissionrate_input[n];
    input_history >> Hydrostaticstress_input[n];

    if (Time_input[n] == 0.0 &&
        Temperature_input[n] == 0.0 &&
        Fissionrate_input[n] == 0.0 &&
        Hydrostaticstress_input[n] == 0.0)
        break;

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
  else
  {
    Sciantix_scaling_factors[0] = 1.0;
    Sciantix_scaling_factors[1] = 1.0;
    Sciantix_scaling_factors[2] = 1.0;
    Sciantix_scaling_factors[3] = 1.0;
  }

  input_check.close();
  input_settings.close();
  input_history.close();
  input_scaling_factors.close();
}

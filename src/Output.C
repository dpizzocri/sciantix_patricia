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
//  Authors: D. Pizzocri, G. Zullo.                                                 //
//                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////

#include "Output.h"

/// Output
// to substitute if statements with switch + ErrorMessages

inline bool if_exist (const std::string& name) {
  // function to check if file "name" exists:
  // 0 --> not existing
  // 1 --> existing
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

void Output( )
{
  if(input_variable[iv["iOutput"]].getValue() == 1)
  {
    std::string filename = "output.txt";
    std::fstream sciantix_output;
    sciantix_output.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

    if (history_variable[hv["Time step number"]].getFinalValue() == 0)
    {
      for(std::vector<HistoryVariable>::size_type i = 0; i != history_variable.size(); ++i)
      {
        if (history_variable[i].getOutput())
          sciantix_output << history_variable[i].getName( ) << " " << history_variable[i].getUOM( ) << "\t";
      }
      for(std::vector<SciantixVariable>::size_type i = 0; i != sciantix_variable.size(); ++i)
      {
        if (sciantix_variable[i].getOutput())
          sciantix_output << sciantix_variable[i].getName( ) << " " << sciantix_variable[i].getUOM( ) << "\t";
      }
      sciantix_output << "\n";
    }

    if ((int)history_variable[hv["Time step number"]].getFinalValue()%1 == 0)
    {
      for(std::vector<HistoryVariable>::size_type i = 0; i != history_variable.size(); ++i)
      {
        if (history_variable[i].getOutput())
          sciantix_output << std::setprecision(10) << history_variable[i].getFinalValue() << "\t";
      }

      for(std::vector<SciantixVariable>::size_type i = 0; i != sciantix_variable.size(); ++i)
      {
        if (sciantix_variable[i].getOutput())
          sciantix_output << std::setprecision(7) << sciantix_variable[i].getFinalValue( ) << "\t";
      }

      sciantix_output << "\n";
    }

    sciantix_output.close( );
  }

  std::string filename = "overview.txt";
  if(if_exist(filename)) remove(filename.c_str()); // from string to const char*
  std::fstream check_file;
  if (!if_exist(filename))
  {
    check_file.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

    for(std::vector<Model>::size_type i = 0; i != model.size(); ++i)
    {
      check_file << "Model #" << i << ": " << "\t";
      check_file << model[i].getName() << "\t";
      check_file << model[i].getRef() << "\n";
    }

    check_file << "\n";

    for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
    {
      check_file << "System #" << i << ": " << "\t";
      check_file << sciantix_system[i].getName() << "\t";
      check_file << sciantix_system[i].getRef() << "\n";
    }

    check_file << "\n";

    for(std::vector<InputVariable>::size_type i = 0; i != input_variable.size(); ++i)
    {
      check_file << "Input setting #" << i << ": " << "\t";
      check_file << input_variable[i].getName() << " = ";
      check_file << input_variable[i].getValue() << "\n";
    }

    check_file << "\n";

    for(std::vector<SciantixVariable>::size_type i = 0; i != sciantix_variable.size(); ++i)
    {
      check_file << "Sciantix variable #" << i << ": " << "\t";
      check_file << sciantix_variable[i].getName() << " ";
      check_file << sciantix_variable[i].getUOM() << "\n";
    }
  }
  check_file.close( );

// MATLAB OUTPUT
//  if(input_variable[iv["ioutput"]].getValue() == 2)
//  {
//    if (history_variable[hv["Time"]].getFinalValue() == Time_end_h)
//    {
//      std::string filename = "sciantix_output.m";
//      std::fstream sciantix_output;
//      sciantix_output.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
//
//      // To be completed..
//      // MATLAB output..
//
//      sciantix_output.close( );
//    }
//  }
}

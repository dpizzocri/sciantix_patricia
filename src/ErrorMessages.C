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

/// ErrorMessages
/// This namespace collects the error messages.

#include "ErrorMessages.h"

namespace ErrorMessages
{
  void Switch(std::string routine, std::string variable_name, int variable)
  {
    Error_log << "Error in function " << routine << "." << std::endl;
    Error_log << "The variable " << variable_name << " = " << variable << " is out of range." << std::endl;
    exit(1);
  }
}

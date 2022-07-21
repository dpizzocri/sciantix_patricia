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

#ifndef PHYSICS_CONSTANT_H
#define PHYSICS_CONSTANT_H

#include "Variable.h"

/// Derived class inherited by Variable

class PhysicsConstant : virtual public Variable
{
  protected:
    std::string uom;
    double value;

  public:
    void setUOM(std::string s)
    {
      uom = s;
    }

    std::string getUOM( )
    {
      return uom;
    }

    void setValue(double v)
    {
      value = v;
    }

    double getValue( )
    {
      return value;
    }

  PhysicsConstant() { }
  ~PhysicsConstant() { }

};

#endif

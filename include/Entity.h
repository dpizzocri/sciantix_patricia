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

#ifndef ENTITY_H
#define ENTITY_H
#include <string>

/// Base class endowed with the member variable name, inherited by both Variable and Material classes.

class Entity
{
  protected:
    std::string overview;
    std::string name;

  public:
    void setName(std::string n)
    {
      /// Member function to set the name of the declared object
      name = n;
    }

    std::string getName( )
    {
      /// Member function to get the name of the object
      return name;
    }

    void setRef(std::string n)
    {
      /// Member function to set the name of the declared object
      overview = n;
    }

    std::string getRef( )
    {
      /// Member function to get the name of the object
      return overview;
    }


  Entity() { }
  ~Entity() { }

};

#endif

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

#ifndef GAS_H
#define GAS_H

#include "Material.h"

/// Derived class for the fission gases (e.g., xenon, krypton, helium).
class Gas : virtual public Material
{
  protected:
    int atomic_number;
    double mass_number;
    double van_der_waals_volume;
    double decay_rate;
    double escape_coefficient;

  public:
    void setAtomicNumber(int y)
    {
      /// Member function to set the atomic number of the fission gas
      atomic_number = y;
    }

    int getAtomicNumber( )
    {
      /// Member function to get the atomic number of the fission gas
      return atomic_number;
    }

      void setMassNumber(int y)
    {
      /// Member function to set the mass number of the fission gas
      mass_number = y;
    }

    int getMassNumber( )
    {
      /// Member function to get the mass number of the fission gas
      return mass_number;
    }

    void setVanDerWaalsVolume(double y)
    {
      /// Member function to set the Wan der Waals volume of the gas
      van_der_waals_volume = y;
    }

    double getVanDerWaalsVolume( )
    {
      /// Member function to get the Wan der Waals volume of the gas
      return van_der_waals_volume;
    }

    void setDecayRate(double l)
    {
      /// Member function to set the gas decay rate
      decay_rate = l;
    }

    double getDecayRate( )
    {
      /// Member function to get the Wan der Waals volume of the gas
      return decay_rate;
    }

      void setEscapeCoefficient(double e)
    {
      /// Member function to set the gas escape coefficient
      escape_coefficient = e;
    }

    double getEscapeCoefficient( )
    {
      /// Member function to get the gas escape coefficient
      return escape_coefficient;
    }

    Gas() { }
    ~Gas() { }
};

#endif

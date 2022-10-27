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

#ifndef MATRIX_H
#define MATRIX_H

#include "Material.h"

/// Class for the (fuel) matrix material (e.g., UO2, UO2-HBS, MOX), derived from the class Material
class Matrix : virtual public Material
{
  protected:
    double density;
    double grain_boundary_mobility;
    double ff_range;
    double ff_influence_radius;
    double surface_tension;
    double schottky_defect_volume;
    double ois_volume;
    double grain_boundary_thickness;
    double semidihedral_angle;
    double lenticular_shape_factor;
    double nucleation_rate;

  public:
    void setDensity(double d)
    {
      /// Member function to set the mass density of the matrix (kg/m3)
      density = d;
    }

    double getDensity( )
    {
      /// Member function to get the mass density of the matrix (kg/m3)
      return density;
    }

    void setSurfaceTension(double r)
    {
      /// Member function to set the surface tension of the matrix material (N/m)
      surface_tension = r;
    }

    double getSurfaceTension( )
    {
      /// Member function to get the radius of influence of the fission fragment track (m)
      return surface_tension;
    }

    void setSchottkyVolume(double v)
    {
      /// Member function to set the volume of a Schottky volume in the matrix (m3).
      schottky_defect_volume = v;
    }

    double getSchottkyVolume( )
    {
      /// Member function to get the volume of a Schottky volume in the matrix (m3).
      return schottky_defect_volume;
    }

    void setOIS(double v)
    {
      /// Member function to set the volume of an octahedral interstitial site (OIS) (m3).
      ois_volume = v;
    }

    double getOIS( )
    {
      /// Member function to get the volume of an octahedral interstitial site (OIS) (m3).
      return ois_volume;
    }

    void setGrainBoundaryMobility(double gb)
    {
      /// Member function to set the mobility of the grain boundaries of the matrix
      grain_boundary_mobility = gb;
    }

    double getGrainBoundaryMobility( )
    {
      /// Member function to get the mobility of the grain boundaries of the matrix
      return grain_boundary_mobility;
    }

    void setFFrange(double r)
    {
      /// Member function to set the (average) range of the fission fragments in the matrix (m)
      ff_range = r;
    }

    double getFFrange( )
    {
      /// Member function to get the (average) range of the fission fragments in the matrix (m)
      return ff_range;
    }

    void setFFinfluenceRadius(double r)
    {
      /// Member function to set the estimated radius of influence of the fission fragment track (m)
      ff_influence_radius = r;
    }

    double getFFinfluenceRadius( )
    {
      /// Member function to get the radius of influence of the fission fragment track (m)
      return ff_influence_radius;
    }

    void setSemidihedralAngle(double sda)
    {
      /// Member function to set the angle between the tangent to the bubble surface as it contacts the grain boundary and the plane of the grain boundary (semidihedral angle)
      semidihedral_angle = sda;
    }

    double getSemidihedralAngle( )
    {
      /// Member function to get the angle between the tangent to the bubble surface as it contacts the grain boundary and the plane of the grain boundary (semidihedral angle)
      return semidihedral_angle;
    }

    void setGrainBoundaryThickness(double gbt)
    {
      /// Member function to set the grain-boundary thickness (m)
      grain_boundary_thickness = gbt;
    }

    double getGrainBoundaryThickness( )
    {
      /// Member function to get the grain-boundary thickness (m)
      return grain_boundary_thickness;
    }

    void setLenticularShapeFactor(double lsf)
    {
      /// Member function to set the lenticular shape factor (/)
      lenticular_shape_factor = lsf;
    }

    double getLenticularShapeFactor( )
    {
      /// Member function to get the lenticular shape factor (/)
      return lenticular_shape_factor;
    }

    void setNucleationRate(double n)
    {
      /// Member function to set the nucleation rate of the matrix under irradiation (1/s)
      nucleation_rate = n;
    }

    double getNucleationRate( )
    {
      /// Member function to get the nucleation rate of the matrix under irradiation (1/s)
      return nucleation_rate;
    }

    Matrix() { }
    ~Matrix() { }
};

#endif

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

#ifndef SIMULATION_H
#define SIMULATION_H

#define _USE_MATH_DEFINES
#include <cmath>

#include <vector>

#include "Solver.h"
#include "Model.h"
#include "MapModel.h"
#include "MapSciantixVariable.h"
#include "MapPhysicsVariable.h"
#include "HistoryVariableDeclaration.h"
#include "SciantixVariableDeclaration.h"
#include "ModelDeclaration.h"
#include "SolverDeclaration.h"
#include "PhysicsVariableDeclaration.h"
#include "GasDeclaration.h"
#include "MapGas.h"

/// Derived class representing the operation of SCIANTIX. The conjunction of the models with the implemented solvers results in the simulation.

class Simulation : public Solver, public Model
{
  public:

  void BurnupEvolution( )
  {
    sciantix_variable[sv["Burnup"]].setFinalValue(solver.Integrator(
      sciantix_variable[sv["Burnup"]].getInitialValue(),
      model[sm["Burnup"]].getParameter().at(0),
      physics_variable[pv["Time step"]].getFinalValue( )));
  }

  void GasProduction( )
  {
    /// GasProduction
    /// Function computing the gas produced from fission events.
    /// It solves the equation dP/dt = y F (integrator solver)
    /// P   --> sciantix_variable[sv[sciantix_system[j].getGasName() + " produced"]]
    /// y F --> model[sm["Gas production - " + sciantix_system[j].getGasName() + " in UO2"]].getParameter().at(0)
    
    // This for loop slides over all the considered gases (both stable and radioactive ones) 
    for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
    {
      sciantix_variable[sv[sciantix_system[i].getGasName() + " produced"]].setFinalValue(solver.Integrator(
        sciantix_variable[sv[sciantix_system[i].getGasName() + " produced"]].getInitialValue(),
        model[sm["Gas production - " + sciantix_system[i].getGasName() + " in UO2"]].getParameter().at(0),
        physics_variable[pv["Time step"]].getFinalValue()));
    }
  }

  void GasDecay( )
  {
    // This for loop slides over all the considered gases (both stable and radioactive ones)
    // but computes the decayed concentration only of radioactive isotopes
    for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
    {
      if(gas[ga[sciantix_system[i].getGasName()]].getDecayRate() > 0.0)
        sciantix_variable[sv[sciantix_system[i].getGasName() + " decayed"]].setFinalValue(solver.Decay(
          sciantix_variable[sv[sciantix_system[i].getGasName() + " decayed"]].getInitialValue(),
          gas[ga[sciantix_system[i].getGasName()]].getDecayRate(),
          gas[ga[sciantix_system[i].getGasName()]].getDecayRate() * sciantix_variable[sv[sciantix_system[i].getGasName() + " produced"]].getFinalValue(),
          physics_variable[pv["Time step"]].getFinalValue()));
    }
  }

  void XeDiffusion( )
  {
    if(input_variable[iv["iGasDiffusionSolver"]].getValue() == 1)
    {
      sciantix_variable[sv["Xe in grain"]].setFinalValue(
        solver.SpectralDiffusion(
          xe_diffusion_modes,
          model[sm["Gas diffusion - Xe in UO2"]].getParameter(),
          physics_variable[pv["Time step"]].getFinalValue()));

      double equilibrium_fraction = model[sm["Resolution rate"]].getParameter().front()
      / (model[sm["Resolution rate"]].getParameter().front() + model[sm["Trapping rate"]].getParameter().front() );

      sciantix_variable[sv["Xe in intragranular solution"]].setFinalValue(
        equilibrium_fraction * sciantix_variable[sv["Xe in grain"]].getFinalValue());

      sciantix_variable[sv["Xe in intragranular bubbles"]].setFinalValue(
        (1 - equilibrium_fraction) * sciantix_variable[sv["Xe in grain"]].getFinalValue());

      sciantix_variable[sv["Xe at grain boundary"]].setFinalValue(
        sciantix_variable[sv["Xe produced"]].getFinalValue() -
        sciantix_variable[sv["Xe in grain"]].getFinalValue() -
        sciantix_variable[sv["Xe released"]].getInitialValue());
    }
    
    else if(input_variable[iv["iGasDiffusionSolver"]].getValue() == 2)
    {
      double ref1 = sciantix_variable[sv["Xe in intragranular solution"]].getFinalValue();
      double ref2 = sciantix_variable[sv["Xe in intragranular bubbles"]].getFinalValue();

      solver.SpectralDiffusionNonEquilibrium(
        ref1,
        ref2,
        xe_diffusion_modes_solution,
        xe_diffusion_modes_bubbles,
        model[sm["Gas diffusion - Xe in UO2"]].getParameter(),
        physics_variable[pv["Time step"]].getFinalValue());
      
      sciantix_variable[sv["Xe in intragranular solution"]].setFinalValue(ref1);
      sciantix_variable[sv["Xe in intragranular bubbles"]].setFinalValue(ref2);
      sciantix_variable[sv["Xe in grain"]].setFinalValue(ref1 + ref2);

      sciantix_variable[sv["Xe at grain boundary"]].setFinalValue(
        sciantix_variable[sv["Xe produced"]].getFinalValue() -
        sciantix_variable[sv["Xe in grain"]].getFinalValue() -
        sciantix_variable[sv["Xe released"]].getInitialValue());

      if(sciantix_variable[sv["Xe at grain boundary"]].getFinalValue() < 0.0)
        sciantix_variable[sv["Xe at grain boundary"]].setFinalValue(0.0);
    }
  }

  void Xe133Diffusion( )
  {
    if(input_variable[iv["iGasDiffusionSolver"]].getValue() == 1)
    {
      sciantix_variable[sv["Xe133 in grain"]].setFinalValue(
        solver.SpectralDiffusion(
          xe133_diffusion_modes,
          model[sm["Gas diffusion - Xe133 in UO2"]].getParameter(),
          physics_variable[pv["Time step"]].getFinalValue()));

      double equilibrium_fraction = (model[sm["Resolution rate"]].getParameter().front() + gas[ga["Xe133"]].getDecayRate())
      / (model[sm["Resolution rate"]].getParameter().front() + model[sm["Trapping rate"]].getParameter().front() + gas[ga["Xe133"]].getDecayRate());

      sciantix_variable[sv["Xe133 in intragranular solution"]].setFinalValue(
        equilibrium_fraction * sciantix_variable[sv["Xe133 in grain"]].getFinalValue());

      sciantix_variable[sv["Xe133 in intragranular bubbles"]].setFinalValue(
        (1 - equilibrium_fraction) * sciantix_variable[sv["Xe133 in grain"]].getFinalValue());

      sciantix_variable[sv["Xe133 at grain boundary"]].setFinalValue(
        sciantix_variable[sv["Xe133 produced"]].getFinalValue() -
        sciantix_variable[sv["Xe133 decayed"]].getFinalValue() -
        sciantix_variable[sv["Xe133 in grain"]].getFinalValue() -
        sciantix_variable[sv["Xe133 released"]].getInitialValue());
    }
    
    else if(input_variable[iv["iGasDiffusionSolver"]].getValue() == 2)
    {
      double ref1 = sciantix_variable[sv["Xe133 in intragranular solution"]].getFinalValue();
      double ref2 = sciantix_variable[sv["Xe133 in intragranular bubbles"]].getFinalValue();

      solver.SpectralDiffusionNonEquilibrium(
        ref1,
        ref2,
        xe133_diffusion_modes_solution,
        xe133_diffusion_modes_bubbles,
        model[sm["Gas diffusion - Xe133 in UO2"]].getParameter(),
        physics_variable[pv["Time step"]].getFinalValue());
      
      sciantix_variable[sv["Xe133 in intragranular solution"]].setFinalValue(ref1);
      sciantix_variable[sv["Xe133 in intragranular bubbles"]].setFinalValue(ref2);
      sciantix_variable[sv["Xe133 in grain"]].setFinalValue(ref1 + ref2);

      sciantix_variable[sv["Xe133 at grain boundary"]].setFinalValue(
        sciantix_variable[sv["Xe133 produced"]].getFinalValue() -
        sciantix_variable[sv["Xe133 decayed"]].getFinalValue() -
        sciantix_variable[sv["Xe133 in grain"]].getFinalValue() -
        sciantix_variable[sv["Xe133 released"]].getInitialValue());

      if(sciantix_variable[sv["Xe133 at grain boundary"]].getFinalValue() < 0.0)
        sciantix_variable[sv["Xe133 at grain boundary"]].setFinalValue(0.0);
    }
  }


  void KrDiffusion( )
  {
    if(input_variable[iv["iGasDiffusionSolver"]].getValue() == 1)
    {
      sciantix_variable[sv["Kr in grain"]].setFinalValue(
        solver.SpectralDiffusion(
          kr_diffusion_modes,
          model[sm["Gas diffusion - Kr in UO2"]].getParameter(),
          physics_variable[pv["Time step"]].getFinalValue()));

      double equilibrium_fraction = model[sm["Resolution rate"]].getParameter().front()
      / (model[sm["Resolution rate"]].getParameter().front() + model[sm["Trapping rate"]].getParameter().front() );

      sciantix_variable[sv["Kr in intragranular solution"]].setFinalValue(
        equilibrium_fraction * sciantix_variable[sv["Kr in grain"]].getFinalValue());

      sciantix_variable[sv["Kr in intragranular bubbles"]].setFinalValue(
        (1 - equilibrium_fraction) * sciantix_variable[sv["Kr in grain"]].getFinalValue());

      sciantix_variable[sv["Kr at grain boundary"]].setFinalValue(
        sciantix_variable[sv["Kr produced"]].getFinalValue() -
        sciantix_variable[sv["Kr in grain"]].getFinalValue() -
        sciantix_variable[sv["Kr released"]].getInitialValue());
    }
    
    else if(input_variable[iv["iGasDiffusionSolver"]].getValue() == 2)
    {
      double ref1 = sciantix_variable[sv["Kr in intragranular solution"]].getFinalValue();
      double ref2 = sciantix_variable[sv["Kr in intragranular bubbles"]].getFinalValue();

      solver.SpectralDiffusionNonEquilibrium(
        ref1,
        ref2,
        kr_diffusion_modes_solution,
        kr_diffusion_modes_bubbles,
        model[sm["Gas diffusion - Kr in UO2"]].getParameter(),
        physics_variable[pv["Time step"]].getFinalValue());
      
      sciantix_variable[sv["Kr in intragranular solution"]].setFinalValue(ref1);
      sciantix_variable[sv["Kr in intragranular bubbles"]].setFinalValue(ref2);
      sciantix_variable[sv["Kr in grain"]].setFinalValue(ref1 + ref2);

      sciantix_variable[sv["Kr at grain boundary"]].setFinalValue(
        sciantix_variable[sv["Kr produced"]].getFinalValue() -
        sciantix_variable[sv["Kr in grain"]].getFinalValue() -
        sciantix_variable[sv["Kr released"]].getInitialValue());

      if(sciantix_variable[sv["Kr at grain boundary"]].getFinalValue() < 0.0)
        sciantix_variable[sv["Kr at grain boundary"]].setFinalValue(0.0);
    }
  }


  void HeDiffusion( )
  {
    if(input_variable[iv["iGasDiffusionSolver"]].getValue() == 1)
    {
      sciantix_variable[sv["He in grain"]].setFinalValue(
        solver.SpectralDiffusion(
          he_diffusion_modes,
          model[sm["Gas diffusion - He in UO2"]].getParameter(),
          physics_variable[pv["Time step"]].getFinalValue()));

      double equilibrium_fraction = model[sm["Resolution rate"]].getParameter().front()
      / (model[sm["Resolution rate"]].getParameter().front() + model[sm["Trapping rate"]].getParameter().front() );

      sciantix_variable[sv["He in intragranular solution"]].setFinalValue(
        equilibrium_fraction * sciantix_variable[sv["He in grain"]].getFinalValue());

      sciantix_variable[sv["He in intragranular bubbles"]].setFinalValue(
        (1 - equilibrium_fraction) * sciantix_variable[sv["He in grain"]].getFinalValue());

      sciantix_variable[sv["He at grain boundary"]].setFinalValue(
        sciantix_variable[sv["He produced"]].getFinalValue() -
        sciantix_variable[sv["He in grain"]].getFinalValue() -
        sciantix_variable[sv["He released"]].getInitialValue());
    }
    
    else if(input_variable[iv["iGasDiffusionSolver"]].getValue() == 2)
    {
      double ref1 = sciantix_variable[sv["He in intragranular solution"]].getFinalValue();
      double ref2 = sciantix_variable[sv["He in intragranular bubbles"]].getFinalValue();

      solver.SpectralDiffusionNonEquilibrium(
        ref1,
        ref2,
        he_diffusion_modes_solution,
        he_diffusion_modes_bubbles,
        model[sm["Gas diffusion - He in UO2"]].getParameter(),
        physics_variable[pv["Time step"]].getFinalValue());
      
      sciantix_variable[sv["He in intragranular solution"]].setFinalValue(ref1);
      sciantix_variable[sv["He in intragranular bubbles"]].setFinalValue(ref2);
      sciantix_variable[sv["He in grain"]].setFinalValue(ref1 + ref2);

      sciantix_variable[sv["He at grain boundary"]].setFinalValue(
        sciantix_variable[sv["He produced"]].getFinalValue() -
        sciantix_variable[sv["He in grain"]].getFinalValue() -
        sciantix_variable[sv["He released"]].getInitialValue());

      if(sciantix_variable[sv["He at grain boundary"]].getFinalValue() < 0.0)
        sciantix_variable[sv["He at grain boundary"]].setFinalValue(0.0);
    }
  }


  void GasDiffusion( )
  {
      XeDiffusion();
      Xe133Diffusion( );
      KrDiffusion();
      HeDiffusion();
  }

  void GrainGrowth( )
  {
    sciantix_variable[sv["Grain radius"]].setFinalValue(
    0.5 * solver.LimitedGrowth(
      2*sciantix_variable[sv["Grain radius"]].getInitialValue(),
      model[sm["Grain growth"]].getParameter(),
      physics_variable[pv["Time step"]].getFinalValue()));
  }

  void GrainGrowthANN( )
  {
    
    double time = physics_variable[pv["Time step"]].getFinalValue() / (3600); // (s) --> (h)
    double temperature = history_variable[hv["Temperature"]].getFinalValue(); // (K)
    double initial_grain_size = sciantix_variable[sv["Grain radius"]].getInitialValue() * 1e6; // initial size in micrometers

    double i_offset[] = {0.0, 773.0, 2.85};
    double i_gain[] = {0.000496031746031746, 0.00142857142857143, 0.164609053497942};
    double i_min = -1;
    double b1[] = {-2.8189651352391860151, 0.10066054763838540309, -3.2587927066956705602};
    double IW1_1[] = {2.6797175039060006085, -2.7783510424372206415, -0.16693998643423232919,
                      0.050140600490369238718, -0.21965867323755683405, -0.27725886465437676875,
                      -3.1578018451850589088, 0.56728282796395734788, 0.073599404528263134839
                      };
    double b2 = -0.56060158781981428433;
    double LW2_1[] = {-0.027286434165159849374, -1.8291134033820521942, -0.73393274734624625033};
    double o_offset = 2.85;
    double o_gain = 0.0730593607305936;
    double o_min = -1;
    double input[] = {time, temperature, initial_grain_size};

    // Dimension
    int n_neurons(3);

    // Input
    for(int i = 0; i < 3; ++i)
      input[i] = (input[i] - i_offset[i]) * i_gain[i] + i_min;

    // Layer 1
    double pp[n_neurons] = {};
    double arg[n_neurons] = {};

    // IW1_1 * input = arg
    solver.dotProduct2D(IW1_1, input, n_neurons, 3, arg);

    for(int i = 0; i < n_neurons; ++i)
    {
      pp[i] = b1[i] + arg[i];
      pp[i] = 2 / (1 + exp(-2*pp[i])) - 1;
    }

    double oo;
    double asp;
    asp = solver.dotProduct1D(LW2_1, pp, n_neurons);

    oo = b2 + asp;

    oo = (oo - o_min) / o_gain + o_offset;

    sciantix_variable[sv["Grain Radius"]].setFinalValue(oo * 1e-6);
  }


  void IntraGranularBubbleBehaviour( )
  {
    // dN / dt = - resolution_rate N + nucleation_rate
    sciantix_variable[sv["Intragranular bubble concentration"]].setFinalValue(
      solver.Decay(sciantix_variable[sv["Intragranular bubble concentration"]].getInitialValue(),
        model[sm["Intragranular bubble evolution"]].getParameter().at(0),
        model[sm["Intragranular bubble evolution"]].getParameter().at(1),
        physics_variable[pv["Time step"]].getFinalValue()));

    // atom per bubbles and bubble radius
    // xe, kr, he, etc...
    for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
    {
      if(gas[ga[sciantix_system[i].getGasName()]].getDecayRate() == 0.0)
      {
        if (sciantix_variable[sv["Intragranular bubble concentration"]].getFinalValue( ) > 0.0)
          sciantix_variable[sv["Intragranular " + sciantix_system[i].getGasName() + " atoms per bubble"]].setFinalValue(
          sciantix_variable[sv[sciantix_system[i].getGasName() + " in intragranular bubbles"]].getFinalValue() /
          sciantix_variable[sv["Intragranular bubble concentration"]].getFinalValue());
        else
          sciantix_variable[sv["Intragranular " + sciantix_system[i].getGasName() + " atoms per bubble"]].setFinalValue(0.0);

        sciantix_variable[sv["Intragranular bubble volume"]].addValue(
          sciantix_system[i].getVolumeInLattice() *
          sciantix_variable[sv["Intragranular " + sciantix_system[i].getGasName() + " atoms per bubble"]].getFinalValue());
      }
    }
    // intragranular bubble radius R = (3Vn/4pi)^(1/3)
    // if i_intragranular bubble evo = 0, i don't want the radius to change
    if(input_variable[iv["iIntraGranularBubbleEvolution"]].getValue())
      sciantix_variable[sv["Intragranular bubble radius"]].setFinalValue(0.620350491 * pow(sciantix_variable[sv["Intragranular bubble volume"]].getFinalValue(), (1.0/3.0)));

    // Swelling
    // 4/3 pi N R^3
    sciantix_variable[sv["Intragranular gas swelling"]].setFinalValue( 4.188790205 *
      pow(sciantix_variable[sv["Intragranular bubble radius"]].getFinalValue(), 3) *
      sciantix_variable[sv["Intragranular bubble concentration"]].getFinalValue());
  }

  void InterGranularBubbleBehaviour()
  {
    // Vacancy concentration
    sciantix_variable[sv["Intergranular vacancies per bubble"]].setFinalValue(
      solver.LimitedGrowth(sciantix_variable[sv["Intergranular vacancies per bubble"]].getInitialValue(),
        model[sm["Intergranular bubble evolution"]].getParameter(),
        physics_variable[pv["Time step"]].getFinalValue()));

    // Bubble volume
    double vol(0);
    for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
    // This for loop slides over only the stable gases, which determine the grain-boundary bubble dynamics
    {
      if(gas[ga[sciantix_system[i].getGasName()]].getDecayRate() == 0.0)
      {
        vol += sciantix_variable[sv["Intergranular " + sciantix_system[i].getGasName() + " atoms per bubble"]].getFinalValue() *
        gas[ga[sciantix_system[i].getGasName()]].getVanDerWaalsVolume();
      }
    }
    vol += sciantix_variable[sv["Intergranular vacancies per bubble"]].getFinalValue() * matrix[sma["UO2"]].getSchottkyVolume();
    sciantix_variable[sv["Intergranular bubble volume"]].setFinalValue(vol);

    // Bubble radius
    sciantix_variable[sv["Intergranular bubble radius"]].setFinalValue(
      0.620350491 * pow(sciantix_variable[sv["Intergranular bubble volume"]].getFinalValue() / (matrix[sma["UO2"]].getLenticularShapeFactor()), 1./3.));

    // Bubble area
    sciantix_variable[sv["Intergranular bubble area"]].setFinalValue(
      M_PI*pow(sciantix_variable[sv["Intergranular bubble radius"]].getFinalValue() * sin(matrix[sma["UO2"]].getSemidihedralAngle()), 2));
    
    // Coalescence
    double dbubble_area = sciantix_variable[sv["Intergranular bubble area"]].getIncrement(); // dA
    sciantix_variable[sv["Intergranular bubble concentration"]].setFinalValue(
      solver.BinaryInteraction(sciantix_variable[sv["Intergranular bubble concentration"]].getInitialValue(), 2.0, dbubble_area));

    // Conservation
    for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
    {
      if(gas[ga[sciantix_system[i].getGasName()]].getDecayRate() == 0.0)
      {
      sciantix_variable[sv["Intergranular " + sciantix_system[i].getGasName() + " atoms per bubble"]].rescaleValue(
        sciantix_variable[sv["Intergranular bubble concentration"]].getInitialValue() /
        sciantix_variable[sv["Intergranular bubble concentration"]].getFinalValue());
      }
    }

    double n_at(0);
    for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
    {
      if(gas[ga[sciantix_system[i].getGasName()]].getDecayRate() == 0.0)
        n_at += sciantix_variable[sv["Intergranular " + sciantix_system[i].getGasName() + " atoms per bubble"]].getFinalValue();
    }
    sciantix_variable[sv["Intergranular atoms per bubble"]].setFinalValue(n_at);

    sciantix_variable[sv["Intergranular vacancies per bubble"]].rescaleValue(
      sciantix_variable[sv["Intergranular bubble concentration"]].getInitialValue() /
      sciantix_variable[sv["Intergranular bubble concentration"]].getFinalValue());

    vol = 0.0;
    for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
    {
      if(gas[ga[sciantix_system[i].getGasName()]].getDecayRate() == 0.0)
      {
        vol += sciantix_variable[sv["Intergranular " + sciantix_system[i].getGasName() + " atoms per bubble"]].getFinalValue() *
        gas[ga[sciantix_system[i].getGasName()]].getVanDerWaalsVolume();
      }
    }
    vol += sciantix_variable[sv["Intergranular vacancies per bubble"]].getFinalValue() * matrix[sma["UO2"]].getSchottkyVolume();
    sciantix_variable[sv["Intergranular bubble volume"]].setFinalValue(vol);

    sciantix_variable[sv["Intergranular bubble radius"]].setFinalValue(
      0.620350491 * pow(sciantix_variable[sv["Intergranular bubble volume"]].getFinalValue() / (matrix[sma["UO2"]].getLenticularShapeFactor()), 1./3.));

    sciantix_variable[sv["Intergranular bubble area"]].setFinalValue(
      M_PI*pow(sciantix_variable[sv["Intergranular bubble radius"]].getFinalValue() * sin(matrix[sma["UO2"]].getSemidihedralAngle()), 2));

    // Fractional coverage
    sciantix_variable[sv["Intergranular fractional coverage"]].setFinalValue(
      sciantix_variable[sv["Intergranular bubble area"]].getFinalValue() *
      sciantix_variable[sv["Intergranular bubble concentration"]].getFinalValue());

    // Intergranular gas release
    //                          F0
    //   ___________A0____________
    //   |_________A1__________  |
    //   |                    |  |
    //   |          F1        N1 N0
    //   |                    |  |
    //   |____________________|__|
    const double similarity_ratio = sqrt(
      sciantix_variable[sv["Intergranular saturation fractional coverage"]].getFinalValue() /
      sciantix_variable[sv["Intergranular fractional coverage"]].getFinalValue());

    if(similarity_ratio < 1.0)
    {
      sciantix_variable[sv["Intergranular bubble area"]].rescaleValue(similarity_ratio);
      sciantix_variable[sv["Intergranular bubble concentration"]].rescaleValue(similarity_ratio);
      sciantix_variable[sv["Intergranular fractional coverage"]].rescaleValue(pow(similarity_ratio, 2));
      sciantix_variable[sv["Intergranular bubble volume"]].rescaleValue(pow(similarity_ratio, 1.5));
      sciantix_variable[sv["Intergranular bubble radius"]].rescaleValue(pow(similarity_ratio, 0.5));
      sciantix_variable[sv["Intergranular vacancies per bubble"]].rescaleValue(pow(similarity_ratio, 1.5));
      sciantix_variable[sv["Intergranular atoms per bubble"]].rescaleValue(pow(similarity_ratio, 1.5));

      // New intergranular gas concentration
      for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
      {
        if(gas[ga[sciantix_system[i].getGasName()]].getDecayRate() == 0.0)
          sciantix_variable[sv["Intergranular " + sciantix_system[i].getGasName() + " atoms per bubble"]].rescaleValue(pow(similarity_ratio, 1.5));
      }

      for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
      {
        sciantix_variable[sv[sciantix_system[i].getGasName() + " at grain boundary"]].rescaleValue(pow(similarity_ratio, 2.5));
      }
    }

    for(std::vector<System>::size_type i = 0; i != sciantix_system.size() - 1; ++i)
    {
      if(gas[ga[sciantix_system[i].getGasName()]].getDecayRate() == 0.0)
      {
        sciantix_variable[sv[sciantix_system[i].getGasName() + " released"]].setFinalValue(
        sciantix_variable[sv[sciantix_system[i].getGasName() + " produced"]].getFinalValue() -
        sciantix_variable[sv[sciantix_system[i].getGasName() + " in grain"]].getFinalValue() -
        sciantix_variable[sv[sciantix_system[i].getGasName() + " at grain boundary"]].getFinalValue());
      }
    }

    for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
    {
      if(gas[ga[sciantix_system[i].getGasName()]].getDecayRate() > 0.0)
      {
        sciantix_variable[sv[sciantix_system[i].getGasName() + " released"]].setFinalValue(
        sciantix_variable[sv[sciantix_system[i].getGasName() + " produced"]].getFinalValue() -
        sciantix_variable[sv[sciantix_system[i].getGasName() + " decayed"]].getFinalValue() -
        sciantix_variable[sv[sciantix_system[i].getGasName() + " in grain"]].getFinalValue() -
        sciantix_variable[sv[sciantix_system[i].getGasName() + " at grain boundary"]].getFinalValue());
      }
    }

    // Swelling
    sciantix_variable[sv["Intergranular gas swelling"]].setFinalValue(
      3 / sciantix_variable[sv["Grain radius"]].getFinalValue() *
      sciantix_variable[sv["Intergranular bubble concentration"]].getFinalValue() *
      sciantix_variable[sv["Intergranular bubble volume"]].getFinalValue()
    );
  }

  void GrainBoundaryMicroCracking( )
  {
    // Parameters:
    // 1st = microcracking parameter
    // 2nd = healing parameter

    // Intergranular fractional intactness
    // df / dT = - dm/dT f
    sciantix_variable[sv["Intergranular fractional intactness"]].setFinalValue(
      solver.Decay(sciantix_variable[sv["Intergranular fractional intactness"]].getInitialValue(),
        model[sm["Grain-boundary micro-cracking"]].getParameter().at(0),
        0.0,
        history_variable[hv["Temperature"]].getIncrement()
      )
    );

    // Intergranular fractional coverage
    // dFc / dT = - ( dm/dT f) Fc
    sciantix_variable[sv["Intergranular fractional coverage"]].setFinalValue(
      solver.Decay(sciantix_variable[sv["Intergranular fractional coverage"]].getInitialValue(),
        model[sm["Grain-boundary micro-cracking"]].getParameter().at(0) * sciantix_variable[sv["Intergranular fractional intactness"]].getFinalValue(),
        0.0,
        history_variable[hv["Temperature"]].getIncrement()
      )
    );

    // Sat fractional coverage
    // dFcsat / dT = - (dm/dT F) Fcsat
    sciantix_variable[sv["Intergranular saturation fractional coverage"]].setFinalValue(
      solver.Decay(sciantix_variable[sv["Intergranular saturation fractional coverage"]].getInitialValue(),
        model[sm["Grain-boundary micro-cracking"]].getParameter().at(0) * sciantix_variable[sv["Intergranular fractional intactness"]].getFinalValue(),
        0.0,
        history_variable[hv["Temperature"]].getIncrement()
      )
    );

    // Intergranular fractional intactness (again)
    // df / dBu = - h f + h
    sciantix_variable[sv["Intergranular fractional intactness"]].setFinalValue(
      solver.Decay(sciantix_variable[sv["Intergranular fractional intactness"]].getFinalValue(),
        model[sm["Grain-boundary micro-cracking"]].getParameter().at(1),
        model[sm["Grain-boundary micro-cracking"]].getParameter().at(1),
        sciantix_variable[sv["Burnup"]].getIncrement()
      )
    );

    // Sat fractional coverage
    // dFcsat / dBu = h (1-f) Fcsat
    sciantix_variable[sv["Intergranular saturation fractional coverage"]].setFinalValue(
      solver.Decay(sciantix_variable[sv["Intergranular saturation fractional coverage"]].getFinalValue(),
        model[sm["Grain-boundary micro-cracking"]].getParameter().at(1) * (1.0 - sciantix_variable[sv["Intergranular fractional intactness"]].getFinalValue()),
        0.0,
        sciantix_variable[sv["Burnup"]].getIncrement()
      )
    );

    // Re-scaling
    const double similarity_ratio = sqrt(
      sciantix_variable[sv["Intergranular fractional coverage"]].getFinalValue() /
      sciantix_variable[sv["Intergranular fractional coverage"]].getInitialValue());

    if(similarity_ratio < 1.0)
    {
      sciantix_variable[sv["Intergranular bubble area"]].rescaleValue(similarity_ratio);
      sciantix_variable[sv["Intergranular bubble concentration"]].rescaleValue(similarity_ratio);
      sciantix_variable[sv["Intergranular fractional coverage"]].rescaleValue(pow(similarity_ratio, 2));
      sciantix_variable[sv["Intergranular bubble volume"]].rescaleValue(pow(similarity_ratio, 1.5));
      sciantix_variable[sv["Intergranular bubble radius"]].rescaleValue(pow(similarity_ratio, 0.5));
      sciantix_variable[sv["Intergranular vacancies per bubble"]].rescaleValue(pow(similarity_ratio, 1.5));
      sciantix_variable[sv["Intergranular atoms per bubble"]].rescaleValue(pow(similarity_ratio, 1.5));

      for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
      {
        if(gas[ga[sciantix_system[i].getGasName()]].getDecayRate() == 0.0)
          sciantix_variable[sv["Intergranular " + sciantix_system[i].getGasName() + " atoms per bubble"]].rescaleValue(pow(similarity_ratio, 1.5));
      }

      for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
      {
          sciantix_variable[sv[sciantix_system[i].getGasName() + " at grain boundary"]].rescaleValue(pow(similarity_ratio, 2.5));
      }
    }

    // This for loop sides over only the stable gases.
    for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
    {
      if(gas[ga[sciantix_system[i].getGasName()]].getDecayRate() == 0.0)
      {
        sciantix_variable[sv[sciantix_system[i].getGasName() + " released"]].setFinalValue(
        sciantix_variable[sv[sciantix_system[i].getGasName() + " produced"]].getFinalValue() -
        sciantix_variable[sv[sciantix_system[i].getGasName() + " in grain"]].getFinalValue() -
        sciantix_variable[sv[sciantix_system[i].getGasName() + " at grain boundary"]].getFinalValue());
      }
    }

    // This for loop sides over only the radioactive gases.
    for(std::vector<System>::size_type i = sciantix_system.size(); i != sciantix_system.size(); ++i)
    {
      if(gas[ga[sciantix_system[i].getGasName()]].getDecayRate() > 0.0)
      {
        sciantix_variable[sv[sciantix_system[i].getGasName() + " released"]].setFinalValue(
        sciantix_variable[sv[sciantix_system[i].getGasName() + " produced"]].getFinalValue() -
        sciantix_variable[sv[sciantix_system[i].getGasName() + " decayed"]].getFinalValue() -
        sciantix_variable[sv[sciantix_system[i].getGasName() + " in grain"]].getFinalValue() -
        sciantix_variable[sv[sciantix_system[i].getGasName() + " at grain boundary"]].getFinalValue());
      }
    }
   }

  void GrainBoundaryVenting( )
  {
    const double grain_edge_length = 0.57 * sciantix_variable[sv["Grain radius"]].getFinalValue();
    const double geom_density = sciantix_variable[sv["Fuel density"]].getFinalValue() / 10950;
    const double porosity = 1 - geom_density;
    const double b = 0.547 * sqrt(porosity/20) * grain_edge_length;
    const double prob = 2 / (grain_edge_length * grain_edge_length) * sciantix_variable[sv["Intergranular bubble radius"]].getFinalValue() * 
      (sciantix_variable[sv["Intergranular bubble radius"]].getFinalValue() + 2 * b);
    //const double R_crit = - b + sqrt(b*b + grain_edge_length * grain_edge_length * 0.5);
    const double R_crit = (grain_edge_length - 2*b)*0.25;

    std::cout << "---" << std::endl;
    std::cout << grain_edge_length << std::endl;
    std::cout << porosity << std::endl;
    std::cout << b << std::endl;
    std::cout << prob << std::endl;
    std::cout << R_crit << std::endl;

    // cracking invariant G = ln(F) - f
    const double cracking_invariant = 
       log(sciantix_variable[sv["Intergranular fractional coverage"]].getFinalValue()) - 
       sciantix_variable[sv["Intergranular fractional intactness"]].getFinalValue();
    
    double sigmoid_variable;
    sigmoid_variable = exp(cracking_invariant + 1);

    // Vented fraction
    if(sciantix_variable[sv["Intergranular bubble radius"]].getFinalValue() < R_crit)
      sciantix_variable[sv["Intergranular vented fraction"]].setFinalValue(prob);
    else
      sciantix_variable[sv["Intergranular vented fraction"]].setFinalValue(
        1.0 / 
        pow( ( 1.0 + model[sm["Grain-boundary venting"]].getParameter().at(0) * 
              exp( - model[sm["Grain-boundary venting"]].getParameter().at(1) * 
                  ( sigmoid_variable - model[sm["Grain-boundary venting"]].getParameter().at(2)) ) ),
          (1.0 / model[sm["Grain-boundary venting"]].getParameter().at(0)))
      );

    // Venting probability
    sciantix_variable[sv["Intergranular venting probability"]].setFinalValue(
      (1.0 - sciantix_variable[sv["Intergranular fractional intactness"]].getFinalValue()) 
      + sciantix_variable[sv["Intergranular fractional intactness"]].getFinalValue() * sciantix_variable[sv["Intergranular vented fraction"]].getFinalValue() 
    );
    
    // Gas is vented by subtracting a fraction of the gas concentration at grain boundaries arrived from diffusion
    for(std::vector<System>::size_type i = 0; i != sciantix_system.size(); ++i)
      sciantix_variable[sv[sciantix_system[i].getGasName() + " at grain boundary"]].setFinalValue(
	    solver.Integrator(
		    sciantix_variable[sv[sciantix_system[i].getGasName() + " at grain boundary"]].getFinalValue(),
	      - sciantix_variable[sv["Intergranular venting probability"]].getFinalValue(),
	        sciantix_variable[sv[sciantix_system[i].getGasName() + " at grain boundary"]].getIncrement()
	    )
    );
  }


  Simulation() { }
  ~Simulation() { }
};

#endif

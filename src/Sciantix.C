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

#include "Sciantix.h"

void Sciantix(int Sciantix_options[],
              double Sciantix_history[],
              double Sciantix_variables[],
              double Sciantix_scaling_factors[],
              double Sciantix_diffusion_modes[])
{
  SetVariables(Sciantix_options, Sciantix_history, Sciantix_variables, Sciantix_scaling_factors, Sciantix_diffusion_modes);

  SetPhysicsConstant( );
  SetMatrix( );
  SetGas( );
  SetSystem( );

  Simulation simulation;

  // Burnup
  Burnup( );                                      MapModel();
  simulation.BurnupEvolution();

  // Grain growth
  GrainGrowth( );                                 MapModel();
  if(input_variable[iv["iGrainGrowth"]].getValue() == 1)
    simulation.GrainGrowth();
  else if(input_variable[iv["iGrainGrowth"]].getValue() == 2)
    simulation.GrainGrowthANN();
  
  // Fission gas behaviour
  GasProduction( );                               MapModel();
  simulation.GasProduction();

  simulation.GasDecay();

  NucleationRate( );                              MapModel();
  ResolutionRate( );                              MapModel();

  IntraGranularBubbleEvolution( );                MapModel();

  simulation.IntraGranularBubbleBehaviour();
  TrappingRate( );                                MapModel();

  GasDiffusion( );                                MapModel(); 
  simulation.GasDiffusion();

  // Intergranular gas / bubble behaviour
  GrainBoundaryVacancyDiffusionCoefficient( );    MapModel();

  GrainBoundaryMicroCracking( );                  MapModel();
  if(input_variable[iv["iGrainBoundaryMicroCracking"]].getValue())
    simulation.GrainBoundaryMicroCracking( );

  GrainBoundaryVenting( );                  MapModel();
  if(input_variable[iv["iGrainBoundaryVenting"]].getValue())
    simulation.GrainBoundaryVenting( );

  InterGranularBubbleEvolution( );                MapModel();
  simulation.InterGranularBubbleBehaviour();

  UpdateVariables(Sciantix_variables, Sciantix_diffusion_modes);

  Output( );

  history_variable.clear();
  sciantix_variable.clear();
  sciantix_system.clear();
  physics_constant.clear();
  physics_variable.clear();
  model.clear();
  material.clear();
  gas.clear();
  matrix.clear();
}

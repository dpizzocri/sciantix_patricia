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

#include "SetVariables.h"

/// SetVariables
/// This routine builds the vectors of objects:
/// - physics_variable
/// - history_variable 
/// - sciantix_variable
/// - input_variable
/// together with the diffusion modes, the maps, and the scaling factors.

void SetVariables(int Sciantix_options[], double Sciantix_history[], double Sciantix_variables[], double Sciantix_scaling_factors[], double Sciantix_diffusion_modes[])
{
  // -----------------------------------------------------------------------------------------------
  // Input variable
  // The vector is used to collect all user input settings relating to the choice of SCIANTIX models
  // -----------------------------------------------------------------------------------------------
  int iv_counter(0);
  if(input_variable.empty())
  {
    input_variable.emplace_back();
    input_variable[iv_counter].setName("iGrainGrowth");
    input_variable[iv_counter].setValue(Sciantix_options[0]);
    ++iv_counter;

    input_variable.emplace_back();
    input_variable[iv_counter].setName("iGasDiffusionCoefficient");
    input_variable[iv_counter].setValue(Sciantix_options[1]);
    ++iv_counter;

    input_variable.emplace_back();
    input_variable[iv_counter].setName("iGasDiffusionSolver");
    input_variable[iv_counter].setValue(Sciantix_options[2]);
    ++iv_counter;

    input_variable.emplace_back();
    input_variable[iv_counter].setName("iIntraGranularBubbleEvolution");
    input_variable[iv_counter].setValue(Sciantix_options[3]);
    ++iv_counter;

    input_variable.emplace_back();
    input_variable[iv_counter].setName("iResolutionRate");
    input_variable[iv_counter].setValue(Sciantix_options[4]);
    ++iv_counter;

    input_variable.emplace_back();
    input_variable[iv_counter].setName("iTrappingRate");
    input_variable[iv_counter].setValue(Sciantix_options[5]);
    ++iv_counter;

    input_variable.emplace_back();
    input_variable[iv_counter].setName("iNucleationRate");
    input_variable[iv_counter].setValue(Sciantix_options[6]);
    ++iv_counter;

    input_variable.emplace_back();
    input_variable[iv_counter].setName("iOutput");
    input_variable[iv_counter].setValue(Sciantix_options[7]);
    ++iv_counter;

    input_variable.emplace_back();
    input_variable[iv_counter].setName("iGrainBoundaryVacancyDiffusionCoefficient");
    input_variable[iv_counter].setValue(Sciantix_options[8]);
    ++iv_counter;

    input_variable.emplace_back();
    input_variable[iv_counter].setName("iGrainBoundaryBehaviour");
    input_variable[iv_counter].setValue(Sciantix_options[9]);
    ++iv_counter;

    input_variable.emplace_back();
    input_variable[iv_counter].setName("iGrainBoundaryMicroCracking");
    input_variable[iv_counter].setValue(Sciantix_options[10]);
    ++iv_counter;

    input_variable.emplace_back();
    input_variable[iv_counter].setName("iFuelMatrix");
    input_variable[iv_counter].setValue(Sciantix_options[11]);
    ++iv_counter;
    
    input_variable.emplace_back();
    input_variable[iv_counter].setName("iGrainBoundaryVenting");
    input_variable[iv_counter].setValue(Sciantix_options[12]);
    ++iv_counter;

    input_variable.emplace_back();
    input_variable[iv_counter].setName("iRadioactiveFissionGas");
    input_variable[iv_counter].setValue(Sciantix_options[13]);
    ++iv_counter;

    input_variable.emplace_back();
    input_variable[iv_counter].setName("iHelium");
    input_variable[iv_counter].setValue(Sciantix_options[14]);
    ++iv_counter;

    input_variable.emplace_back();
    input_variable[iv_counter].setName("iGrainBoundarySweeping");
    input_variable[iv_counter].setValue(Sciantix_options[15]);
    ++iv_counter;

    input_variable.emplace_back();
    input_variable[iv_counter].setName("iDefectiveFuelRod");
    input_variable[iv_counter].setValue(Sciantix_options[16]);
    ++iv_counter;
  }
  MapInputVariable();

  bool toOutputRadioactiveFG(0);
  if(input_variable[iv["iRadioactiveFissionGas"]].getValue() != 0) toOutputRadioactiveFG = 1;

  bool toOutputVenting(0);
  if(input_variable[iv["iGrainBoundaryVenting"]].getValue() != 0) toOutputVenting = 1;

  bool toOutputHelium(0);
  if(input_variable[iv["iHelium"]].getValue() != 0) toOutputHelium = 1;

  bool toOutputCracking(0);
  if(input_variable[iv["iGrainBoundaryMicroCracking"]].getValue() != 0) toOutputCracking = 1;

  bool toOutputGrainBoundary(0);
  if(input_variable[iv["iGrainBoundaryBehaviour"]].getValue() == 1) toOutputGrainBoundary = 1;

  bool toOutputDefectiveFuelRod(0);
  if(input_variable[iv["iDefectiveFuelRod"]].getValue() == 1) toOutputDefectiveFuelRod = 1;

  // ----------------------------------------------------------------------------
  // Physics variable
  // ----------------------------------------------------------------------------
  physics_variable.emplace_back();
  physics_variable[0].setName("Time step");
  physics_variable[0].setUOM("(s)");
  physics_variable[0].setInitialValue(Sciantix_history[6]);
  physics_variable[0].setFinalValue(Sciantix_history[6]);
  physics_variable[0].setOutput(0);
  // ----------------------------------------------------------------------------
  // History variable
  // ----------------------------------------------------------------------------
  history_variable.emplace_back();
  history_variable[0].setName("Time");
  history_variable[0].setUOM("(h)");
  history_variable[0].setInitialValue(Sciantix_history[7]);
  history_variable[0].setFinalValue(Sciantix_history[7]);
  history_variable[0].setOutput(1);

  history_variable.emplace_back();
  history_variable[1].setName("Time step number");
  history_variable[1].setUOM("(/)");
  history_variable[1].setInitialValue(Sciantix_history[8]);
  history_variable[1].setFinalValue(Sciantix_history[8]);
  history_variable[1].setOutput(0);

  history_variable.emplace_back();
  history_variable[2].setName("Temperature");
  history_variable[2].setUOM("(K)");
  history_variable[2].setInitialValue(Sciantix_history[0]);
  history_variable[2].setFinalValue(Sciantix_history[1]);
  history_variable[2].setOutput(1);

  history_variable.emplace_back();
  history_variable[3].setName("Fission rate");
  history_variable[3].setUOM("(fiss / m3 s)");
  history_variable[3].setInitialValue(Sciantix_history[2]);
  history_variable[3].setFinalValue(Sciantix_history[3]);
  history_variable[3].setOutput(1);

  history_variable.emplace_back();
  history_variable[4].setName("Hydrostatic stress");
  history_variable[4].setUOM("(MPa)");
  history_variable[4].setInitialValue(Sciantix_history[4]);
  history_variable[4].setFinalValue(Sciantix_history[5]);
  history_variable[4].setOutput(1);
  // ----------------------------------------------------------------------------
  // Sciantix variable
  // ----------------------------------------------------------------------------
  int sv_counter = 0;
  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Grain radius");
  sciantix_variable[sv_counter].setUOM("(m)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[0]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[0]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Xe produced");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[1]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[1]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Xe in grain");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[2]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[2]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Xe in intragranular solution");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[3]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[3]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Xe in intragranular bubbles");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[4]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[4]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Xe at grain boundary");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[5]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[5]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Xe released");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[6]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[6]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Xe decayed");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(0.0);
  sciantix_variable[sv_counter].setFinalValue(0.0);
  sciantix_variable[sv_counter].setOutput(0);
  ++sv_counter;
  
  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Xe133 produced");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[48]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[48]);
  sciantix_variable[sv_counter].setOutput(toOutputRadioactiveFG);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Xe133 in grain");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[49]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[49]);
  sciantix_variable[sv_counter].setOutput(toOutputRadioactiveFG);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Xe133 in intragranular solution");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[50]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[50]);
  sciantix_variable[sv_counter].setOutput(toOutputRadioactiveFG);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Xe133 in intragranular bubbles");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[51]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[51]);
  sciantix_variable[sv_counter].setOutput(toOutputRadioactiveFG);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Xe133 decayed");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[52]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[52]);
  sciantix_variable[sv_counter].setOutput(toOutputRadioactiveFG);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Xe133 at grain boundary");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[53]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[53]);
  sciantix_variable[sv_counter].setOutput(toOutputRadioactiveFG);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Xe133 released");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[54]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[54]);
  sciantix_variable[sv_counter].setOutput(toOutputRadioactiveFG);
  ++sv_counter;
  

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Xe133 in fuel rod free volume");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[55]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[55]);
  sciantix_variable[sv_counter].setOutput(toOutputDefectiveFuelRod);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Xe133 R/B");
  sciantix_variable[sv_counter].setUOM("(/)");
  sciantix_variable[sv_counter].setInitialValue(0.0);
  sciantix_variable[sv_counter].setFinalValue(0.0);
  sciantix_variable[sv_counter].setOutput(toOutputRadioactiveFG);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Kr produced");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[7]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[7]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Kr in grain");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[8]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[8]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Kr in intragranular solution");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[9]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[9]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Kr in intragranular bubbles");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[10]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[10]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Kr at grain boundary");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[11]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[11]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Kr released");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[12]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[12]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Kr decayed");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(0.0);
  sciantix_variable[sv_counter].setFinalValue(0.0);
  sciantix_variable[sv_counter].setOutput(0);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Fission gas release");
  sciantix_variable[sv_counter].setUOM("(/)");
  sciantix_variable[sv_counter].setInitialValue(0.0);
  sciantix_variable[sv_counter].setFinalValue(0.0);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("He produced");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[13]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[13]);
  sciantix_variable[sv_counter].setOutput(toOutputHelium);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("He in grain");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[14]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[14]);
  sciantix_variable[sv_counter].setOutput(toOutputHelium);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("He in intragranular solution");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[15]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[15]);
  sciantix_variable[sv_counter].setOutput(toOutputHelium);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("He in intragranular bubbles");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[16]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[16]);
  sciantix_variable[sv_counter].setOutput(toOutputHelium);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("He at grain boundary");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[17]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[17]);
  sciantix_variable[sv_counter].setOutput(toOutputHelium);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("He released");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[18]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[18]);
  sciantix_variable[sv_counter].setOutput(toOutputHelium);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("He decayed");
  sciantix_variable[sv_counter].setUOM("(at/m3)");
  sciantix_variable[sv_counter].setInitialValue(0.0);
  sciantix_variable[sv_counter].setFinalValue(0.0);
  sciantix_variable[sv_counter].setOutput(0);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("He fractional release");
  sciantix_variable[sv_counter].setUOM("(/)");
  sciantix_variable[sv_counter].setInitialValue(0.0);
  sciantix_variable[sv_counter].setFinalValue(0.0);
  sciantix_variable[sv_counter].setOutput(toOutputHelium);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("He release rate");
  sciantix_variable[sv_counter].setUOM("(at/m3 s)");
  sciantix_variable[sv_counter].setInitialValue(0.0);
  sciantix_variable[sv_counter].setFinalValue(0.0);
  sciantix_variable[sv_counter].setOutput(toOutputHelium);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intragranular bubble concentration");
  sciantix_variable[sv_counter].setUOM("(bub/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[19]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[19]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intragranular bubble radius");
  sciantix_variable[sv_counter].setUOM("(m)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[20]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[20]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intragranular bubble volume");
  sciantix_variable[sv_counter].setUOM("(m3)");
  sciantix_variable[sv_counter].setInitialValue(0.0);
  sciantix_variable[sv_counter].setFinalValue(0.0);
  sciantix_variable[sv_counter].setOutput(0);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intragranular Xe atoms per bubble");
  sciantix_variable[sv_counter].setUOM("(at/bub)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[21]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[21]);
  sciantix_variable[sv_counter].setOutput(0);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intragranular Kr atoms per bubble");
  sciantix_variable[sv_counter].setUOM("(at/bub)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[22]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[22]);
  sciantix_variable[sv_counter].setOutput(0);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intragranular He atoms per bubble");
  sciantix_variable[sv_counter].setUOM("(at/bub)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[23]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[23]);
  sciantix_variable[sv_counter].setOutput(0);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intragranular atoms per bubble");
  sciantix_variable[sv_counter].setUOM("(at/bub)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[21] + Sciantix_variables[22] + Sciantix_variables[23]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[21] + Sciantix_variables[22] + Sciantix_variables[23]);
  sciantix_variable[sv_counter].setOutput(0);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intragranular gas swelling");
  sciantix_variable[sv_counter].setUOM("(/)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[24]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[24]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intergranular bubble concentration");
  sciantix_variable[sv_counter].setUOM("(bub/m2)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[25]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[25]);
  sciantix_variable[sv_counter].setOutput(toOutputGrainBoundary);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intergranular Xe atoms per bubble");
  sciantix_variable[sv_counter].setUOM("(at/bub)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[26]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[26]);
  sciantix_variable[sv_counter].setOutput(0);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intergranular Kr atoms per bubble");
  sciantix_variable[sv_counter].setUOM("(at/bub)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[27]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[27]);
  sciantix_variable[sv_counter].setOutput(0);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intergranular He atoms per bubble");
  sciantix_variable[sv_counter].setUOM("(at/bub)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[28]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[28]);
  sciantix_variable[sv_counter].setOutput(0);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intergranular atoms per bubble");
  sciantix_variable[sv_counter].setUOM("(at/bub)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[29]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[29]);
  sciantix_variable[sv_counter].setOutput(toOutputGrainBoundary);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intergranular vacancies per bubble");
  sciantix_variable[sv_counter].setUOM("(vac/bub)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[30]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[30]);
  sciantix_variable[sv_counter].setOutput(toOutputGrainBoundary);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intergranular bubble radius");
  sciantix_variable[sv_counter].setUOM("(m)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[31]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[31]);
  sciantix_variable[sv_counter].setOutput(toOutputGrainBoundary);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intergranular bubble area");
  sciantix_variable[sv_counter].setUOM("(m2)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[32]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[32]);
  sciantix_variable[sv_counter].setOutput(toOutputGrainBoundary);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intergranular bubble volume");
  sciantix_variable[sv_counter].setUOM("(m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[33]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[33]);
  sciantix_variable[sv_counter].setOutput(toOutputGrainBoundary);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intergranular fractional coverage");
  sciantix_variable[sv_counter].setUOM("(/)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[34]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[34]);
  sciantix_variable[sv_counter].setOutput(toOutputGrainBoundary);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intergranular saturation fractional coverage");
  sciantix_variable[sv_counter].setUOM("(/)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[35]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[35]);
  sciantix_variable[sv_counter].setOutput(toOutputGrainBoundary);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intergranular gas swelling");
  sciantix_variable[sv_counter].setUOM("(/)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[36]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[36]);
  sciantix_variable[sv_counter].setOutput(toOutputGrainBoundary);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intergranular fractional intactness");
  sciantix_variable[sv_counter].setUOM("(/)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[37]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[37]);
  sciantix_variable[sv_counter].setOutput(toOutputCracking);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Burnup");
  sciantix_variable[sv_counter].setUOM("(MWd/kgUO2)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[38]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[38]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Effective burnup");
  sciantix_variable[sv_counter].setUOM("(MWd/kgUO2)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[39]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[39]);
  sciantix_variable[sv_counter].setOutput(0);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Fuel density");
  sciantix_variable[sv_counter].setUOM("(kg/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[40]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[40]);
  sciantix_variable[sv_counter].setOutput(0);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("U234");
  sciantix_variable[sv_counter].setUOM("(kg/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[41]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[41]);
  sciantix_variable[sv_counter].setOutput(0);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("U235");
  sciantix_variable[sv_counter].setUOM("(kg/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[42]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[42]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("U236");
  sciantix_variable[sv_counter].setUOM("(kg/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[43]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[43]);
  sciantix_variable[sv_counter].setOutput(0);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("U237");
  sciantix_variable[sv_counter].setUOM("(kg/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[44]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[44]);
  sciantix_variable[sv_counter].setOutput(0);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("U238");
  sciantix_variable[sv_counter].setUOM("(kg/m3)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[45]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[45]);
  sciantix_variable[sv_counter].setOutput(1);
  ++sv_counter;

  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intergranular vented fraction");
  sciantix_variable[sv_counter].setUOM("(/)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[46]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[46]);
  sciantix_variable[sv_counter].setOutput(toOutputVenting);
  ++sv_counter;
  
  sciantix_variable.emplace_back();
  sciantix_variable[sv_counter].setName("Intergranular venting probability");
  sciantix_variable[sv_counter].setUOM("(/)");
  sciantix_variable[sv_counter].setInitialValue(Sciantix_variables[47]);
  sciantix_variable[sv_counter].setFinalValue(Sciantix_variables[47]);
  sciantix_variable[sv_counter].setOutput(toOutputVenting);
  ++sv_counter;

  // ----------------------------------------------------------------------------
  // Diffusion modes
  // ----------------------------------------------------------------------------
  for(int i = 0; i < n_modes; ++i)
  {
    xe_diffusion_modes[i] = Sciantix_diffusion_modes[i];
    xe_diffusion_modes_solution[i] = Sciantix_diffusion_modes[1 * n_modes + i];
    xe_diffusion_modes_bubbles[i]  = Sciantix_diffusion_modes[2 * n_modes + i];
    kr_diffusion_modes[i] = Sciantix_diffusion_modes[3 * n_modes + i];
    kr_diffusion_modes_solution[i] = Sciantix_diffusion_modes[4 * n_modes + i];
    kr_diffusion_modes_bubbles[i] = Sciantix_diffusion_modes[5 * n_modes + i];
    he_diffusion_modes[i] = Sciantix_diffusion_modes[6 * n_modes + i];
    he_diffusion_modes_solution[i] = Sciantix_diffusion_modes[7 * n_modes + i];
    he_diffusion_modes_bubbles[i] = Sciantix_diffusion_modes[8 * n_modes + i];
    xe133_diffusion_modes[i] = Sciantix_diffusion_modes[9 * n_modes + i];
    xe133_diffusion_modes_solution[i] = Sciantix_diffusion_modes[10 * n_modes + i];
    xe133_diffusion_modes_bubbles[i] = Sciantix_diffusion_modes[11 * n_modes + i];
  }
  // ----------------------------------------------------------------------------
  // Scaling factors
  // ----------------------------------------------------------------------------
  sf_resolution_rate = Sciantix_scaling_factors[0];
  sf_trapping_rate   = Sciantix_scaling_factors[1];
  sf_nucleation_rate = Sciantix_scaling_factors[2];
  sf_diffusion_coeff = Sciantix_scaling_factors[3];
  sf_screw_parameter = Sciantix_scaling_factors[4];
  sf_span_parameter  = Sciantix_scaling_factors[5];
  sf_cent_parameter  = Sciantix_scaling_factors[6]; 
  // ----------------------------------------------------------------------------
  // Maps
  // ----------------------------------------------------------------------------
  MapHistoryVariable();
  MapSciantixVariable();
  MapPhysicsVariable();
  // ----------------------------------------------------------------------------
}

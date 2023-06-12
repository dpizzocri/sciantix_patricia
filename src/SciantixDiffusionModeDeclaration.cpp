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

#include "SciantixDiffusionModeDeclaration.h"

/// SciantixDiffusionModeDeclaration

const int n_modes(40);
double modes_initial_conditions[n_modes * n_modes];
double xe_diffusion_modes[n_modes];
double xe_diffusion_modes_solution[n_modes];
double xe_diffusion_modes_bubbles[n_modes];
double xe133_diffusion_modes[n_modes];
double xe133_diffusion_modes_solution[n_modes];
double xe133_diffusion_modes_bubbles[n_modes];
double kr_diffusion_modes[n_modes];
double kr_diffusion_modes_solution[n_modes];
double kr_diffusion_modes_bubbles[n_modes];
double kr85m_diffusion_modes[n_modes];
double kr85m_diffusion_modes_solution[n_modes];
double kr85m_diffusion_modes_bubbles[n_modes];
double he_diffusion_modes[n_modes];
double he_diffusion_modes_solution[n_modes];
double he_diffusion_modes_bubbles[n_modes];
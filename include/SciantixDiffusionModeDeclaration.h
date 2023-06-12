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
#ifndef SCIANTIX_DIFFUSION_MODES_DECLARATION
#define SCIANTIX_DIFFUSION_MODES_DECLARATION

#include <vector>

/// SciantixDiffusionModeDeclaration

extern const int n_modes;
extern double modes_initial_conditions[40*40];
extern double xe_diffusion_modes[40];
extern double xe_diffusion_modes_solution[40];
extern double xe_diffusion_modes_bubbles[40];
extern double xe133_diffusion_modes[40];
extern double xe133_diffusion_modes_solution[40];
extern double xe133_diffusion_modes_bubbles[40];
extern double kr_diffusion_modes[40];
extern double kr_diffusion_modes_solution[40];
extern double kr_diffusion_modes_bubbles[40];
extern double kr85m_diffusion_modes[40];
extern double kr85m_diffusion_modes_solution[40];
extern double kr85m_diffusion_modes_bubbles[40];
extern double he_diffusion_modes[40];
extern double he_diffusion_modes_solution[40];
extern double he_diffusion_modes_bubbles[40];

#endif

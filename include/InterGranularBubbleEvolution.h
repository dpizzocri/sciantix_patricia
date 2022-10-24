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

#include "SciantixVariableDeclaration.h"
#include "MapSciantixVariable.h"
#include "ModelDeclaration.h"
#include "MapModel.h"
#include "MatrixDeclaration.h"
#include "MapMatrix.h"
#include "PhysicsConstantDeclaration.h"
#include "MapPhysicsConstant.h"
#include "SystemDeclaration.h"
#include "MapSystem.h"
#include "GasDeclaration.h"
#include "MapGas.h"
#define _USE_MATH_DEFINES
#include <cmath>

void InterGranularBubbleEvolution( );

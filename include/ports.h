/**
 * @file ports.h
 * @author Simon Kloos (sk.dev@alb.one)
 * @brief Contains all defines for ports and controller main declarations
 * @version 0.1
 * @date 2022-03-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#pragma once

#include "main.h"

extern pros::Controller master;

//Motor ports
#define ML1_PORT 11
#define ML2_PORT 12
#define ML3_PORT 13
#define MR1_PORT 20
#define MR2_PORT 19
#define MR3_PORT 18
#define ARM_PORT 9
#define CONV_PORT 1


//Sensor ports
#define ROT_ARM_PORT 5
#define DECH_MECH_PORT 21
#define INERT_PORT 8
#define LED_GREEN_PORT "G"
#define LED_RED_PORT "H"

//Pneumatic ports
#define CLAW_PORT "A"
#define MOGO_MECH_PORT "B"
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
#define ML1_PORT 12
#define ML2_PORT 13
#define ML3_PORT 14
#define MR1_PORT 1
#define MR2_PORT 2
#define MR3_PORT 3
#define ARM_PORT 11
#define CONV_PORT 9


//Sensor ports
#define ROT_ARM_PORT 10
#define DECH_MECH_PORT 0
#define INERT_PORT 0
#define LED_GREEN_PORT 'G'
#define LED_RED_PORT 'H'

//Pneumatic ports
#define CLAMP_PORT 'A'
#define MOGO_CLAMP 'c'
#define MOGO_TILT1 'D'
#define MOGO_TILT2 'E'
#define GOALCOVER_PORT 'B'
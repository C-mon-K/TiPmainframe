/**
 * @file mogomech.cpp
 * @author Simon Kloos (sk.dev@alb.one)
 * @brief 
 * @version 0.1
 * @date 2022-04-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"

pros::ADIDigitalOut TILT1 (MOGO_TILT1);
pros::ADIDigitalOut TILT2 (MOGO_TILT2);
pros::ADIDigitalOut MOGO (MOGO_CLAMP);

bool closed = false;
bool tilted = false;

/**
 * @brief Construct a new SemicolonMogoMech::SemicolonMogoMech object
 * 
 */
SemicolonMogoMech::SemicolonMogoMech() {};

/**
 * @brief initializes the mogo mech (opened and dropped down)
 * 
 */
void SemicolonMogoMech::init() {    
    open();
    drop();
}

/**
 * @brief opens mogo mech clamp
 * 
 */
void SemicolonMogoMech::open() {
    MOGO.set_value(false);
    closed = false;
}

/**
 * @brief closes mogo mech clamp
 * 
 */
void SemicolonMogoMech::close() {
    MOGO.set_value(true);
    closed = true;
}

/**
 * @brief tilt the mogo mech up
 * 
 */
void SemicolonMogoMech::tilt() {
    TILT1.set_value(false);
    TILT2.set_value(false);
    tilted = true;
}

/**
 * @brief drop the mogo mech down
 * 
 */
void SemicolonMogoMech::drop() {
    TILT1.set_value(true);
    TILT2.set_value(true);
    tilted = false;
}

/**
 * @brief toggle the tilter (up <---> down)
 * 
 */
void SemicolonMogoMech::toggleTilt() {
    if(tilted) drop();
    else tilt();
}

/**
 * @brief toggle the clamp (opened <---> closed)
 * 
 */
void SemicolonMogoMech::toggleClamp() {
    if(closed) open();
    else close();
}

/**
 * @brief operates the mogo mech; IF button pressed THEN actuate pistons
 * 
 */
void SemicolonMogoMech::operate() {
    if(master.get_digital_new_press(BUTTON_MOGO_MECH_CLAMP)) toggleClamp();
    if(master.get_digital_new_press(BUTTON_MOGO_MECH_TILT)) toggleTilt();
}
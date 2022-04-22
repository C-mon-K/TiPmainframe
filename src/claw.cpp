/**
 * @file claw.cpp
 * @author Simon Kloos (sk.dev@alb.one)
 * @brief class containing all claw functions. CONSTRUCTOR: LockingClamp
 * @version 0.1
 * @date 2022-04-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "claw.h"

pros::ADIDigitalOut CLAMP (CLAMP_PORT);
bool opened = false;

/**
 * @brief Construct a new Locking Clamp::Locking Clamp object
 * 
 */
LockingClamp::LockingClamp() {}

/**
 * @brief initialization closes the claw
 * 
 */
void LockingClamp::init() {
    close();
}

/**
 * @brief toggle the claw between opened/closed state
 * 
 */
void LockingClamp::toggle() {
    if(opened) {
        close();
        return;
    }
    else { open(); }
}

/**
 * @brief closes the claw
 * 
 */
void LockingClamp::close() {
    CLAMP.set_value(true);
    opened = false;

}

/**
 * @brief opens the claw
 * 
 */
void LockingClamp::open() {
    CLAMP.set_value(false);
    opened = true;

}

/**
 * @brief function that operates the claw. IF button pressed THEN toggle open/closed
 * 
 */
void LockingClamp::operate() {
    if(master.get_digital_new_press(BUTTON_FRONT_CLAMP)) toggle();
}
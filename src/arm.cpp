#include "main.h"

pros::Motor ARM  (ARM_PORT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Rotation ROT_ARM (ROT_ARM_PORT);


/**
 * @brief Construct a new Arm object
 * 
 */
Arm::Arm() {
}

/**
 * @brief Moves up the lift at DRIVE_UP_SPEED. 
 *      Will automatically stop if the rotational 
 *      sensor registers a high enough value.
 *      No toggle; Button hold is required.
 * 
 */
void Arm::moveUp() {

}

/**
 * @brief Moves down he lift at DRIVE_DOWN_SPEED.
 *      Will automatically sto if the rotational 
 *      sensor registers a low enough value. 
 *      No toggle; Button hold is required.
 * 
 */
void Arm::moveDown() {

}

/**
 * @brief Automatically moves the arm to the given
 *      position in degrees. Is interrupted when any
 *      controller input for the arm is given
 * 
 * @param degrees 
 */
void Arm::moveTo(int degrees) {

}
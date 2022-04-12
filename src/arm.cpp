/**
 * @file arm.cpp
 * @author Simon Kloos (sk.dev@alb.one)
 * @brief class containing all arm functions
 * @version 0.1
 * @date 2022-03-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"

#define ARM_MAX_ANGLE 70
#define ARM_MIN_ANGLE 0

pros::Motor ARM (ARM_PORT, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Rotation ROT_ARM (ROT_ARM_PORT);


/**
 * @brief Construct a new Arm object
 * 
 */
Arm::Arm() {}

void Arm::operate() {
    int input = master.get_analog(STICK_ARM);
    bool positive = input > 0;
    bool negative = input < 0;
    int angle = ROT_ARM.get_angle();
    
    //master.print(2, 0, "ARM ANGLE: %d", angle);

    //if(positive && 30000 > angle > 95000) return;
    //if(negative && (angle < 500 || angle > 30000)) return;
    if((positive && (angle > 9500 && angle < 30000)) || (negative && (angle <500 || angle > 30000))) {
        ARM.move(0);
        return;
    }
    //if((positive && (9500 < angle < 30000)) || (negative && (angle < 500 || angle > 30000))) return;
    ARM.move(input);
}

void Arm::init() {
    ARM.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}



/**
 * @brief Moves up the lift at DRIVE_UP_SPEED. 
 *      Will automatically stop if the rotational 
 *      sensor registers a high enough value.
 *      No toggle; Button hold is required.
 * 
 *//*
void Arm::moveUp() {
    if(ROT_ARM.get_angle()<70)
        ARM.move(70);
        }
*/
/**
 * @brief Moves down he lift at DRIVE_DOWN_SPEED.
 *      Will automatically sto if the rotational 
 *      sensor registers a low enough value. 
 *      No toggle; Button hold is required.
 * 
 *//*
void Arm::moveDown() {
    if(ROT_ARM.get_angle()>0 || ROT_ARM.get_angle()>25000)
        ARM.move(-127);
}
*/
/**
 * @brief Stops the arm
 * 
 *//*
void Arm::stop() {
    ARM.move(0);
}
*/


/**
 * @brief Automatically moves the arm to the given
 *      position in degrees. Is interrupted when any
 *      controller input for the arm is given
 * 
 * @param degrees 
 */
void Arm::moveTo(int angle) {
    angle = angle*100;
    while(angle > ROT_ARM.get_angle() && ROT_ARM.get_angle()<70) {
        ARM.move(100);
    }
    while(angle < ROT_ARM.get_angle() && (ROT_ARM.get_angle() > 0 || ROT_ARM.get_angle() > 250)) {
        ARM.move(-100);
    }
    ARM.move(0);

}
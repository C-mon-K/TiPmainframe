/**
 * @file arm.cpp
 * @author Simon Kloos (sk.dev@alb.one)
 * @brief class containing all arm functions. CONSTRUCTOR: Arm
 * @version 0.1
 * @date 2022-03-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"


//Motor and sensor constructors
pros::Motor ARM (ARM_PORT, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Rotation ROT_ARM (ROT_ARM_PORT);

/**
 * @brief Construct a new Arm object
 * 
 */
Arm::Arm() {}

void Arm::operate() {
    double input = master.get_analog(STICK_ARM);
    bool positive = input > 0;
    bool negative = input < 0;
    int angle = ROT_ARM.get_angle();

    if(master.get_digital_new_press(BUTTON_HOME_ARM)) {
        home();
        ringmech.down();
        return;
    }

    if(master.get_digital_new_press(BUTTON_ARM_UP_MACRO)) {
        up();
        return;
    }

    if((positive && (angle > 9500 && angle < 30000)) || (negative && (angle <500 || angle > 30000))) {
        ARM.brake();
        return;
    }
    if(!ArmPID::isArmAutonRunning()) ARM.move_velocity(input * 100 / 127);
}

/**
 * @brief initialize Arm settings (brake mode)
 * 
 */
void Arm::init() {
    ARM.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

/**
 * @brief shortcut function to move the ARM down and up a little
 * 
 */
[[deprecated ("No longer using shake macro. Didn't work anyway")]]
void Arm::shake() {
    ARM.move(-127);
    pros::delay(500);
    ARM.move(127);
    pros::delay(500);
    ARM.brake();
}

void Arm::home() {
    ArmPID::armPID(3000);
}

void Arm::up() {
    ArmPID::armPID(9500);
}

/**
 * @brief
 * Automatically moves the arm to the given
 *      position in centidegrees. Is interrupted when any
 *      controller input for the arm is given
 * 
 * @param angle angle that the arm rotates to in centidegrees
 */
[[deprecated ("replaced by ArmPID, function ArmPID::armPID(double angle)")]]
void Arm::moveTo(int angle) {
    while(angle > ROT_ARM.get_angle() && ROT_ARM.get_angle()<70) {
        ARM.move(100);
    }
    while(angle < ROT_ARM.get_angle() && (ROT_ARM.get_angle() > 0 || ROT_ARM.get_angle() > 250)) {
        ARM.move(-100);
    }
    ARM.move(0);

}
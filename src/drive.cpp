/**
 * @file drive.cpp
 * @author Simon Kloos - Jacob Thompson
 * @brief class containing all drive functions
 * @version 0.1
 * @date 2022-03-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"

//Motor constructors
pros::Motor ML1 (ML1_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor ML2 (ML2_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor ML3 (ML3_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor MR1 (MR1_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor MR2 (MR2_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor MR3 (MR3_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

/**
 * @brief Construct a new SixMotorDrive::SixMotorDrive object
 * 
 */
SixMotorDrive::SixMotorDrive() {
    
}

/**
 * @brief move with a voltage (scaled 0-12V to integers between 0-127)
 * 
 * @param left Motor voltages for left chassis side (ML1, ML2, ML3)
 * @param right Motor voltages for right chassis side (MR1, MR2, MR3)
 */
void SixMotorDrive::move(int left, int right) {

    if(left == 0 && right == 0) {
        ML1.brake();
        ML2.brake();
        ML3.brake();
        MR1.brake();
        MR2.brake();
        MR3.brake();
        return;
    }
    ML1.move(left);
    ML2.move(left);
    ML3.move(left);
    MR1.move(right);
    MR2.move(right);
    MR3.move(right);
}

/**
 * @brief move with a voltage (values of 0-12,000 [mV])
 * 
 * @param left Motor voltages for left chassis side (ML1, ML2, ML3)
 * @param right Motor voltages for right chassis side (MR1, MR2, MR3)
 */
void SixMotorDrive::move_voltage(int left, int right) {
    if(left == 0 && right == 0) {
        ML1.brake();
        ML2.brake();
        ML3.brake();
        MR1.brake();
        MR2.brake();
        MR3.brake();
        pros::lcd::print(5, "Braking Left: %d", left);
    }
    ML1.move_voltage(left);
    ML2.move_voltage(left);
    ML3.move_voltage(left);
    MR1.move_voltage(right);
    MR2.move_voltage(right);
    MR3.move_voltage(right);
    pros::lcd::print(5, "Left value: %d", left);
}

/**
 * @brief operating function of the drive; includes arcade drive with exponential control
 * 
 */
void SixMotorDrive::driveExponentialArcade() {
    int power = master.get_analog(STICK_DRIVE_POWER);
    int turn = master.get_analog(STICK_DRIVE_TURN);

    int left = power + turn;
    int right = power - turn;

    int expLeft = SixMotorDrive::mapToExponential(left);
    int expRight = SixMotorDrive::mapToExponential(right);

    SixMotorDrive::move(expLeft, expRight);
}

/**
 * @brief function to map voltage values (-127 to 127) to an exponential control
 * 
 * @param value value that is supposed to be mapped to exponential
 * @return int exponentially mapped value
 */
int SixMotorDrive::mapToExponential(int value) {
    double mappedValue = value*100/127;
    bool negative = value<0;
    if(negative) mappedValue = -mappedValue;
    double newValue = 1.2*pow(1.043, mappedValue) - 1.2 + 0.2*mappedValue;
    if(negative) newValue = -newValue;
    newValue = newValue*127/100;
    return newValue;
}

void SixMotorDrive::init() {
    ML1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    ML2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    ML3.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    MR1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    MR2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    MR3.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

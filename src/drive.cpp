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

bool holding = false;

pros::Motor ML1 (ML1_PORT, true);
pros::Motor ML2 (ML2_PORT, false);
pros::Motor ML3 (ML3_PORT, true);
pros::Motor MR1 (MR1_PORT, false);
pros::Motor MR2 (MR2_PORT, true);
pros::Motor MR3 (MR3_PORT, false);

SixMotorDrive::SixMotorDrive() {
    ML1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    ML2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    ML3.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    MR1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    MR2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    MR3.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    holding = false;
}

void SixMotorDrive::move(int left, int right) {
    ML1.move(left);
    ML2.move(left);
    ML3.move(left);
    MR1.move(right);
    MR2.move(right);
    MR3.move(right);
}

void SixMotorDrive::move_voltage(int left, int right) {
    ML1.move_voltage(left);
    ML2.move_voltage(left);
    ML3.move_voltage(left);
    MR1.move_voltage(right);
    MR2.move_voltage(right);
    MR3.move_voltage(right);
}

void SixMotorDrive::driveExponentialArcade() {
    int power = master.get_analog(STICK_DRIVE_POWER);
    int turn = master.get_analog(STICK_DRIVE_TURN);

    int left = power + turn;
    int right = power - turn;

    int expLeft = SixMotorDrive::mapToExponential(left);
    int expRight = SixMotorDrive::mapToExponential(right);

    SixMotorDrive::move(expLeft, expRight);

    if(master.get_digital_new_press(BUTTON_TOGGLE_DRIVE_BRAKE)) toggleBrake();
}

int SixMotorDrive::mapToExponential(int value) {
    double mappedValue = value*100/127;
    bool negative = value<0;
    if(negative) mappedValue = -mappedValue;
    double newValue = 1.2*pow(1.043, mappedValue) - 1.2 + 0.2*mappedValue;
    if(negative) newValue = -newValue;
    newValue = newValue*127/100;
    return newValue;
}

void SixMotorDrive::toggleBrake() {
    if(!holding) {
        ML1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        ML2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        ML3.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        MR1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        MR2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        MR3.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        holding = true;
    }
    else {
        ML1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        ML2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        ML3.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        MR1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        MR2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        MR3.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        holding = false;
    }
}
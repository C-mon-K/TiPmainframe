#include "main.h"

pros::Motor ML1 (ML1_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor ML2 (ML2_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor ML3 (ML3_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor MR1 (MR1_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor MR2 (MR2_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor MR3 (MR3_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);

SixMotorDrive::SixMotorDrive() {
    ML1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    ML2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    ML3.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    MR1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    MR2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    MR3.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
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
    int power = master.get_analog(ANALOG_LEFT_Y);
    int turn = master.get_analog(ANALOG_LEFT_X);

    int left = power + turn;
    int right = power - turn;

    left = SixMotorDrive::mapToExponential(left);
    right = SixMotorDrive::mapToExponential(right);

    SixMotorDrive::move(left, right);
}

int SixMotorDrive::mapToExponential(int value) {
    value = value/127*100;
    bool negative = false;
    if(value<0) {
        value = -value;
        negative = true;
    }
    value = 1.2*pow(1.043, value) - 1.2 + 0.2*value;
    if(negative) value = -value;
    value = value/100*127;
    return value;
}

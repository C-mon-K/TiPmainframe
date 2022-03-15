#include "main.h"

SixMotorDrive::SixMotorDrive() {
    {
        pros::Motor ML1 (ML1_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
        pros::Motor ML2 (ML2_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
        pros::Motor ML3 (ML3_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
        pros::Motor MR1 (MR1_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
        pros::Motor MR2 (MR2_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
        pros::Motor MR3 (MR3_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);

        ML1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        ML2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        ML3.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        MR1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        MR2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        MR3.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    }
}
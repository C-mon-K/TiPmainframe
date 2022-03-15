#pragma once

#include "main.h"

//motor declarations 
extern pros::Motor ML1;
extern pros::Motor ML2;
extern pros::Motor ML3;
extern pros::Motor MR1;
extern pros::Motor MR2;
extern pros::Motor MR3;


/**
 * @class 
 * 
 */
class SixMotorDrive {
public:
    SixMotorDrive();
    int mapToExponential(int value);
private:
    void driveExponentialArcade(pros::controller_analog_e_t powerStick, pros::controller_analog_e_t turnStick);
    void move(int left, int right);
    void move_voltage(int left, int right);

};



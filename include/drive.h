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
    void move(int left, int right);
    void move_voltage(int left, int right);
    void driveExponentialArcade(); 
    int mapToExponential(int value);

};



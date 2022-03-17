/**
 * @file main.cpp
 * 
 * @author Simon Kloos (sk.dev@alb.one)
 * @brief main file, contains all vex competition functions
 * @version 0.1
 * @date 2022-03-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"

pros::Controller master (pros::E_CONTROLLER_MASTER);
SixMotorDrive drive;
Arm arm;

void on_center_button() {}

void initialize() {
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	std::cout << "OP control starting..." << std::endl;
	while(true) {
		drive.driveExponentialArcade();
		arm.operate();
		pros::delay(20);
	}
}

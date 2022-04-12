/**
 * @file main.cpp
 * 
 * @author Simon Kloos - Jacob Thompson (sk.dev@alb.one)
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
LockingClamp clamp;
SemicolonMogoMech mogomech;
Goalcover goalcover;
RingMech ringmech;

void on_center_button() {}

void initialize() {
	arm.init();
	clamp.init();
	mogomech.init();
	goalcover.init();
	ringmech.init();
}

void disabled() {}

void competition_initialize() {
	arm.init();
	clamp.init();
	mogomech.init();
	goalcover.init();
	ringmech.init();
}

void autonomous() {}

void opcontrol() {
	std::cout << "OP control starting..." << std::endl;
	while(true) {
		drive.driveExponentialArcade();
		arm.operate();
		clamp.operate();
		mogomech.operate();
		goalcover.operate();
		ringmech.operate();
		pros::delay(20);
	}
}
#include "main.h"

pros::Controller master (pros::E_CONTROLLER_MASTER);
SixMotorDrive drive;

void on_center_button() {}

void initialize() {}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	while(true) {
		drive.driveExponentialArcade(pros::E_CONTROLLER_ANALOG_LEFT_Y, pros::E_CONTROLLER_ANALOG_LEFT_X);
		pros::delay(20);
	}
}

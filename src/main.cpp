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
		drive.driveExponentialArcade();
		pros::delay(20);
	}
}

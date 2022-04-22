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

bool autonPhase;

void on_center_button() {}

void initialize() {
	arm.init();
	clamp.init();
	mogomech.init();
	goalcover.init();
	ringmech.init();
	drive.init();
	pros::lcd::initialize();
	pros::lcd::register_btn0_cb ( LLEMUbtn1 );
	pros::lcd::register_btn1_cb ( LLEMUbtn2 );
	pros::lcd::register_btn2_cb ( LLEMUbtn3 );
	armAuton();
}

void disabled() {
	
}

void competition_initialize() {
	armAuton();
}

void autonomous() {
	runAuton();

}

void opcontrol() {
	std::cout << "OP control starting..." << std::endl;
	autonPhase = false;
	ArmPID::disableArmPID();
	while(true) {
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)
			&& master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)
			&& master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)
			&& master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)
			&& master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) armAuton();
		drive.driveExponentialArcade();
		arm.operate();
		clamp.operate();
		mogomech.operate();
		goalcover.operate();
		ringmech.operate();
		pros::delay(20);
	}
}

/**
 * @brief returns if auton phase is running
 * 
 * @return true: auton phase is running or game didn't start yet
 * @return false: driver control phase is running or ran before
 */
bool isAutonPhase() {
	return autonPhase;
}

void armAuton()	{
	autonPhase = true;
	DrivePID::initDrivePID();
	ArmPID::initArmPID();
}
/**
 * @brief Get the drive object
 * 
 * @return SixMotorDrive object
 */
SixMotorDrive getDrive() {
	return drive;
}

/////////////////////////////////////////////
// AUTONSSSSSSSSSS
/////////////////////////////////////////////
std::string autonDescr1 = "1";
std::string autonDescr2 = "2";
std::string autonDescr3 = "3";

int autonSelection = 1;

void runAuton(void) {
    if(autonSelection == 1) auton1();
    if(autonSelection == 2) auton2();
    if(autonSelection == 3) auton3();
}
void printAutonDescription() {
	pros::lcd::print(0, "Selected Auton: %d", autonSelection);
    if(autonSelection == 1) pros::lcd::print(1, "%s", autonDescr1);
	if(autonSelection == 2) pros::lcd::print(1, "%s", autonDescr2);
	if(autonSelection == 3) pros::lcd::print(1, "%s", autonDescr3);
}

/////////////////////////////////////////////
// AUTON ONE (1)
/////////////////////////////////////////////
void auton1(void) {
    master.print(0, 0, "Auton 1 Running");
	clamp.open();
	goalcover.down();
	DrivePID::drivePID(38, 0);
	DrivePID::isClear();
	clamp.close();
	pros::delay(150);
	DrivePID::drivePID(-30, 0);
}

/////////////////////////////////////////////
// AUTON TWO (2)
/////////////////////////////////////////////
void auton2(void) {
    master.print(0, 0, "Auton 2 Running");
}

/////////////////////////////////////////////
// AUTON THREE (3)
/////////////////////////////////////////////
void auton3(void) {
    master.print(0, 0, "Auton 3 Running");
	DrivePID::reverseIntoMogo();
}

/////////////////////////////////////////////
// MENU BUTTONS
/////////////////////////////////////////////

void LLEMUbtn1(void) {
    autonSelection = 1;
    printAutonDescription();
}

void LLEMUbtn2(void) {
    autonSelection = 2;
    printAutonDescription();
}

void LLEMUbtn3(void) {
    autonSelection = 3;
    printAutonDescription();
}
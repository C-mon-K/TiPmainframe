/**
 * @file pid.cpp
 * @author Simon Kloos (sk.dev@alb.one)
 * @brief based on and modified "C++ VEXCode V5 Text Tutorials - Autonomous PID and Multitasking" by Connor 1814D
 * @version 0.1
 * @date 2022-04-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"


namespace DrivePID {
    pros::IMU imu (INERT_PORT);
    pros::ADIDigitalOut yellowLED (LED_YELLOW_PORT);
    pros::ADIDigitalOut greenLED (LED_GREEN_PORT);
    pros::ADIDigitalOut redLED (LED_RED_PORT);
    pros::Distance distance (DIST_REAR_PORT);
    bool autonClear = false;
    bool sprinting = false;

    namespace lateral {
        double kP = 43.0;
        double kI = 0.0;
        double kD = 112.5;

        double error = 0;
        double prevError = 0;
        double derivative = 0;
        double integral = 0;

        double position;
        double motorPower;
        double desiredValue;
    }
    namespace turn {
        double kP = 165.0; //110
        double kI = 0.0;
        double kD = 390.0; //75.5;    

        double error = 0;
        double prevError = 0;
        double derivative = 0;
        double integral = 0;
        
        double position;
        double motorPower;
        double desiredValue;
    }
    bool motorTaring = false;

    void drivePIDfunction() {

        while(imu.is_calibrating()) { pros::delay(50); }
        yellowLED.set_value(false);
        master.print(2,0, "auton armed");
        while(isAutonPhase()) {
            if(motorTaring) {
                motorTaring = false;
                MR1.tare_position();
                MR2.tare_position();
                MR3.tare_position();
                ML1.tare_position();
                ML2.tare_position();
                ML3.tare_position();
            }

            int MR1degrees = MR1.get_position();
            int MR2degrees = MR2.get_position();
            int MR3degrees = MR3.get_position();
            int ML1degrees = ML1.get_position();
            int ML2degrees = ML2.get_position();
            int ML3degrees = ML3.get_position();

            int leftMotorPosition =  (ML1degrees + ML2degrees + ML3degrees)/3;
            int rightMotorPosition = (MR1degrees + MR2degrees + MR3degrees)/3;
    /////////////////////////////////////
    // LATERAL MOVEMENT PID
    /////////////////////////////////////
            lateral::position = (leftMotorPosition + rightMotorPosition)/2;

            lateral::error = lateral::desiredValue - lateral::position;
            lateral::derivative = lateral::error - lateral::prevError;
            lateral::integral += lateral::error;

            lateral::motorPower = (lateral::error * lateral::kP + lateral::integral * lateral::kI 
                + lateral::derivative * lateral::kD);

    /////////////////////////////////////   
    // TURN MOVEMENT PID
    /////////////////////////////////////
            turn::position = imu.get_rotation();

            turn::error = turn::desiredValue - turn::position;
            turn::derivative = turn::error - turn::prevError;
            //turn::integral += turn::error;

            turn::motorPower = (turn::error * turn::kP + turn::integral * turn::kI 
                + turn::derivative * turn::kD);

            if(turn::motorPower>10000) turn::motorPower = 10000;

    /////////////////////////////////////
    // 
    /////////////////////////////////////
            if(!sprinting) getDrive().move_voltage( lateral::motorPower + turn::motorPower, lateral::motorPower - turn::motorPower);
            lateral::prevError = lateral::error;
            turn::prevError = turn::error;

            if(MR1.get_actual_velocity() != 0 || ML1.get_actual_velocity() != 0) autonClear = false;
            else autonClear = true;

            pros::delay(20);
        }
        master.print(2,0, "auton disabled");
        yellowLED.set_value(true);
        return;
    }

    void drivePID(double distance, double rotation) {
        motorTaring = true;
        sprinting = false;
        lateral::desiredValue = distance*19.8426942;
        turn::desiredValue = rotation;
    }

    bool isClear() {
        pros::delay(70);
	    master.print(0,0, "%d", DrivePID::autonClear);
        while(!autonClear) {pros::delay(50);}
        return DrivePID::autonClear;
    }

    void initDrivePID() {
        motorTaring = true;
        imu.reset();
        greenLED.set_value(false);
        redLED.set_value(true);
        while(imu.is_calibrating()) { pros::delay(50); }
        greenLED.set_value(true);
        redLED.set_value(false);
        pros::Task drivePIDtask (drivePIDfunction);
    }

    void tareMotors() {
        MR1.tare_position();
        MR2.tare_position();
        MR3.tare_position();
        ML1.tare_position();
        ML2.tare_position();
        ML3.tare_position();
    }

    void sprintForward(double distance) {
        sprinting = true;
        tareMotors();
        getDrive().move_voltage(12000, 12000);
        double avgPosition;
        while(true) {
            avgPosition = (MR1.get_position()+MR2.get_position()+MR3.get_position()+ML1.get_position()+ML2.get_position()+ML3.get_position())/6;
            if(avgPosition >= distance*19.8426942) break;
            pros::delay(20);
        }
        sprinting = false;
    }

    void reverseIntoMogo() {
        sprinting = true;
        mogomech.drop();
        mogomech.open();
        getDrive().move(-80, -80);
        while((distance.get() > 219)) {
            pros::lcd::print(2, "Rear Mogo Sensor: %dmm", distance.get());
            pros::delay(20);
        }
        //pros::delay(100);
        mogomech.close();
        getDrive().move(0, 0);
        pros::delay(100);
        mogomech.tilt();
        sprinting = false;
    }
}

namespace ArmPID {
    double kP = 0.04;
    double kI = 0.0;
    double kD = 0.08;

    double desiredAngle = 0;

    double angle = 0;

    double error = 0;
    double prevError = 0;
    double derivative = 0;
    double integral = 0;

    double motorPower = 0;

    bool armAutonRunning = true;

    void armPIDfunction() {
        while(true) {
            if(armAutonRunning) {
                if(!isAutonPhase() && (master.get_analog(STICK_ARM) != 0)) armAutonRunning = false;
                else {
                    angle = ROT_ARM.get_angle();
                    if(angle > 30000) { angle = angle - 36000; }

                    error = desiredAngle - angle;
                    derivative = error - prevError;
                    integral += error;
                    prevError = error;

                    motorPower = kP * error + kI * integral + kD * derivative;
                    if((motorPower < 0 && angle < 0) || (motorPower > 0 && angle > 9500)) {
                         ARM.brake();
                         motorPower=0;
                    }
                    ARM.move_velocity(motorPower);
                }
            }
            pros::delay(20);
        }
    }

    void armPID(double inputAngle) {
        armAutonRunning = true;
        desiredAngle = inputAngle;
    }

    void initArmPID() {
	    pros::Task armPIDTask (ArmPID::armPIDfunction);
    }

    void isArmClear() {
        pros::delay(70);
        while(ARM.get_actual_velocity() != 0) { pros::delay(50); }
        return;
    }

    bool isArmAutonRunning() {
        return armAutonRunning;
    }

    void disableArmPID() {
        armAutonRunning = false;
    }

}
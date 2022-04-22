#pragma once

#include "main.h"


namespace DrivePID {
    void drivePIDfunction();
    void drivePID(double distance, double rotation);
    bool isClear(void);
    void initDrivePID(void);
    void sprintForward(double distance);
    void tareMotors(void);
    void reverseIntoMogo(void);
};
namespace ArmPID {
    void armPIDfunction(void);
    void armPID(double desiredAngle);
    void initArmPID(void);
    void disableArmPID(void);
    void isArmClear(void);
    bool isArmAutonRunning(void);
};



#pragma once

#include "main.h"

#define DRIVE_UP_SPEED 127*0.7
#define DRIVE_DOWN_SPEED -127

extern pros::Motor ARM;
extern pros::Rotation ROT_ARM;

class Arm{
public:
    Arm();
private:
    void moveUp();
    void moveDown();
    void moveTo(int degrees);
};
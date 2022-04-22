/**
 * @file arm.h
 * @author Simon Kloos (sk.dev@alb.one)
 * @brief arm header file
 * @version 0.1
 * @date 2022-03-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "main.h"

#define DRIVE_UP_SPEED 127*0.7
#define DRIVE_DOWN_SPEED -127

extern pros::Motor ARM;
extern pros::Rotation ROT_ARM;



class Arm{
public:
    Arm();
    void operate();
    void moveUp();
    void moveDown();
    void stop();
    void init();
    static void shake();
    void home();
    void up();
    static bool isArmLow() {
        return ROT_ARM.get_angle() < 1000;
    };
    void moveTo(int angle);
};
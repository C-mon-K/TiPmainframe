#include "mogomech.h"

pros::ADIDigitalOut TILT1 (MOGO_TILT1);
pros::ADIDigitalOut TILT2 (MOGO_TILT2);
pros::ADIDigitalOut MOGO (MOGO_CLAMP);

bool closed = false;
bool tilted = false;

SemicolonMogoMech::SemicolonMogoMech() {};

void SemicolonMogoMech::init() {    
    open();
    drop();
}

void SemicolonMogoMech::open() {
    MOGO.set_value(false);
    closed = false;
}

void SemicolonMogoMech::close() {
    MOGO.set_value(true);
    closed = true;
}

void SemicolonMogoMech::tilt() {
    TILT1.set_value(false);
    TILT2.set_value(false);
    tilted = true;
}

void SemicolonMogoMech::drop() {
    TILT1.set_value(true);
    TILT2.set_value(true);
    tilted = false;
}

void SemicolonMogoMech::toggleTilt() {
    if(tilted) drop();
    else tilt();
}

void SemicolonMogoMech::toggleClamp() {
    if(closed) open();
    else close();
}

void SemicolonMogoMech::operate() {
    if(master.get_digital_new_press(BUTTON_MOGO_MECH_CLAMP)) toggleClamp();
    if(master.get_digital_new_press(BUTTON_MOGO_MECH_TILT)) toggleTilt();
}
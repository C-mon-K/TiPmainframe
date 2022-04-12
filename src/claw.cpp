#include "claw.h"

pros::ADIDigitalOut CLAMP (CLAMP_PORT);
bool opened = false;

LockingClamp::LockingClamp() {}

void LockingClamp::init() {
    close();
}

void LockingClamp::toggle() {
    if(opened) {
        close();
        return;
    }
    else { open(); }
}

void LockingClamp::close() {
    CLAMP.set_value(true);
    opened = false;

}
void LockingClamp::open() {
    CLAMP.set_value(false);
    opened = true;

}

void LockingClamp::operate() {
    if(master.get_digital_new_press(BUTTON_FRONT_CLAMP)) toggle();
}
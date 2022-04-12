#include "ringmech.h"

#define RING_OFF 0
#define RING_UP 1
#define RING_DOWN 2

pros::Motor RING_MECH (CONV_PORT);

int status = RING_OFF;

RingMech::RingMech() {}

void RingMech::init() {
    RING_MECH.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void RingMech::up() {
    RING_MECH.move(127);
    status = RING_UP;
}

void RingMech::down() {
    RING_MECH.move(-127);
    status = RING_DOWN;
}

void RingMech::stop() {
    RING_MECH.move(0);
    status = RING_OFF;
}

void RingMech::operate() {

    if(Arm::isArmLow()) {
        stop();
        return;
    }

    bool inputUp = master.get_digital_new_press(BUTTON_RING_MECH_UP);
    bool inputDown = master.get_digital_new_press(BUTTON_RING_MECH_DOWN);

    if(inputUp && inputDown) {
        stop();
        return;
    }
    
    if(inputUp) {
        if(status==RING_UP) {
            stop();
            return;
        }
        up();
        return;
    }
    if(inputDown) {
        if(status==RING_DOWN) {
            stop();
            return;
        }
        down();
        return;
    }


}
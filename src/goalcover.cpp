#include "goalcover.h"

pros::ADIDigitalOut GOALCOVER (GOALCOVER_PORT);

bool cover_down = false;

Goalcover::Goalcover() {}

void Goalcover::init() {
    down();
}

void Goalcover::down() {
    GOALCOVER.set_value(true);
    cover_down = true;
}

void Goalcover::up() {
    GOALCOVER.set_value(false);
    cover_down = false;
}

void Goalcover::toggle() {
    if(cover_down) up();
    else down();
}

void Goalcover::operate() {
    if(master.get_digital_new_press(BUTTON_COVER)) toggle();
}
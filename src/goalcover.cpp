/**
 * @file goalcover.cpp
 * @author (sk.dev@alb.one)
 * @brief 
 * @version 0.1
 * @date 2022-04-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "goalcover.h"

pros::ADIDigitalOut GOALCOVER (GOALCOVER_PORT);

bool cover_down = false;
/**
 * @brief Construct a new Goalcover::Goalcover object
 * 
 */
Goalcover::Goalcover() {}

/**
 * @brief initializes the goalcover (cover down)
 * 
 */
void Goalcover::init() {
    up();
}

/**
 * @brief drives the cover down
 * 
 */
void Goalcover::down() {
    GOALCOVER.set_value(true);
    cover_down = true;
}

/**
 * @brief drives the cover up
 * 
 */
void Goalcover::up() {
    GOALCOVER.set_value(false);
    cover_down = false;
}

/**
 * @brief toggles the cover between up <---> down
 * 
 */
void Goalcover::toggle() {
    if(cover_down) up();
    else down();
}

/**
 * @brief operates the goal; IF button pressed THEN toggle cover
 * 
 */
void Goalcover::operate() {
    if(master.get_digital_new_press(BUTTON_COVER)) toggle();
}
#pragma once

#include "main.h"

class SemicolonMogoMech {
public:
    SemicolonMogoMech();
    void init(); 
    void open();
    void close();
    void tilt();
    void drop();
    void toggleTilt();
    void toggleClamp();
    void operate();
};
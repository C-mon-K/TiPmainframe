#pragma once

#include "main.h"

class LockingClamp {
public:
    LockingClamp();
    void init();
    void toggle();
    void close();
    void open();
    void operate();
};
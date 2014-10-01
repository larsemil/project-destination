#include "Subsystem.hpp"

Subsystem::Subsystem(SubsysType type, int x, int y, int w, int h,
        int weight, int maxIntegrity, int powerDrain)
{
    _x = x;
    _y = y;
    _w = w;
    _h = h;
    _weight = weight;
    _maxIntegrity = maxIntegrity;
    _integrity = maxIntegrity;
    _powerDrain = powerDrain;
}


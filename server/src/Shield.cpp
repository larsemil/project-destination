#include "Shield.hpp"

Shield::Shield(int maxCapacity, int x, int y, int w, int h,
    int weight, int maxIntegrity, int powerDrain) :
  Subsystem(SUB_SHIELD, x, y, w, h, weight, maxIntegrity, powerDrain)
{
  _maxCapacity = maxCapacity;
  _capacity = maxCapacity;
}

#ifndef SHIELD_H
#define SHIELD_H

#include "Subsystem.hpp"

class Shield : public Subsystem
{
  private:
    int _maxCapacity;
    int _capacity;

  public:
    Shield(int maxCapacity, int x, int y, int w, int h,
        int weight, int maxIntegrity, int powerDrain);

    int GetCapacity() { return _capacity; }
    void SetCapacity(int capacity) { _capacity = capacity; }
};

#endif

#ifndef ENGINE_H
#define ENGINE_H

#include "Subsystem.hpp"

class Engine : public Subsystem
{
  private:
    int _energyOutput;
    int _power;

  public:
    Engine(int energyOutput, int power, int x, int y, int w, int h,
        int weight, int maxIntegrity, int powerDrain);

    const int GetEnergyOutput() const { return _energyOutput; }
    const int GetPower() const { return _power; }
};

#endif

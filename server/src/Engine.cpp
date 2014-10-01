#include "Engine.hpp"

Engine::Engine(int energyOutput, int power, int x, int y, int w, int h,
    int weight, int maxIntegrity, int energyDrain) :
  Subsystem(SUB_ENGINE, x, y, w, h, weight, maxIntegrity, energyDrain)
{
  _energyOutput = energyOutput;
  _power = power;
}

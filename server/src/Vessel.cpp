#include <cmath>
#include <iostream>
#include <string>
//#include "GameEngine.hpp"
#include "Engine.hpp"
#include "Vessel.hpp"
#include "vkeys.hpp"
#include "functions.hpp"

Vessel::Vessel(int id, std::string name,
    const std::vector<Subsystem*>& subsystems, double x, double y,
    double rot, Vector2d vel, double spin) :
  Entity(0, x, y, rot, vel, spin)
{
  std::cout << name << "::Vessel" << std::endl;

  /* Basic initialization */
  _id = id;
  _isAlive = true;
  _name = name;

  /* Characteristics reseting */

  /* Subsystems update */
  _subsystems = subsystems;
  UpdateSubsystems();
}

Vessel::~Vessel()
{
  std::cout << _name << "::~Vessel()" << std::endl;
  while (!_subsystems.empty())
  {
    if (_subsystems.back())
      delete _subsystems.back();
    _subsystems.pop_back();
  }
}

void Vessel::SetWeaponTarget(Vessel* target)
{
  //std::cout << "'" << _name << "'" << "::SetWeaponTarget()" << std::endl;
  /* FIXME */
}

void Vessel::UpdateSubsystems()
{
  _enginePower = 0;
  _energyOutput = 0;
  _size = 0;
  _signature = 0;
  _weight = 0;
  _crewCapacity = 0;

  for (unsigned int i = 0; i < _subsystems.size(); ++i)
  {
    Subsystem* current = _subsystems.at(i);

    _size += current->GetSize();
    _weight += current->GetWeight();
    _powerDrain += current->GetPowerDrain();

    switch (current->GetType())
    {
      case SUB_ARMAMENT:
        break;
      case SUB_ENGINE:
        _enginePower += ((Engine*)current)->GetPower();
        _energyOutput += ((Engine*)current)->GetEnergyOutput();
        break;
      case SUB_SHIELD:
        break;
      case SUB_SENSOR:
        break;
      case SUB_CARGO:
        break;
      case SUB_QUARTERS:
        break;
      case SUB_INFIRMARY:
        break;
      case SUB_SECURITY:
        break;
    }
  }
}

void Vessel::TakeDamage()
{
  //std::cout << "'" << _name << "'" << "::TakeDamage()" << std::endl;

  /* FIXME
  if (_shield.GetCapacity() > armament->GetShieldImpact())
  {
    _shield.TakeDamage(armament->GetShieldImpact());
    std::cout << _name << " takes " << armament->GetShieldImpact()
      << " shield damage!" << std::endl;
  }
  else
  {
    double hullImpact = armament->GetHullEffect() *
      (armament->GetImpact() -
       _shield.GetCapacity() / armament->GetShieldEffect());
    _shield.SetCapacity(0);
    _hull.TakeDamage(hullImpact);
    std::cout << _name << " takes " << hullImpact << " hull damage!"
      << std::endl;
  }

  std::cout << _name << " has " << _shield.GetCapacity() << " shield and "
    << _hull.GetIntegrity() << " hull integrity. " << std::endl;

  if (_hull.GetIntegrity() <= 0)
  {
    Destroy();
  }
  */
}

void Vessel::Destroy()
{
  std::cout << _name << "::Destroy()" << std::endl;
  _isAlive = false;
}

void Vessel::HandleEvent(const SDL_Event& event)
{
  /* FIXME
     if (event.type == SDL_KEYDOWN)
     {
     switch(event.key.keysym.sym)
     {
     case SDLK_LEFT:
     _steering += 0.1;
     break;
     case SDLK_RIGHT:
     _steering -= 0.1;
     break;
     case FORWARD:
     _throttle += 0.1;
     break;
     case BACKWARD:
     _throttle -= 0.1;
     break;
     default:
     std::cerr << "Unkown signal: " << signal << std::endl;
     }
     }
   */
}

void Vessel::Update()
{
  //std::cout << _name << "::Update()" << std::endl;

  Uint8* keyState = (Uint8*)_player;//->GetKeyState();

  if (keyState[VK_UP])
    _throttle = _throttle + 10 < 100 ? _throttle + 10 : 100;
  else if (keyState[VK_DOWN])
    _throttle = _throttle - 10 > 0 ? _throttle - 10 : 0;
  else if (keyState[VK_STOP])
    _throttle = 0;

  if (keyState[VK_LEFT])
    _steering = 100;
  else if (keyState[VK_RIGHT])
    _steering = -100;
  else
    _steering = 0;

  _rot += (_enginePower * _steering) / _mass;
  while (_rot > 360.0)
    _rot -= 360.0;
  while (_rot < 0.0)
    _rot += 360.0;

  double thrust = (_throttle * _enginePower) / _mass;
  Vector2d acc = Vector2d(thrust * cos(deg2rad(_rot)), thrust * sin(deg2rad(_rot)));
  _vel += acc;
  _pos += _vel;

  std::cout << "\r" << _pos.X() << ", " << _pos.X();
}

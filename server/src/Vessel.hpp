#ifndef VESSEL_H
#define VESSEL_H

#include <vector>
#include <SDL/SDL.h>
#include "Entity.hpp"
#include "Subsystem.hpp"
#include "Vector2d.hpp"

class Vessel : public Entity
{
  private:
    /* ID for indexing ship */
    int _id;

    /* The player instance who owns the ship */
    int* _player;

    /* Indicates whether the ship is alive or not */
    bool _isAlive;

    /* A human readable name on the ship */
    std::string _name;

    /* The list of subsystems on board the ship */
    std::vector<Subsystem*> _subsystems;

    /* Controls for the ship */
    int _steering;
    int _throttle;

    /* Characteristics for this particular ship */
    int _enginePower;   /* How much power the ship has to move with */
    int _energyOutput;  /* The engine's electrical energy output */
    int _size;          /* A function of number and size of subsystems */
    int _weight;        /* The weight of the ship's subsystems */
    int _powerDrain;    /* The amount of energy required by the subsystems */
    int _signature;     /* How wasy the ship is to spot with scanners */
    int _crewCapacity;  /* How many crew members the ship can keep */

  public:
    Vessel() { }
    Vessel(int id, std::string name,
        const std::vector<Subsystem*>& subsystems, double x, double y,
        double rot, Vector2d vel, double spin);
    ~Vessel();

    const std::string GetName() const { return _name; }
    const bool IsAlive() const { return _isAlive; }

    void SetWeaponTarget(Vessel* vessel);
    void UpdateSubsystems();

    void TakeDamage();
    void Destroy();

    void HandleEvent(const SDL_Event& event);
    void Update();
};

#endif

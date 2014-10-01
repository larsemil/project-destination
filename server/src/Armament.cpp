#include <iostream>
#include "Armament.hpp"

Armament::Armament(Vessel* parent, std::string type, std::string model,
    double impact, double shieldEffect, double hullEffect, double range,
    int maxCooldown, int burstRate, int ammoCount, int x, int y, int w, int h,
    int weight, int maxIntegrity, int energyDrain) :
  Subsystem(SUB_ARMAMENT, x, y, w, h, weight, maxIntegrity, energyDrain)
{
  _parent = parent;
  _type = type;
  _model = model;
  _impact = impact;
  _shieldEffect = shieldEffect;
  _hullEffect = hullEffect;
  _range = range;
  _maxCooldown = maxCooldown;
  _cooldown = 0;
  _burstRate = burstRate;
  _ammoCount = ammoCount;
  _target = NULL;
}

void Armament::SetParent(Vessel* parent)
{
  _parent = parent;
}

/* If _target is not NULL, the weapon will try to fire at it in the next
   update.  We can't use a reference here because we need the NULL metadata
   when there is no target. */
void Armament::SetTarget(Vessel* target)
{
  //std::cout << "Armament::SetTarget" << std::endl;
  _target = target;
}

/* After all events are handled, update the game logic before drawing */
void Armament::Update()
{
  //std::cout << "Armament::Update" << std::endl;
  if (_cooldown > 0)
    --_cooldown;

  /* Check if something is targeted, if the weapons is ready to fire
     and if the target is within range. If so, fire. */
  if (_target != NULL)
  {
    if (_cooldown == 0 && _ammoCount > 0
        && abs(_parent->GetPos().Mag() - _target->GetPos().Mag())
        <= _range)
    {
      /* FIXME
         std::cout << _model << " fires " << _burstRate << " time(s) at "
         << _target->GetName() << "!" << std::endl;

         _target->TakeDamage(this);
         _ammoCount -= _burstRate;

         std::cout << _model << " has " << _ammoCount << " rounds left."
         << std::endl;
       */

      /* If the target was destroyed, the pointer needs to be reset */
      if (!_target->IsAlive())
        _target = NULL;

      /* Prevent the weapon from firing again until it has cooled down. */
      _cooldown = _maxCooldown;
    }
  }
}

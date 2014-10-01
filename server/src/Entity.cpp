#include "Entity.hpp"

Entity::Entity(int mass, double x, double y, double rot, Vector2d vel, double spin)
{
  _isAlive = true;
  _mass = mass;
  _pos.X(x);
  _pos.Y(y);
  _rot = rot;
  _vel = vel;
  _spin = spin;
}

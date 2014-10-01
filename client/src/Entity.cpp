#include "Entity.hpp"

Entity::Entity(float x, float y, float rot)
{
  _isAlive = true;
  _pos.X(x);
  _pos.Y(y);
  _rot = rot;
}

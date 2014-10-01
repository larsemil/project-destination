// ===================================
// <copyright>Christofer Odén</copyright>
// <email>mailto:bei.oden@gmail.com</email>
// <license>GNU General Public License</license>
// <created>Sunday, January 23, 2011</created>
// ===================================

#include <cmath>
#include "Vector2d.hpp"

Vector2d::Vector2d(const Vector2d& vector)
{
	X(vector.X());
	Y(vector.Y());
}

void Vector2d::Rotate(double radians)
{
	double x1 = _x * cos(radians) - _y * sin(radians);
	double y1 = _x * sin(radians) + _y * cos(radians);
	_x = x1;
	_y = y1;
}

Vector2d& Vector2d::operator = (const Vector2d &rhs)
{
	if (this != &rhs)
  {
    X(rhs.X());
    Y(rhs.Y());
  }

	return *this;
}

Vector2d& Vector2d::operator += (const double rhs)
{
  X(X() + rhs);
  Y(Y() + rhs);

  return *this;
}

Vector2d& Vector2d::operator += (const Vector2d &rhs)
{
	X(X() + rhs.X());
	Y(Y() + rhs.Y());

	return *this;
}

const Vector2d Vector2d::operator + (const double rhs) const
{
  return Vector2d(*this) += rhs;
}

const Vector2d Vector2d::operator + (const Vector2d &rhs) const
{
  return Vector2d(*this) += rhs;
}

bool Vector2d::operator == (const Vector2d &rhs) const
{
  return (X() == rhs.X() && Y() == rhs.Y());
}

bool Vector2d::operator != (const Vector2d &rhs) const
{
  return !(*this == rhs);
}

double Vector2d::operator [] (unsigned int index)
{
	switch (index)
	{
	case 0:
		return _x;
		break;
	case 1:
		return _y;
		break;
	default:
		throw "Index must be 0 or 1.";
	}
}

double Distance(const Vector2d& lhs, const Vector2d& rhs)
{
    return sqrt(pow(rhs.X() - lhs.X(), 2) +
            pow(rhs.Y() - lhs.Y(), 2));
}

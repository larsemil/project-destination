// ===================================
// <copyright>Christofer Odén</copyright>
// <email>mailto:bei.oden@gmail.com</email>
// <license>GNU General Public License</license>
// <created>Sunday, January 23, 2011</created>
// ===================================

/* Euclidean vector class */

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>

typedef double vtype;

class Vector2d
{
private:
	double _x;
	double _y;
public:
	Vector2d() { _x = 0; _y = 0; }
	Vector2d(const Vector2d& vector);
	Vector2d(double x, double y) { _x = x; _y = y; }

	double X() const { return _x; }
	double Y() const { return _y; }
  double Mag() const { return sqrt(_x * _x + _y * _y); }
  Vector2d Unit() const { return Vector2d(X() / Mag(), Y() / Mag()); }

  void X(double x) { _x = x; }
	void Y(double y) { _y = y; }

	void Rotate(double radians);

	Vector2d& operator = (const Vector2d &rhs);
	Vector2d& operator += (const double rhs);
	Vector2d& operator += (const Vector2d &rhs);
	const Vector2d operator + (const double rhs) const;
	const Vector2d operator + (const Vector2d &rhs) const;
  bool operator == (const Vector2d &rhs) const;
  bool operator != (const Vector2d &rhs) const;
	double operator [] (unsigned int index);
};

double Distance(const Vector2d& lhs, const Vector2d& rhs);

#endif

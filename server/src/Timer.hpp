// ===================================
// <copyright>Christofer Odén</copyright>
// <email>mailto:bei.oden@gmail.com</email>
// <license>GNU General Public License</license>
// <created>Sunday, January 23, 2011</created>
// ===================================

#ifndef TIMER_H
#define TIMER_H

#include <SDL/SDL.h>

class Timer
{
private:
	int _t0;
public:
	void Mark() { _t0 = SDL_GetTicks(); }
	int GetTicks() { return SDL_GetTicks() - _t0; }
};

#endif
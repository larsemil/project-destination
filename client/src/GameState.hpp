// ===================================
// <copyright>Christofer Odén</copyright>
// <email>mailto:bei.oden@gmail.com</email>
// <license>GNU General Public License</license>
// <created>Sunday, January 23, 2011</created>
// ===================================

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL/SDL.h>

class GameState
{
public:
	virtual void HandleEvent(const SDL_Event& event) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

#endif //GAMESTATE_H

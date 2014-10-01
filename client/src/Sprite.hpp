#ifndef SPRITE_H
#define SPRITE_H

#include <SDL/SDL.h>
#include "Vector2d.hpp"

class Sprite
{
    private:
        bool _isAlive;
        Vector2d _position;
        Vector2d _vector;
        int _life;

    public:
        Sprite(Vector2d position, Vector2d vector, int life);

        void HandleEvents(const SDL_Event &event) {}
        void Update();
        void Draw();
};

#endif

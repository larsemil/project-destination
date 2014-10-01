#ifndef ENTITY_H
#define ENTITY_H

#include <SDL/SDL.h>
#include "Vector2d.hpp"

class Entity
{
    protected:
        bool _isAlive;

        Vector2d _pos;
        double _rot;

    public:
        Entity() {}
        Entity(float x, float y, float rot);

        const Vector2d GetPos() const { return _pos; }
        const double GetRot() const { return _rot; }

        virtual void HandleEvent(const SDL_Event& event) = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;

        void Destroy() { _isAlive = false; }
};

#endif


#ifndef ENTITY_H
#define ENTITY_H

#include <SDL/SDL.h>
#include "Vector2d.hpp"

class Entity
{
    protected:
        bool _isAlive;

        int _mass;
        Vector2d _pos;
        double _rot;

        Vector2d _vel;
        double _spin;

    public:
        Entity() {}
        Entity(int _mass, double x, double y, double rot, Vector2d vel=Vector2d(),
            double spin=0);

        const Vector2d GetPos() const { return _pos; }
        const double GetRot() const { return _rot; }
        const Vector2d GetVel() const { return _vel; }
        const double GetSpin() const { return _spin; }

        virtual void HandleEvent(const SDL_Event& event) = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;

        void Destroy() { _isAlive = false; }
};

#endif


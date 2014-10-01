#ifndef STATEVESSELTEST_H
#define STATEVESSELTEST_H

#include <SDL/SDL.h>
#include "GameState.hpp"
#include "Vessel.hpp"

class GSMain : public GameState
{
    private:
        float _zoomFactor;
        int _nextId;

        std::vector<Entity*> _entities;

    public:
        GSMain();
        ~GSMain();

        int GetNextId() { return ++_nextId; }

        void HandleEvent(const SDL_Event& event);
        void Update();
        void Draw();
};

#endif

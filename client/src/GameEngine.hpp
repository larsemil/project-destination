// ===================================
// <copyright>Christofer Odén</copyright>
// <email>mailto:bei.oden@gmail.com</email>
// <license>GNU General Public License</license>
// <created>Sunday, January 23, 2011</created>
// ===================================

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "GameState.hpp"
#include "ClientSocket.hpp"
#include "Timer.hpp"

const int FPS_TARGET = 100;
const int TICKS_PER_FRAME = (int)(1000.0 / FPS_TARGET + 0.5);

class GameEngine
{
  private:
    GameEngine() {};

    static GameEngine* _instance;

    ClientSocket _socket;

    Timer _frameTimer;
    bool _isRunning;
    int _currentFps;

    std::vector<GameState*> _gameStates;

  public:
    static GameEngine* Instance();
    void Initialize(const SDL_Rect& screenSize);
    void Start();
    void Quit();

    void Send(const SDL_Event &event) const;
    int Music(Mix_Chunk*& channel);
	void Sound();

    void PushState(GameState* gameState);
    void PopState();
    void ChangeState(GameState* gameState);

    void HandleEvents();
    void Update();
    void Draw();
};

#endif

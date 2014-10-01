// ===================================
// <copyright>Christofer Odén</copyright>
// <email>mailto:bei.oden@gmail.com</email>
// <license>GNU General Public License</license>
// <created>Sunday, January 23, 2011</created>
// ===================================

/* This is the server version of the game engine */

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include <SDL/SDL.h>
#include "Timer.hpp"
#include "Player.hpp"
#include "ServerSocket.hpp"
//#include "Vector2d.hpp"

const int FPS_TARGET = 100;
const int TICKS_PER_FRAME = (int)(1000.0 / FPS_TARGET + 0.5);

class GameEngine
{
  private:
    GameEngine() {};

    static GameEngine* _instance;

    bool _isRunning;

    ServerSocket _socket;

    Timer _frameTimer;
    int _currentFps;
    int _pingTimer;

    int _nextId;

    std::vector<Player*> _players;

  public:
    static GameEngine* Instance();
    ~GameEngine();

    void Initialize();
    void Start();
    int GetNextId();
    void Quit();

    void RecieveEvents();
    void Update();
    void Broadcast();
};

#endif

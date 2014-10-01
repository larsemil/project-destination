// ===================================
// <copyright>Christofer Odén</copyright>
// <email>mailto:bei.oden@gmail.com</email>
// <license>GNU General Public License</license>
// <created>Sunday, January 23, 2011</created>
// ===================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GameEngine.hpp"
#include "Player.hpp"

GameEngine* GameEngine::_instance = NULL;

GameEngine::~GameEngine()
{
  while (!_players.empty())
  {
    delete _players.back();
    _players.pop_back();
  }
}

GameEngine* GameEngine::Instance()
{
  if (!_instance)
  {
    _instance = new GameEngine();
  }

  return _instance;
}

void GameEngine::Initialize()
{
  std::cout << "GameEngine::Initialize" << std::endl;

  // Set up listening UDP socket
  _socket = ServerSocket("5001");

  // Initialize the timer funtionality
  SDL_Init(SDL_INIT_TIMER);

  // Offering to the Random Number God
  srand((unsigned int)time(NULL));
}

void GameEngine::Start()
{
  Uint32 nextSecond = SDL_GetTicks() + 1000;
  int frames = 0;

  _isRunning = true;
  while (_isRunning)
  {
    _frameTimer.Mark();

    RecieveEvents();
    Update();
    Broadcast();

    if (_frameTimer.GetTicks() < TICKS_PER_FRAME)
      SDL_Delay(TICKS_PER_FRAME - _frameTimer.GetTicks());
    if (SDL_GetTicks() >= nextSecond)
    {
      nextSecond += 1000;
      _currentFps = frames;
      frames = 0;
    }
    ++frames;
  }
}

int GameEngine::GetNextId()
{
  return _nextId++;
}

void GameEngine::Quit()
{
  _isRunning = false;
}

// Handle packets sent by clients
void GameEngine::RecieveEvents()
{
  BasePkt* packet = NULL;
  Player* player;
  std::string address;
  std::string service;

  // Check if there is a packet waiting and process it
  while (_socket.Recieve(&packet, address, service) > 0)
  {
    std::cout << "Received packet from " << address << ":" << service
      << std::endl;

    // Returns NULL if the player is not in the list
    player = SelectPlayer(address, _players);
    if (player == NULL)
      continue;

    // Check if a player wants to join
    if (packet->type == PKT_JOIN)
    {
      // If player is not in the list, add it
      if (player == NULL)
        _players.push_back(new Player(GetNextId(), address,
              ((JoinPkt*)packet)->name));

      // Send the credentials in case the player hasn't got them (UDP)
      _socket.SendCredentials(player);

      // Continue loop to check next packet in line
      continue;
    }

    switch (packet->type)
    {
      case PKT_PING_REPLY:
        // Update player latency
        player->SetLatency(SDL_GetTicks() - ((PingPkt*)packet)->timeOfSending);
        break;
      case PKT_KBD_EVENT:
        // Handle event for player
        break;
      case PKT_MOUSE_EVENT:
        // Handle mouse event for player
        break;
    }
  }

  if (packet)
    delete packet;
}

void GameEngine::Update()
{
  for (unsigned int i = 0; i < _players.size(); ++i)
  {
    _players.at(i)->Update();
  }
}

void GameEngine::Broadcast()
{
  for (unsigned int i = 0; i < _players.size(); ++i)
  {
    _socket.SendWorld(_players.at(i));
  }
}

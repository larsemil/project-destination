// ===================================
// <copyright>Christofer Odén</copyright>
// <email>mailto:bei.oden@gmail.com</email>
// <license>GNU General Public License</license>
// <created>Sunday, January 23, 2011</created>
// ===================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GameEngine.hpp"
#include "GSMain.hpp"

GameEngine* GameEngine::_instance = NULL;

GameEngine* GameEngine::Instance()
{
  if (!_instance)
  {
    _instance = new GameEngine();
  }

  return _instance;
}

void GameEngine::Initialize(const SDL_Rect& screenSize)
{
  std::cout << "GameEngine::Initialize" << std::endl;

  _socket = ClientSocket("0.0.0.0", "5001");

  SDL_Init(SDL_INIT_EVERYTHING);
  srand((unsigned int)time(NULL));

  // Soundstuff
  int audioRate = 22050;
  Uint16 audioFormat = AUDIO_S16SYS;
  int audioChannels = 2;
  int audioBuffers = 4096;

  if(Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers) != 0)
  {
    std::cerr << "Unable to initialize audio: " << Mix_GetError()
      << std::endl;
    throw Mix_GetError();
  }

  // Activate anti-aliasing
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  // Set AA level to 2
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

  if (SDL_SetVideoMode(screenSize.x, screenSize.y, 32,
        SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL) == NULL)
  {
    /* Ugly hack to make it work even if the system doesn't support
       multisampling. [FIXME]*/
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
    if (SDL_SetVideoMode(screenSize.x, screenSize.y, 32,
          SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL) == NULL)
    {
      throw SDL_GetError();
    }
  }

  glViewport(0, 0, screenSize.x, screenSize.y);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, screenSize.x, 0, screenSize.y, 1, -1);
  glMatrixMode(GL_MODELVIEW);
  glClearColor(0, 0.1f, 0, 1.0f);
  glClearDepth(1.0f);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glAlphaFunc(GL_GREATER, 0.1f);

  PushState(new GSMain());
}

void GameEngine::Start()
{
  int ticksPerFrame = (int)(1000.0 / FPS_TARGET + 0.5);
  Uint32 nextSecond = SDL_GetTicks() + 1000;
  int frames = 0;

  Mix_Chunk *track = NULL;
  int channel = 0; 

  _isRunning = true;
  while (_isRunning)
  {
    _frameTimer.Mark();

    HandleEvents();
    Update();
    Draw();

    // If there is no music playing
    if(Mix_Playing(channel) == 0)
      // Play music
      channel = Music(track);

    if (_frameTimer.GetTicks() < ticksPerFrame)
      SDL_Delay(ticksPerFrame - _frameTimer.GetTicks());
    if (SDL_GetTicks() >= nextSecond)
    {
      nextSecond += 1000;
      _currentFps = frames;
      frames = 0;
    }
    ++frames;
  }
}

void GameEngine::Quit()
{
  _isRunning = false;
}

void GameEngine::Send(const SDL_Event& event) const
{
  EventPkt eventPkt;

  if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
  {
    eventPkt.type = event.type;
    eventPkt.button = event.key.keysym.sym;
  }
  else if (event.type == SDL_MOUSEBUTTONDOWN ||
      event.type == SDL_MOUSEBUTTONUP)
  {
    eventPkt.type = event.type;
    eventPkt.button = event.button.button;
    eventPkt.x = event.button.x;
    eventPkt.y = event.button.y;
  }
  else
  {
    return;
  }

  _socket.SendEvent(eventPkt);
}

int GameEngine::Music(Mix_Chunk*& track)
{
  /*
   * Is made this way, because here we can then change music depending on
   * whats happening in the game. It could for instance trigger on gamestate
   * etc. Also there are SDL_mixer functions to fade out or fade in songs so
   * that could be done here, allthough for now this functions is only called
   * upon when there is no music playin.
   */
  if (!track)
  {
    track = Mix_LoadWAV("music/track1.ogg");
  }
  int channel;

  channel = Mix_PlayChannel(-1, track, 1);
  return channel;
}

void GameEngine::Sound()
{
  	Mix_Chunk *_sfx = NULL;
	_sfx = Mix_LoadWAV("soundFX/shoot.ogg");
	int channel = 0;	
	channel = Mix_PlayChannel(-1,_sfx,0);


}


void GameEngine::PushState(GameState* gameState)
{
  _gameStates.push_back(gameState);
}

void GameEngine::PopState()
{
  if (!_gameStates.empty())
  {
    _gameStates.pop_back();
  }
}

void GameEngine::ChangeState(GameState* gameState)
{
  PopState();
  PushState(gameState);
}

void GameEngine::HandleEvents()
{
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type)
    {
      case SDL_QUIT:
        _isRunning = false;
        break;
    }

    if (!_gameStates.empty()) {
      _gameStates.back()->HandleEvent(event);
    }
  }
}

void GameEngine::Update()
{
  _gameStates.back()->Update();
}

void GameEngine::Draw()
{
  _gameStates.back()->Draw();

  /* Broken in move from SDL -> OpenGL
     SDL_Rect dest = { 0, 0, NULL, NULL };
     TextBlitter::Instance()->BlitText(_currentFps, _screen, &dest);*/
  SDL_GL_SwapBuffers();
}

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GameEngine.hpp"
#include "GSMain.hpp"

GSMain::GSMain()
{
  std::cout << "GSMain::GSMain" << std::endl;

  _zoomFactor = 1.0f;
}

GSMain::~GSMain()
{
  std::cout << "GSMain::~GSMain" << std::endl;

  while (!_entities.empty())
  {
    delete _entities.back();
    _entities.pop_back();
  }
}

void GSMain::HandleEvent(const SDL_Event& event)
{
  //std::cout << "GSMain::HandleEvents" << std::endl;
  if (event.type == SDL_KEYDOWN)
  {
    switch (event.key.keysym.sym)
    {
      case SDLK_q:
        if (SDL_GetModState() & (KMOD_LSHIFT | KMOD_RSHIFT))
        {
          GameEngine::Instance()->Quit();
        }
		break;

	  case SDLK_SPACE:
		GameEngine::Instance()->Sound();
		break;

      default:
        break;
    }
  }

  GameEngine::Instance()->Send(event);
}

void GSMain::Update()
{
  //std::cout << "GSMain::Update" << std::endl;

  Uint8* keyState = SDL_GetKeyState(NULL);
  if (keyState[SDLK_a])
  {
    _zoomFactor *= 1.01;
  }
  else if (keyState[SDLK_z])
  {
    _zoomFactor *= 0.99;
  }

  for (unsigned int i = 0; i < _entities.size(); ++i)
  {
    _entities.at(i)->Update();
  }
}

void GSMain::Draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  glTranslatef(512, 300, 0.0);
  glScalef(_zoomFactor, _zoomFactor, 1.0f);

  for (unsigned int i = 0; i < _entities.size(); ++i)
  {
    _entities.at(i)->Draw();
  }
  glPopMatrix();
}

#include <cmath>
#include <iostream>
#include <string>
#include "GameEngine.hpp"
#include "Vessel.hpp"
#include "graphics.hpp"

Vessel::Vessel(int id, std::string name, std::vector<Subsystem*>&,
    float x, float y, float rot) :
  Entity(x, y, rot)
{
  std::cout << name << "::Vessel" << std::endl;

  _id = id;
  _isAlive = true;
  _textureId = LoadTexture("images/spaceship.png", false);
  _name = name;
}

Vessel::~Vessel()
{
  std::cout << _name << "::~Vessel()" << std::endl;
  for (unsigned int i = 0; i < _subsystems.size(); ++i)
  {
    if (_subsystems.at(i))
    {
      delete _subsystems.at(i);
    }
  }
}

void Vessel::Destroy()
{
  _isAlive = false;
  std::cout << _name << " is destroyed!" << std::endl;
}

// Handle packet data from server and update position and such.
void Vessel::ReceiveWorld()
{
  //std::cout << _name << "::ReceiveWorld()" << std::endl;

  /*
     FIXME
   */
}

// Update animation counters and such.
void Vessel::Update()
{
  //std::cout << _name << "::Update()" << std::endl;

  /*
     FIXME
   */
}

// Draw the ship on the screen
void Vessel::Draw()
{
  //std::cout << _name << "::Draw()" << std::endl;
  if (_isAlive)
  {
    // Select the vessel texture
    glBindTexture(GL_TEXTURE_2D, _textureId);

    // Save the global matrix
    glPushMatrix();

    // Translate the global matrix to the vessel center
    glTranslatef(_pos.X(), _pos.Y(), 0);
    // Rotate the matrix to match the vessels bearing (around the z axis)
    glRotatef(_rot, 0.0, 0.0, 1.0);

    // Draw the vessel
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_TEXTURE_2D);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 0.0); glVertex2d(-25, -25);
    glTexCoord2d(1.0, 0.0); glVertex2d(25, -25);
    glTexCoord2d(1.0, 1.0); glVertex2d(25, 25);
    glTexCoord2d(0.0, 1.0); glVertex2d(-25, 25);
    glEnd();

    // Restore the global matrix
    glPopMatrix();
  }
}

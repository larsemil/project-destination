#include <SDL/SDL.h>
#include "Player.hpp"

Player::Player(unsigned int id, std::string ipAddress,
    const char name[256])
{
  _id = id;
  _name = name;

  // Connect to server
}

Player::~Player()
{
  /* FIXME
  if (_keyState)
  {
    delete [] _keyState;
  }
  */
}

void Player::Update()
{
  for (unsigned int i = 0; i < _vessels.size(); ++i)
  {
    _vessels.at(i)->Update();
  }
}


//
// Class related functions
//

Player* SelectPlayer(std::string hostaddr,
    const std::vector<Player*>& players)
{
  for (unsigned int i = 0; i < players.size(); ++i)
  {
    /* FIXME
    if (players.at(i).GetIPAddress() == ipAddress)
    {
      return players.at(i);
    }
    */
  }

  return NULL;
}

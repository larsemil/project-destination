#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <netinet/in.h>
#include <netdb.h>
#include "Vessel.hpp"
#include "defines.hpp"

struct Address
{
  char address[NI_MAXHOST];
  char port[NI_MAXSERV];
};

class Player
{
  private:
    unsigned int _id;
    std::string _name;

    // How old the last packet is, when too old, ping!
    int _packetAge;
    // The latency of the last ping
    int _latency;
    // The player's associated IP address
    Address _address;


    // The ships owned by the player
    std::vector<Vessel*> _vessels;
    // The currently controlled ship
    Vessel* _currentVessel;

  public:
    Player(unsigned int id, std::string address,
        const char name[PKT_NAMELEN]);
    ~Player();

    const Address& GetIPAddress() const { return _address; }

    void SetLatency(int latency) { _latency = latency; }

    void HandleEvent(const SDL_Event& event);
    void Update();
};

Player* SelectPlayer(std::string address,
    const std::vector<Player*>& players);

#endif

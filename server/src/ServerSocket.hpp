#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <SDL/SDL.h>
#include "defines.hpp"
#include "Player.hpp"

enum PktType
{
  PKT_JOIN,
  PKT_PING,
  PKT_PING_REPLY,
  PKT_KBD_EVENT,
  PKT_MOUSE_EVENT
};

struct BasePkt
{
  uint8_t type;
};

struct JoinPkt : BasePkt
{
  char name[PKT_NAMELEN];
};

struct PingPkt : BasePkt
{
  uint32_t timeOfSending;
};

struct EventPkt : BasePkt
{
  uint8_t state;
  uint8_t button;
  uint16_t x;
  uint16_t y;
};

class ServerSocket
{
  private:
    int _socket;

  public:
    ServerSocket() {};
    ServerSocket(const char* port);

    const int Recieve(BasePkt** packet, std::string& retAddr,
        std::string& retServ) const;
    void SendCredentials(Player* player);
    void PrintLocalAddr();

    // Send the world to a player
    void SendWorld(Player* player);
};

#endif

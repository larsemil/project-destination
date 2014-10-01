#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

//#include <cstdint>
#include <SDL/SDL.h>

enum PktType
{
  PING, KEYBOARD, MOUSE
};

struct BasePkt
{
  Uint8 type;

  BasePkt() : type(0) {}
};

struct PingPkt : BasePkt
{
  Uint32 sendTime;

  PingPkt() { type = PING; }
};

struct EventPkt : BasePkt
{
  Uint8 button;
  Uint16 x, y;

  EventPkt() : button(0), x(0), y(0) {}
};

class ClientSocket
{
  private:
    int _socket;

  public:
    ClientSocket() { _socket = 0; }
    ClientSocket(const char* host, const char* port);

    void SendEvent(const EventPkt& eventPkt) const;
};

#endif

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "ClientSocket.hpp"

ClientSocket::ClientSocket(const char* host, const char* port)
{
  addrinfo hints = {};
  addrinfo *result;
  addrinfo *rp;
  
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;

  int err;
  if ((err = getaddrinfo(host, port, &hints, &result)) != 0)
  {
    std::cerr << "getaddrinfo() error: "
      << gai_strerror(err) << std::endl;
    throw gai_strerror(err);
  }

  for (rp = result; rp != NULL; rp = rp->ai_next)
  {
    _socket = socket(rp->ai_family, rp->ai_socktype,
                     rp->ai_protocol);

    if (_socket == -1)
      continue;

    if (connect(_socket, rp->ai_addr, rp->ai_addrlen) != -1)
      break;  /* Success */

    close(_socket);
  }

  if (rp == NULL)
  {
    std::cerr << "Could not connect" << std::endl;
    throw "Could not connect";
  }

  freeaddrinfo(result);
}

void ClientSocket::SendEvent(const EventPkt& packet) const
{
  if (write(_socket, &packet, sizeof(packet)) != sizeof(packet))
  {
    std::cerr << "Partial or failed write to socket" << std::endl;
  }
}

#include <cerrno>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "ServerSocket.hpp"
#include "functions.hpp"

ServerSocket::ServerSocket(const char* port)
{
  addrinfo hints = {};
  addrinfo *serverInfo;

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;

  int res;
  if ((res = getaddrinfo(NULL, port, &hints, &serverInfo)) != 0)
  {
    std::cerr << "getaddrinfo() error: "
      << gai_strerror(res) << std::endl;
    throw gai_strerror(res);
  }

  if ((_socket = socket(serverInfo->ai_family,
          serverInfo->ai_socktype, serverInfo->ai_protocol)) == -1)
  {
    std::cerr << "socket() error" << std::endl;
    throw "socket() error";
  }

  if (bind(_socket, serverInfo->ai_addr, serverInfo->ai_addrlen) == -1)
  {
    close(_socket);
    std::cerr << "bind() error" << std::endl;
    throw "bind() error";
  }

  freeaddrinfo(serverInfo);
  std::cout << "Server started, listening on ";
  PrintLocalAddr();
  std::cout << std::endl;
}

const int ServerSocket::Recieve(BasePkt** packet, std::string& retAddr,
    std::string& retServ)
const
{
  char buffer[PKT_BUFLEN];
  char addr[NI_MAXHOST];
  char serv[NI_MAXSERV];
  sockaddr from;
  socklen_t fromlen = sizeof(sockaddr);

  int result = recvfrom(_socket, buffer, PKT_BUFLEN,
      MSG_DONTWAIT, &from, &fromlen);
  if (result > 0)
  {
    hexdump(buffer, result);
    *packet = new BasePkt(*(BasePkt*)(buffer));

    int error = getnameinfo(&from, fromlen, addr, sizeof(addr),
        serv, sizeof(serv), NI_NUMERICHOST | NI_NUMERICSERV | NI_DGRAM);
    if (error == 0)
    {
      retAddr = addr;
      retServ = serv;
    }
    else
    {
      std::cout << "Couldn't get host address from read packet: "
        << gai_strerror(error) << " : " << strerror(errno) << std::endl;
    }
  }
  else if (result == 0)
  {
    std::cout << "Error reading packet: " << strerror(errno) << std::endl;
  }
  else
  {
    // Nothing to read
  }

  return result;
}

void ServerSocket::SendCredentials(Player *player)
{

}

void ServerSocket::PrintLocalAddr()
{
  struct sockaddr sa;
  socklen_t len = sizeof(sa);
  char host[NI_MAXHOST];
  char serv[NI_MAXSERV];

  getsockname(_socket, &sa, &len);
  getnameinfo(&sa, len, host, sizeof(host),
      serv, sizeof(serv), NI_NUMERICHOST | NI_NUMERICSERV);

  std::cout << host << ":" << serv;
}

// Send the world to a player
void ServerSocket::SendWorld(Player *player)
{
}

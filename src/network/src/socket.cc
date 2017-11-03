#include "include/rpc_socket.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

using namespace std;

bool IPv4Connection::create(int port){
  m_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (m_listen_fd == -1)
    return false;
  struct sockaddr_in servaddr;

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);
  if (bind(m_listen_fd, reinterpret_cast<struct sockaddr*>(&servaddr), sizeof(servaddr)) == -1)
    return false;

  return true;
}

bool IPv4Connection::connect(string ip, int port){
  return false;
}

void IPv4Connection::accept(){
}

int IPv4Connection::read(char *buffer){
  return 0;
}

int IPv4Connection::write(char *buffer){
  return 0;
}


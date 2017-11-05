#include "include/rpc_socket.h"
#include "util/include/util.h"
#include "util/include/exception.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <fcntl.h>

using namespace std;
namespace rpc{
namespace socket{

#ifndef RPC_SOCKET_ERROR_THROW
#define RPC_SOCKET_ERROR_THROW(_cond, _fun_name, _msg)\
  rpc_throw_if((_cond), SocketException, "Socket init error when %s, %s\n",_fun_name, _msg)
#endif

int IPv4Connection::init_socket(string &port){
  struct addrinfo hints;
  struct addrinfo *result, *p;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family   = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags    = AI_PASSIVE;

  int s = getaddrinfo(nullptr, port.c_str(), &hints, &result);
  RPC_SOCKET_ERROR_THROW(s==0, "getaddrinfo", gai_strerror(s));
  auto rp = result;
  int sfd;

  for (; rp != nullptr; rp = rp->ai_next){
    sfd = ::socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (rpc_unlikely(sfd == -1))
      continue;

    auto s = bind(sfd, rp->ai_addr, rp->ai_addrlen);
    if (s == 0)
      break;
  }

  RPC_SOCKET_ERROR_THROW(rp == nullptr, "bind", "bind failed\n");
  freeaddrinfo(result);

  return sfd;
}

void IPv4Connection::set_non_block(int socket_fd){
  int flag = fcntl(socket_fd, F_GETFL, 0);
  RPC_SOCKET_ERROR_THROW(flag == -1, "fctl", "fctl failed\n");
  flag |= O_NONBLOCK;
  flag = fcntl(socket_fd, F_SETFL, flag);
  RPC_SOCKET_ERROR_THROW(flag == -1, "fctl", "fctl failed\n");
}

Handler IPv4Connection::create(string& port){
  int soket_fd = init_socket(port);
  set_non_block(soket_fd);

  RPC_SOCKET_ERROR_THROW(listen(soket_fd, CONNECT_NUMBER) == -1, "listen", 
                         "listen failed!\n");

  return IPv4Connection::IPv4Handler(soket_fd);
}

bool IPv4Connection::connect(string &ip, int port){
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
}
}

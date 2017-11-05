#pragma once
#include <string>
#include "io_handle.h"

namespace rpc{
namespace socket{
class Connection{
  public:
    virtual Handler create(std::string& port) = 0;
    virtual bool connect(std::string& ip, int port) = 0;
    virtual void accept() = 0;

    virtual int read(char *buffer) = 0;
    virtual int write(char *buffer) = 0;

  protected:
    std::string m_protocol;
};


class IPv4Connection : Connection {
  public:
    const static int CONNECT_NUMBER = 0;
    class IPv4Handler : public Handler {
      public:
        IPv4Handler(int fd) : Handler(fd){}

        int get_handle(){
          return fd;
        }
    };

    Handler create(std::string &port) override;
    bool connect(std::string &ip, int port) override;
    void accept() override;

    int read(char *buffer) override;
    int write(char *buffer) override;

    IPv4Connection(){
      m_protocol = "IPv4";
    }

  private:
    int m_listen_fd;

    // set socket io not block
    void set_non_block(int socket_fd);
    // init socket, finish socket create and bind
    int init_socket(std::string &port);
};
}
}

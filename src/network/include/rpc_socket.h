#include <string>

class Connection{
  public:
    virtual bool create(int port) = 0;
    virtual bool connect(std::string ip, int port) = 0;
    virtual void accept() = 0;

    virtual int read(char *buffer) = 0;
    virtual int write(char *buffer) = 0;

  protected:
    std::string m_protocol;
};


class IPv4Connection : Connection {
  public:
    bool create(int port);
    bool connect(std::string ip, int port);
    void accept();

    int read(char *buffer);
    int write(char *buffer);

    IPv4Connection(){
      m_protocol = "IPv4";
    }

  private:
    int m_listen_fd;
};

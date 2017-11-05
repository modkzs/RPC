#pragma onece

namespace rpc{
namespace socket{
// Base Handler for all io handler
class Handler{
  public:
    int handle_id = -1;
    Handler(int fd): handle_id(fd){}

    virtual int get_handle() = 0;
};

// Base class for io handler
class IO_Handler{
  public:
    virtual void add_handler(Handler handle) = 0;
    virtual void start() = 0;
};

class Async_Handler : IO_Handler {
  public:
    void add_handler(const Handler &handle);
    void start();

    Async_Handler();
  private:
    int m_epoll_fd;
};

}
}

#include <sys/epoll.h>

#include "include/io_handle.h"
#include "util/include/util.h"
#include "util/include/exception.h"

namespace rpc{
namespace socket {
Async_Handler::Async_Handler(){
  m_epoll_fd = epoll_create1();
  rpc_throw_if(m_epoll_fd == -1, SocketException, "epoll create failed\n");
}
void  Async_Handler::add_handler(const Handler &handle){
  struct epoll_event event;
  event.data.fd = handle.get_handle();
  event.events = EPOLLIN | EPOLLET;
  s = epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, handle.get_handle(), &event);
}


}
}

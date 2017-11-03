#include <stdexception>
#include <string>

namespace rpc{
  class RpcException : std::exception {
    protected:
      std::string m_msg;
    public:
      const char *what() const noexcept override {
        return m_msg.c_str()
      }
  
      RpcException(std::string &msg):m_msg(msg){}
      ~RpcException() noexcept = default;
  };

  class SocketException : RpcException {
    using RpcException::RpcException;
  };

  class AssertException: RpcException {
    using RpcException::RpcException;
  };
}


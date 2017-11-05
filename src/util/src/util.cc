#include "include/exception.h"
#include "include/util.h"

using namespace rpc;

#if RPC_ASSERT_LOC == 1
void __assert_fail__(
        const char *file, int line, const char *func,
        const char *expr, const char *msg_fmt, ...) {

    std::string msg = ssprintf("assertion `%s' failed at %s:%d: %s",
            expr, file, line, func);
    if (msg_fmt) {
        msg_fmt = convert_fmt_str(msg_fmt);
        va_list ap;
        va_start(ap, msg_fmt);
        msg.append("\nextra message: ");
        msg.append(svsprintf(msg_fmt, ap));
        va_end(ap);
    }
    RPC_THROW(AssertionError{msg});
}
#else
void rpc::__assert_fail__() {
    RPC_THROW(AssertionError, "assertion failed");
}
#endif

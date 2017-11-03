namespace rpc{
#define rpc_likely(v) __builtin_expect(static_cast<bool>(v), 1)
#define rpc_unlikely(v) __builtin_expect(static_cast<bool>(v), 0)

#if RPC_EXCEPTION == 1

#define RPC_TRY try
#define RPC_THROW(_exec...) throw(_exec)
#define RPC_CATCH(_decl, _stmt) catch(_decl, _stmt)

#else

#define RPC_TRY
#define RPC_THROW(_exec...) __builtin_trap()
#define RPC_CATCH(_decl, _stmt)

#endif

#if RPC_ASSERT_LOC == 1
#define rpc_assert(expr, msg...)\
  do { \
    if (rpc_unlikely(!(expr))) \
      ::rpc::__assert_fail__(__FILE__, __LINE__, __PRETTY_FUNCTION__, #expr, ##msg);\
  } while(0)

  void __assert_fail__(const char *file, const int line, const char *name,
                       const char *expr, const char *msg_fmt = 0, ...) 
                       __attribute__((format(printf, 5, 6), noreturn));
#else
#define rpc_assert(expr, msg...)\
  do { \
    if (rpc_unlikely(!(expr))) \
      ::rpc::__assert_fail__();\
  }while(0)
  void __assert_fail__() __attribute__((noreturn));;
#endif
}

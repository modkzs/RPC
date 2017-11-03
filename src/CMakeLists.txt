FILE(GLOB SOURCE "network/*/*.cc" "network/*/*.h" "serialize/*/*.h" "serialize/*/*.cc" "util/*/*.cc" "util/*/*.h")

INCLUDE_DIRECTORIES("./network")
INCLUDE_DIRECTORIES("./serialize")
INCLUDE_DIRECTORIES("./util")

list(APPEND SOURCE "main.cpp")

ADD_EXECUTABLE(PRC ${SOURCE})

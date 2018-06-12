cmake_minimum_required(VERSION 2.8)

add_definitions( -std=c++11 )

set(PRJ_HEADERS
  
)

set(PRJ_SRCS
  main.cpp
)

add_executable(main
  ${PRJ_SRCS}
  ${PRJ_HEADERS}
)

#target_link_libraries(main
#)

cmake_minimum_required(VERSION 3.5.1)
project(tinyhttpd)


file(GLOB_RECURSE TINYHTTPD_HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE TINYHTTPD_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/)

include_directories(include/)
add_executable(tinyhttpd ${TINYHTTPD_SOURCES} ${TINYHTTPD_HEADERS})

FIND_LIBRARY(EVENT_LIB NAMES event PATHS /usr/local/lib )
MESSAGE(STATUS "libevent lib path: ${EVENT_LIB}")

TARGET_LINK_LIBRARIES(tinyhttpd ${EVENT_LIB})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wall")

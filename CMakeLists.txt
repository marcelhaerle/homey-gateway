cmake_minimum_required(VERSION 3.16)

project(homey-gateway)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)

find_package(PkgConfig REQUIRED)

pkg_search_module(GATTLIB REQUIRED gattlib)
pkg_search_module(GLIB REQUIRED glib-2.0)
pkg_search_module(PCRE REQUIRED libpcre)

include_directories(${GLIB_INCLUDE_DIRS})

set(SOURCES src/main.cpp src/Device.cpp)

add_executable(homey-gateway ${SOURCES})
target_link_libraries(homey-gateway ${GATTLIB_LIBRARIES} ${GATTLIB_LDFLAGS} ${GLIB_LDFLAGS} ${PCRE_LIBRARIES} pthread)

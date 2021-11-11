cmake_minimum_required(VERSION 3.16)

project(homey-gateway LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(gattlib
        GIT_REPOSITORY    git@github.com:labapart/gattlib.git
        )
FetchContent_MakeAvailable(gattlib)

add_executable(homey-gateway src/main.cpp src/Device.cpp)
target_link_libraries(homey-gateway gattlib)

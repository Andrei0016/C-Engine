cmake_minimum_required(VERSION 3.28)
project(untitled1)

set(CMAKE_CXX_STANDARD 26)

set(SDL2_INCLUDE_DIR C:/dev/SDL/include)
set(SDL2_LIB_DIR C:/dev/SDL/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(untitled1 main.cpp
        lib.h
        game_engine.h
        linear_math.h
        window.h
        window.cpp
        linear_math.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)

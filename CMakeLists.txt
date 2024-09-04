cmake_minimum_required(VERSION 3.28)
project(CEngine)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_library(engine SHARED
        lib.h
        game_engine.h
        linear_math.h
        window.h
        window.cpp
        linear_math.cpp
        CommandBuffer.h
        CommandBuffer.cpp
        Renderer.h
        Renderer.cpp
        Object.cpp
        Object.h
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(engine ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIR})
target_link_libraries(engine ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARY})

add_executable(demo demo.cpp)
target_link_libraries(demo engine)

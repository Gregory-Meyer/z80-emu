cmake_minimum_required(VERSION 3.8)

project(z80-emu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wconversion -pedantic -pedantic-errors -Wshadow -Wcast-qual -march=native")
set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS} -Og -g3 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -flto -fgcse-sm -fgcse-las -fgcse-after-reload")

set(SOURCES src/z80/emulator.cpp)

include_directories(include/)

add_executable(main src/main.cpp ${SOURCES})

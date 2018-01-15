cmake_minimum_required(VERSION 3.8.2)

project(z80-emu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -Wconversion -pedantic -pedantic-errors -Wshadow -Wcast-qual -march=native")
# will have to add -fsanitize=address -fsanitize=leak -fsanitize=undefined later
set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS} -Og -g3 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -flto -fgcse-sm -fgcse-las -fgcse-after-reload")

find_package(Boost COMPONENTS system REQUIRED)
find_package(Threads REQUIRED)

include_directories(include ${Boost_INCLUDE_DIRS})

add_library(timer include/timer.h src/timer.cpp)
if (WIN32)
	target_link_libraries(timer Threads::Threads ${Boost_LIBRARIES} wsock32 ws2_32)
else()
	target_link_libraries(timer Threads::Threads ${Boost_LIBRARIES})
endif()

add_library(register_pair src/register_pair.cpp)
target_link_libraries(register_pair Threads::Threads)

add_library(exceptions src/exceptions.cpp)

add_library(memory_unit src/memory_unit.cpp)
target_link_libraries(memory_unit exceptions)

add_library(utility src/utility.cpp)

add_executable(emulator src/emulator.cpp)
target_link_libraries(emulator timer)
add_dependencies(emulator timer)

add_executable(test_timer test/test_timer.cpp)
target_link_libraries(test_timer timer)
add_dependencies(test_timer timer)

add_executable(test_register_pair test/test_register_pair.cpp)
target_link_libraries(test_register_pair register_pair)
add_dependencies(test_register_pair register_pair)

add_executable(test_literals test/test_literals.cpp)

add_executable(test_memory_unit test/catch_main.cpp test/test_memory_unit.cpp)
target_link_libraries(test_memory_unit memory_unit)

add_executable(test_utility test/catch_main.cpp test/test_utility.cpp)
target_link_libraries(test_utility utility)

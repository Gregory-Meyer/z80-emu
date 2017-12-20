cmake_minimum_required(VERSION 3.8.2)

find_package(Boost COMPONENTS system REQUIRED)

find_package(Threads REQUIRED)

include_directories(include ${Boost_INCLUDE_DIRS})

add_executable(emulator src/emulator.cpp src/timer.cpp)
target_link_libraries(emulator ${Boost_LIBRARIES} Threads::Threads)
target_compile_features(emulator PUBLIC cxx_std_17)

add_executable(timer_test test/test_timer.cpp src/timer.cpp)
target_link_libraries(timer_test ${Boost_LIBRARIES} Threads::Threads)
target_compile_features(timer_test PUBLIC cxx_std_17)

set_target_properties(emulator timer_test PROPERTIES CXX_EXTENSIONS OFF)

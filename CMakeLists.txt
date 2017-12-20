cmake_minimum_required(VERSION 3.8.2)

find_package(Boost COMPONENTS system REQUIRED)

find_package(Threads REQUIRED)

include_directories(include ${Boost_INCLUDE_DIRS})

add_executable(emulator src/emulator.cpp src/timer.cpp)
target_link_libraries(emulator ${Boost_LIBRARIES} Threads::Threads)
target_compile_features(emulator PUBLIC cxx_std_17)

add_executable(test_timer test/test_timer.cpp src/timer.cpp)
target_link_libraries(test_timer ${Boost_LIBRARIES} Threads::Threads)
target_compile_features(test_timer PUBLIC cxx_std_17)

add_executable(test_register_pair
			   test/test_register_pair.cpp src/register_pair.cpp)
target_link_libraries(test_timer Threads::Threads)
target_compile_features(test_timer PUBLIC cxx_std_17)

set_target_properties(emulator test_timer test_register_pair
					  PROPERTIES CXX_EXTENSIONS OFF)

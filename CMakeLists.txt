cmake_minimum_required(VERSION 3.1)
project(txtcompose)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(Boost 1.44.0 REQUIRED
	filesystem
	system
)

include_directories(Boost_INCLUDE_DIRS)
link_directories(Boost_LIBRARY_DIRS)

add_executable(txtcompose
	composer.cpp
	options.cpp
	txtcompose.cpp
)

target_link_libraries(txtcompose boost_filesystem boost_system)

cmake_minimum_required(VERSION 3.10)

project(GraphEditor VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)  


include_directories(GraphEditor)


find_package(Boost 1.70 REQUIRED)


file(GLOB_RECURSE SOURCES "GraphEditor/*.cpp")

add_executable(GraphEditor ${SOURCES})

target_link_libraries(GraphEditor Boost::Boost)
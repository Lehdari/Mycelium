cmake_minimum_required(VERSION 2.8)
project(Mycelium)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Add shared library: mycelium
add_subdirectory(include)
add_subdirectory(src)

add_library(mycelium SHARED ${LIBRARY_HEADERS} ${LIBRARY_SOURCES})

target_include_directories(mycelium PUBLIC include)

#Add Eigen include directory
find_package(Eigen3 REQUIRED)

if(NOT EIGEN3_INCLUDE_DIR)
    set(EIGEN3_INCLUDE_DIR "$ENV{EIGEN3_INCLUDE_DIR}")
endif()

target_include_directories(mycelium PUBLIC ${EIGEN3_INCLUDE_DIR})

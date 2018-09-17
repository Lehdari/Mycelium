cmake_minimum_required(VERSION 2.8)
project(Mycelium)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Add executable: {{EXECUTABLE_NAME}}
add_subdirectory(include)
add_subdirectory(src)

add_executable({{EXECUTABLE_NAME}} ${LIBRARY_HEADERS} ${LIBRARY_SOURCES})

target_include_directories({{EXECUTABLE_NAME}} PUBLIC include)
# CMakeLists.txt for program

cmake_minimum_required(VERSION 3.16.0)

set(HEADERS Command.h Flyweight.h)
set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# End file

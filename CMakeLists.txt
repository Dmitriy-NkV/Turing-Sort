cmake_minimum_required(VERSION 3.10)
project(TapeSorter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/tmp)

add_executable(TapeSorter
  src/tape.cpp
  src/tape.hpp
  src/i_tape.hpp
  src/tape_sorter.cpp
  src/tape_sorter.hpp
  main.cpp
)
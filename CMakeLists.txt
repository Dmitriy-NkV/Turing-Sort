cmake_minimum_required(VERSION 3.14)
project(TuringSort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(COMMON_SOURCES
  src/tape.cpp
  src/tape.hpp
  src/i_tape.hpp
  src/tape_sorter.cpp
  src/tape_sorter.hpp
  src/functions.cpp
  src/functions.hpp
)

add_executable(TuringSort
  ${COMMON_SOURCES}
  main.cpp
)

add_executable(Tests
  ${COMMON_SOURCES}
  tests/test_main.cpp
  tests/test_tape.cpp
  tests/test_sorter.cpp
)
target_link_libraries(Tests
  PRIVATE
  gtest
  gmock
  pthread
)

enable_testing()
add_test(NAME Tests COMMAND Tests)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/tmp)

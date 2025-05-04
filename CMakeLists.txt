cmake_minimum_required(VERSION 3.14)
project(TuringSort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  GoogleTest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.17.0
)
FetchContent_MakeAvailable(GoogleTest)

set(COMMON_SOURCES
    src/tape.cpp
    src/tape.hpp
    src/i_tape.hpp
    src/tape_sorter.cpp
    src/tape_sorter.hpp
)

add_executable(TuringSort ${COMMON_SOURCES} main.cpp)

add_executable(Tests ${COMMON_SOURCES} test/test_tape.cpp test/test_sorter.cpp)
target_link_libraries(Tests PRIVATE GTest::GTest GTest::Main)

enable_testing()
add_test(NAME Tests COMMAND Tests)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/tmp)
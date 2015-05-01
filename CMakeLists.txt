cmake_minimum_required(VERSION 3.1)

set(EXECUTABLE_NAME "step_plot")
set(CMAKE_C_COMPILER clang-3.6)
set(CMAKE_CXX_COMPILER clang++-3.6)
set(CMAKE_CXX_FLAGS "${CM_CXX_FLAGS} --stdlib=libstdc++ --std=c++14")

set(SOURCE_FILES main.cpp)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

add_subdirectory(step_log)

find_package(Boost COMPONENTS system program_options filesystem)
find_package(Curses)

include_directories(${Boost_INCLUDE_DIR})
include_directories(${Curses_INCLUDE_DIR})
include_directories(/home/brian/repos/brainstem_breakfast/source/)

target_link_libraries(${EXECUTABLE_NAME}
    ${Boost_LIBRARIES})

target_link_libraries(${EXECUTABLE_NAME}
    ${CURSES_NCURSES_LIBRARY})
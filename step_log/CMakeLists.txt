cmake_minimum_required(VERSION 3.1)

set(EXECUTABLE_NAME "step_log_test")
set(CMAKE_C_COMPILER clang-3.6)
set(CMAKE_CXX_COMPILER clang++-3.6)
set(CMAKE_CXX_FLAGS "${CM_CXX_FLAGS} --stdlib=libstdc++ --std=c++14")

set(SOURCE_FILES step_log_test.cpp)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

find_package(Boost COMPONENTS system program_options filesystem)

include_directories(${Boost_INCLUDE_DIR})
include_directories(/home/brian/repos/cereal/include)
include_directories(/home/brian/repos/multi)

target_link_libraries(${EXECUTABLE_NAME}
    ${Boost_LIBRARIES})

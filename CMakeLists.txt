cmake_minimum_required(VERSION 3.0.0)
project(Simulator)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
    code/include
    lib/include/concepts
    lib/include/tss
    lib/include/util
)

add_executable(main
    code/source/Main.cpp
    code/source/Compiler.cpp
    code/source/Configuration.cpp
    code/source/Machine.cpp
    code/source/Memory.cpp
    code/source/Operation.cpp
    code/source/Strategy.cpp
    code/source/Writer.cpp)
target_link_libraries(main ${CMAKE_CURRENT_SOURCE_DIR}/lib/libSimulationEngine.so)
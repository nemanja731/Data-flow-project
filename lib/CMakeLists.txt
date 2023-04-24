cmake_minimum_required(VERSION 2.8)

project(SimulationEngine)
set(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/concepts)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/tss)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/util)
add_library(SimulationEngine SHARED

	${CMAKE_CURRENT_SOURCE_DIR}/implementation/concepts/AbstractConcepts.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/implementation/concepts/RndGen.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/implementation/concepts/SimEng.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/implementation/concepts/Visitor.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/implementation/tss/CrossSem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/implementation/tss/FlowSink.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/implementation/tss/FlowSource.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/implementation/tss/Pipe.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/implementation/tss/QueServer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/implementation/tss/Switch1to3.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/implementation/tss/VModelChecker.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/implementation/tss/VModelDocumenter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/implementation/tss/VSimReporter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/implementation/tss/VTxtOutputGen.cpp
)

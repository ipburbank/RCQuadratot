project("RobotEvolver")

# The version number.
set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#build the GUI simulator too or just the CLI
option(BUILD_VISUAL "BuildVisual" ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")

#bullet
include_directories(SYSTEM Libraries/Bullet3/src) #to avoid errors from c++11
SET(BULLET_VERSION 2.83)
add_subdirectory(Libraries/Bullet3/src)

#bullet demo files
add_subdirectory(BulletDemoFiles)

#all compiles after this use c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(RobotGeometry)

if(BUILD_VISUAL)
add_executable(SimulatorInteractive SimulatorInteractive.cpp SimulationVisual.cpp Simulation.cpp)

target_link_libraries(SimulatorInteractive BulletDemoGlut RobotGeometry BulletDemoFiles BulletDynamics BulletCollision LinearMath)

#system libraries
target_link_libraries(SimulatorInteractive -lglut)
target_link_libraries(SimulatorInteractive -lGL)
target_link_libraries(SimulatorInteractive -lGLU)
endif(BUILD_VISUAL)

add_executable(SimulatorCLI SimulatorCLI.cpp Simulation.cpp)

target_link_libraries(SimulatorCLI RobotGeometry BulletDemoFiles BulletDynamics BulletCollision LinearMath)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Docs/Doxyfile.in 
		${CMAKE_CURRENT_BINARY_DIR}/Docs/Doxyfile @ONLY
	)
	add_custom_target(docs
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Docs/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Docs
		COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
endif(DOXYGEN_FOUND)

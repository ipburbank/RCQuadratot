project("RobotEvolver")

# The version number.
set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#build the GUI simulator too or just the CLI
option(BUILD_VISUAL "BuildVisual" ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")

#bullet
include_directories(SYSTEM Libraries/Bullet3/src) #to avoid errors from c++11
SET(BULLET_VERSION 2.83)
add_subdirectory(Libraries/Bullet3/src)

#bullet demo files
add_subdirectory(BulletDemoFiles)

#all compiles after this use c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package( Boost 1.50 COMPONENTS filesystem system thread )

IF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	ADD_DEFINITIONS(-fPIC)
ENDIF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

ADD_DEFINITIONS(
		-DTIXML_USE_STL
		-DNOPCH
		-D_USE_MATH_DEFINES
		-pthread
		-DONETHREADual
)

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_subdirectory(RobotGeometry)
add_subdirectory(ANN)

if(BUILD_VISUAL)
add_executable(SimulatorInteractive SimulatorInteractive.cpp SimulationVisual.cpp Simulation.cpp)

target_link_libraries(SimulatorInteractive
ANN

${Boost_LIBRARIES}

tinyxmldll
zlib

BulletDemoGlut RobotGeometry BulletDemoFiles BulletDynamics BulletCollision LinearMath)

#system libraries
target_link_libraries(SimulatorInteractive -lglut)
target_link_libraries(SimulatorInteractive -lGL)
target_link_libraries(SimulatorInteractive -lGLU)
endif(BUILD_VISUAL)

add_executable(SimulatorCLI SimulatorCLI.cpp Simulation.cpp)

target_link_libraries (SimulatorCLI
ANN

${Boost_LIBRARIES}

tinyxmldll
zlib

RobotGeometry 
BulletDemoFiles
BulletDynamics
BulletCollision
LinearMath
)

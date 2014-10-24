project("RCQuadratot")

# The version number.
set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o3")

#project components
add_subdirectory(Simulator)
add_subdirectory(Hypercube_NEAT)


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

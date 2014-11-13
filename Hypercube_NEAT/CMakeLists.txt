Project(NEAT)

cmake_minimum_required(VERSION 2.8)

ADD_DEFINITIONS(
		-DTIXML_USE_STL
		-DNOPCH
		-D_USE_MATH_DEFINES
		-pthread
		-DONETHREADual
		#-DINTERACTIVELYEVOLVINGSHAPES
		-DVISUALIZESHAPES
)

IF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	ADD_DEFINITIONS(-fPIC)
ENDIF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

include_directories(Libraries/JGTL/include)
include_directories(src/hiller)
include_directories(include)
include_directories(NEAT/include)

INCLUDE_REGULAR_EXPRESSION( "^.*([Hh][Cc][Uu][Bb][Ee]|[Nn][Ee][Aa][Tt]|main).*$" )


find_package( Boost 1.50 COMPONENTS filesystem system thread )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

ADD_LIBRARY(
	NEAT
	STATIC

	NEAT/src/NEAT_FastNetwork.cpp
	NEAT/src/NEAT_FastBiasNetwork.cpp
	NEAT/src/NEAT_GeneticGene.cpp
	NEAT/src/NEAT_GeneticGeneration.cpp
	NEAT/src/NEAT_GeneticIndividual.cpp
	NEAT/src/NEAT_GeneticLinkGene.cpp
	NEAT/src/NEAT_GeneticNodeGene.cpp
	NEAT/src/NEAT_GeneticPopulation.cpp
	NEAT/src/NEAT_GeneticSpecies.cpp
	NEAT/src/NEAT_Globals.cpp
	NEAT/src/NEAT_ModularNetwork.cpp
	NEAT/src/NEAT_Network.cpp
	NEAT/src/NEAT_NetworkLink.cpp
	NEAT/src/NEAT_NetworkNode.cpp
	NEAT/src/NEAT_Random.cpp
	NEAT/src/cRandom.cc

	NEAT/include/NEAT_FastNetwork.h
	NEAT/include/NEAT_FastBiasNetwork.h
	NEAT/include/NEAT_GeneticGene.h
	NEAT/include/NEAT_GeneticGeneration.h
	NEAT/include/NEAT_GeneticIndividual.h
	NEAT/include/NEAT_GeneticLinkGene.h
	NEAT/include/NEAT_GeneticNodeGene.h
	NEAT/include/NEAT_GeneticPopulation.h
	NEAT/include/NEAT_GeneticSpecies.h
	NEAT/include/NEAT_Globals.h
	NEAT/include/NEAT.h
	NEAT/include/NEAT_Defines.h
	NEAT/include/NEAT_ModularNetwork.h
	NEAT/include/NEAT_Network.h
	NEAT/include/NEAT_NetworkLink.h
	NEAT/include/NEAT_NetworkNode.h
	NEAT/include/NEAT_Random.h
	NEAT/include/NEAT_STL.h
	include/HCUBE_Defines.h
	NEAT/include/cRandom.h
)

ADD_LIBRARY(
	Hypercube_NEAT_Base
	STATIC

	src/HCUBE_Defines.cpp
	src/HCUBE_ExperimentRun.cpp
	src/HCUBE_EvaluationSet.cpp

	src/hiller/Array3D.cpp
	src/hiller/Array3D.h
	src/hiller/DigitalMatter.cpp
	src/hiller/DigitalMatter.h
	src/hiller/MarchCube.cpp
	src/hiller/MarchCube.h
	src/hiller/Mesh.h
	src/hiller/Mesh.cpp
	src/hiller/XML_Rip.cpp
	src/hiller/XML_Rip.h

	src/Experiments/HCUBE_FindClusterExperiment.cpp
	src/Experiments/HCUBE_FindClusterNoGeomExperiment.cpp
	src/Experiments/HCUBE_SoftbotsExperiment.cpp
	src/Experiments/HCUBE_RCQuadratotExperiment.cpp

	include/HCUBE_Boost.h
	include/HCUBE_Defines.h
	include/HCUBE_EvaluationSet.h
	include/HCUBE_ExperimentRun.h
	include/HCUBE_STL.h

	include/Experiments/HCUBE_FindClusterExperiment.h
	include/Experiments/HCUBE_FindClusterNoGeomExperiment.h
	include/Experiments/HCUBE_RCQuadratotExperiment.h

	include/Experiments/HCUBE_Experiment.h
)

ADD_EXECUTABLE(
	Hypercube_NEAT

	src/main.cpp
)


TARGET_LINK_LIBRARIES(
	Hypercube_NEAT

	${Boost_LIBRARIES}

	Hypercube_NEAT_Base

	tinyxmldll
        zlib

	NEAT
)

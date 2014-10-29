
#ifndef HCUBE_DEFINES_H_INCLUDED
#define HCUBE_DEFINES_H_INCLUDED


#ifdef _MSC_VER
#pragma warning (disable : 4251)
#pragma warning (disable : 4996)
#endif

/** THESE ARE THE ONLY INCLUDES FROM THIS PROJECT THAT SHOULD BE IN THIS FILE! **/
#include "HCUBE_STL.h"
#include "HCUBE_Boost.h"

#include "JGTL_StackMap.h"
#include "JGTL_DynamicPoolMap.h"
#include "JGTL_Vector2.h"
#include "JGTL_Vector3.h"
#include "JGTL_Index3.h"
#include "JGTL_StringConverter.h"
#include "JGTL_LocatedException.h"
using namespace JGTL;

#ifdef _MSC_VER
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC // include Microsoft memory leak detection procedures
//#define _INC_MALLOC      // exclude standard memory alloc procedures
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <iomanip>
#endif
#endif

namespace HCUBE
{
    typedef Index3 Node;    
}


#include "NEAT.h"

#define HASBIT(NUMBER,BIT) (((NUMBER)&(1<<(BIT)))>0)
#define SETBIT(NUMBER,BIT) ((NUMBER)|=(1<<(BIT)))
#define UNSETBIT(NUMBER,BIT) ((NUMBER)&=~(1<<(BIT)))
#define TOGGLEBIT(NUMBER,BIT) ((NUMBER)^=(1<<(BIT)))

//#define PRINT_GENETIC_PERTUBATION_INFO (1)

namespace HCUBE
{
	extern const int NUM_THREADS;

    /** typedefs **/
    typedef unsigned int uint;
    typedef unsigned long long ulong;
    typedef unsigned char uchar;
    typedef unsigned short ushort;
    typedef DynamicPoolMap<Node,string > NodeMap;

    /** class Prototypes **/
    class Experiment;
    class ExperimentRun;

    class MainFrame;
    class ExperimentPanel;

    class UserEvaluationFrame;

    class EvaluationPanel;
    class NetworkPanel;
}

/** enums **/

enum ExperimentType
{
    EXPERIMENT_RCQUADRATOT=44,
    EXPERIMENT_END
};

#endif // HCUBE_DEFINES_H_INCLUDED

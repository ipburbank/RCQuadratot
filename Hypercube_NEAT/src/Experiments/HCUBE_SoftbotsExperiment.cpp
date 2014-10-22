#include <iomanip> 
#include "Experiments/HCUBE_SoftbotsExperiment.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <map>
#include <algorithm>
#include <queue>

namespace HCUBE
{
  SoftbotsExperiment::SoftbotsExperiment(string _experimentName)
    : Experiment(_experimentName)
  {
    cout << "Constructing experiment named SoftbotsExperiment.\n";
  }
}

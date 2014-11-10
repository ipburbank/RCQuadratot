#ifndef HCUBE_RCQUADRATOT_H_INCLUDED
#define HCUBE_RCQUADRATOT_H_INCLUDED

#include "HCUBE_Experiment.h"
#include "HCUBE_Vector2.h"

#include "tinyxmldll.h"
#include <boost/filesystem.hpp>

#include <fstream>
#include <stdlib.h>

namespace HCUBE
{
  class RCQuadratotExperiment : public Experiment
  {
  public:
  protected:

  public:
    RCQuadratotExperiment(string _experimentName);

    virtual ~RCQuadratotExperiment() {}
    
    virtual NEAT::GeneticPopulation* createInitialPopulation(int populationSize);

    double invidividualToFile(shared_ptr<NEAT::GeneticIndividual> individual, int generation, int individualId);
    virtual void processGroup(shared_ptr<NEAT::GeneticGeneration> generation);

    virtual Experiment* clone();
  };

}

#endif // HCUBE_RCQUADRATOT_H_INCLUDED

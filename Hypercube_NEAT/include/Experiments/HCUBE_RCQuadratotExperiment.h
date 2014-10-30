#ifndef HCUBE_RCQUADRATOT_H_INCLUDED
#define HCUBE_RCQUADRATOT_H_INCLUDED

#include "HCUBE_Experiment.h"

#include "HCUBE_Vector2.h"

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

    double processEvaluation(shared_ptr<NEAT::GeneticIndividual> individual);
    virtual void processGroup(shared_ptr<NEAT::GeneticGeneration> generation);

    virtual Experiment* clone();
  };

}

#endif // HCUBE_RCQUADRATOT_H_INCLUDED

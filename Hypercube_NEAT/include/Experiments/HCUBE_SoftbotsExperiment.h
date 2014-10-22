#ifndef HCUBE_SOFTBOTS_H_INCLUDED
#define HCUBE_SOFTBOTS_H_INCLUDED

#include "HCUBE_Experiment.h"

#include "HCUBE_Vector2.h"

#include <fstream>



namespace HCUBE
{

  class SoftbotsExperiment : public Experiment
  {
  public:
  protected:
		


  public:
    inline void setBestFitnessThisGen(double value) {0;}
    inline double getBestFitnessThisGen() {0;}
      
    SoftbotsExperiment(string _experimentName);
      
    virtual ~SoftbotsExperiment(){}
      
    virtual NEAT::GeneticPopulation* createInitialPopulation(int populationSize){}
      
    double mapXYvalToNormalizedGridCoord(const int & r_xyVal, const int & r_numVoxelsXorY){}
      
    double processEvaluation(shared_ptr<NEAT::GeneticIndividual> individual){}
      
    virtual void processGroup(shared_ptr<NEAT::GeneticGeneration> generation){}

    virtual void processIndividualPostHoc(shared_ptr<NEAT::GeneticIndividual> individual){}

    virtual void printNetworkCPPN(shared_ptr<const NEAT::GeneticIndividual> individual){}

    virtual Experiment* clone(){}
				
    bool converged(int generation){}

    bool outOfBoundingBox(double x, double y, double z){}

    double calculateFitnessAdjustment( vector< vector< vector< int > > > matrixForVoxelyze ){}

    void moveFitnessFile( shared_ptr<const NEAT::GeneticIndividual> individual ){}

    void writeVoxelyzeFile( vector< vector< vector< int > > > matrixForVoxelyze ){}

    int getMaterialAtThisVoxel(NEAT::FastNetwork <double> network, double x, double y, double z){}
  };

}

#endif // HCUBE_SHAPES_H_INCLUDED

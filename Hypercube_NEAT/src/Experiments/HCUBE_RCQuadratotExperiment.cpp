#include <iomanip> 
#include <sys/stat.h>
#include "Experiments/HCUBE_RCQuadratotExperiment.h"


namespace HCUBE
{
  using namespace NEAT;

  NEAT::GeneticPopulation* RCQuadratotExperiment::createInitialPopulation(int populationSize)
  {
    NEAT::GeneticPopulation* population = new NEAT::GeneticPopulation();
    vector<GeneticNodeGene> genes;
    
    // Include a bias node (set to 0.3 by default)
    genes.push_back(GeneticNodeGene("Bias","NetworkSensor",0,false));

    // THESE ARE THE INPUT NODES TO THE CPPN (from node -> to node):
    genes.push_back(GeneticNodeGene("from","NetworkSensor",0,false));
    genes.push_back(GeneticNodeGene("to","NetworkSensor",0,false));

    // THESE ARE THE OUTPUT NODES FROM THE CPPN:
    genes.push_back(GeneticNodeGene("Weight","NetworkOutputNode",1,false,ACTIVATION_FUNCTION_SIGMOID));

    for (size_t a=0;a<populationSize;a++)
      {
	shared_ptr<GeneticIndividual> individual(new GeneticIndividual(genes,true,1.0));
	population->addIndividual(individual);
      }
    
    return population;
  }

  RCQuadratotExperiment::RCQuadratotExperiment(string _experimentName)
    :   Experiment(_experimentName)
  {
    cout << "Constructing experiment: RCQuadratotExperiment.\n";
  }

  double RCQuadratotExperiment::processEvaluation(shared_ptr<NEAT::GeneticIndividual> individual)
  {
    NEAT::FastNetwork <double> network = individual->spawnFastPhenotypeStack<double>();

    network.reinitialize(); //reset CPPN
    
    network.setValue("Bias",0.3);

    network.setValue("to", 0); //set the input values...
    network.setValue("from", 0);
    
    network.update(); //run the CPPN network

    double weight = std::max(0.d, network.getValue("Weight"));
    cout << "weight is: " << weight << std::endl;

    return (weight + 1.0 ) * 100;
  }
  
  void RCQuadratotExperiment::processGroup(shared_ptr<NEAT::GeneticGeneration> generation)
  {
    // create folders for vxa files to be recorded by generation
    int genNum = generation->getGenerationNumber() + 1;

    for(int z=0;z< group.size();z++)
      {
	shared_ptr<NEAT::GeneticIndividual> individual = group[z];
	double fitness = processEvaluation(individual);
	if(fitness > std::numeric_limits<double>::max())
	  {
	    cout << "error: the max fitness is greater than the size of the double. " << endl;
	    cout << "max double size is: : " << std::numeric_limits<double>::max() << endl;
	    exit(88);
	  }
	if (fitness < 0)
	  {
	    cout << "Fitness Less Than Zero!!!, it is: " << fitness << "\n";
	    exit(10);
	  }

	cout << "Fitness: " << fitness << endl;
	individual->reward(fitness);
	
	cout << endl;
      }
  }
}

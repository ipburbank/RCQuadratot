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
    // LAYER TO CONSIDER:
    genes.push_back(GeneticNodeGene("layer","NetworkSensor",0,false));

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

  double RCQuadratotExperiment::invidividualToFile(shared_ptr<NEAT::GeneticIndividual> individual,
                                                   int generation, int individualId)
  {
    //config
    int numInputNeurons = NEAT::Globals::getSingleton()->getParameterValue("NumInputNeurons");
    int numHiddenNeurons = NEAT::Globals::getSingleton()->getParameterValue("NumHiddenNeurons");
    int numHiddenLayers = NEAT::Globals::getSingleton()->getParameterValue("NumHiddenLayers");
    int numOutputNeurons = NEAT::Globals::getSingleton()->getParameterValue("NumOutputNeurons");
    
    //neat network
    NEAT::FastNetwork <double> network = individual->spawnFastPhenotypeStack<double>();    
    network.reinitialize(); //reset CPPN
    network.setValue("Bias",0.3);

    //XML PREAMBLE
    char buffer [50];
    TiXmlDocument doc;
    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
    doc.LinkEndChild( decl );

    TiXmlElement * root = new TiXmlElement("RCQuadratotConfig");  
    doc.LinkEndChild( root );

    TiXmlElement* runConfig = new TiXmlElement("RunConfig");  
    root->LinkEndChild(runConfig);
    TiXmlElement* cfg;
    {
      cfg = new TiXmlElement("NumInputNeurons");
      sprintf(buffer, "%i", numInputNeurons);
      cfg->LinkEndChild( new TiXmlText(buffer));  
      runConfig->LinkEndChild( cfg );
      
      cfg = new TiXmlElement("NumHiddenNeurons");
      sprintf(buffer, "%i", numHiddenNeurons);
      cfg->LinkEndChild( new TiXmlText(buffer));  
      runConfig->LinkEndChild( cfg );

      cfg = new TiXmlElement("NumHiddenLayers");
      sprintf(buffer, "%i", numHiddenLayers);
      cfg->LinkEndChild( new TiXmlText(buffer));  
      runConfig->LinkEndChild( cfg );

      cfg = new TiXmlElement("numOutputNeurons");
      sprintf(buffer, "%i", numOutputNeurons);
      cfg->LinkEndChild( new TiXmlText(buffer));  
      runConfig->LinkEndChild( cfg );
    }

    TiXmlElement* weightElem;

    //input layer
    TiXmlElement* inputLayer = new TiXmlElement("InputLayer");  
    root->LinkEndChild(inputLayer);
    
    network.setValue("layer", -1);
    
    for(int i=0; i < numInputNeurons; i++)
      {
        for(int j=0; j < numHiddenNeurons; j++)
          {
            network.setValue("from", i);
            network.setValue("to", j); //set the input values...
            network.update(); //run the CPPN network
            
            weightElem = new TiXmlElement("Weight");
            sprintf(buffer, "%f", network.getValue("Weight"));
            weightElem->LinkEndChild( new TiXmlText(buffer));
            weightElem->SetAttribute("to", i);
            weightElem->SetAttribute("from", j);
            inputLayer->LinkEndChild(weightElem);
          }
      }

    //hidden layers
    TiXmlElement* hiddenLayers = new TiXmlElement("HiddenLayers");  
    root->LinkEndChild(hiddenLayers);

    for(int k=0; k < numHiddenLayers; k++)
      {
        network.setValue("layer", (1.0 / numHiddenLayers) * k - 0.5);
        TiXmlElement* hiddenLayer = new TiXmlElement("HiddenLayer");  
        hiddenLayers->LinkEndChild(hiddenLayer);
    
        for(int i=0; i < numHiddenNeurons; i++)
          {
            for(int j=0; j < numHiddenNeurons; j++)
              {
                network.setValue("from", i);
                network.setValue("to", j); //set the input values...
                network.update(); //run the CPPN network
            
                weightElem = new TiXmlElement("Weight");
                sprintf(buffer, "%f", network.getValue("Weight"));
                weightElem->LinkEndChild( new TiXmlText(buffer));
                weightElem->SetAttribute("to", i);
                weightElem->SetAttribute("from", j);
                hiddenLayer->LinkEndChild(weightElem);
              }
          }
      }

    //output layer
    TiXmlElement* outputLayer = new TiXmlElement("OutputLayer");
    root->LinkEndChild(outputLayer);
    
    network.setValue("layer", 1);
    
    for(int i=0; i < numHiddenNeurons; i++)
      {
        for(int j=0; j < numOutputNeurons; j++)
          {
            network.setValue("from", i);
            network.setValue("to", j); //set the input values...
            network.update(); //run the CPPN network
            
            weightElem = new TiXmlElement("Weight");
            sprintf(buffer, "%f", network.getValue("Weight"));
            weightElem->LinkEndChild( new TiXmlText(buffer));
            weightElem->SetAttribute("to", i);
            weightElem->SetAttribute("from", j);
            outputLayer->LinkEndChild(weightElem);
          }
      }

    sprintf(buffer, "runs/gen%i/", generation);
    boost::filesystem::create_directories(buffer);

    sprintf(buffer, "runs/gen%i/gen%i-individual%i.xml", generation, individualId);
    doc.SaveFile(buffer);
    
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
	double fitness = invidividualToFile(individual, genNum, z);
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

  Experiment* RCQuadratotExperiment::clone()
  {
    RCQuadratotExperiment* experiment = new RCQuadratotExperiment(*this);
    return experiment;
  }
}

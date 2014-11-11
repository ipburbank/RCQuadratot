#ifndef SIMULATIONVISUAL_H
#define SIMULATIONVISUAL_H

#include "BulletDemoFiles/GlutDemoApplication.h"
#include "Simulation.h"

class SimulationVisual : public GlutDemoApplication, public Simulation
{
 public:
  //resolve multiple inheritance issues
  void initPhysics()
  {
    setTexturing(true);
    setShadows(true);
    setCameraDistance(btScalar(5.));
    clientResetScene();		
    Simulation::initPhysics();
  };
  //btDynamicsWorld* getDynamicsWorld (){Simulation::getDynamicsWorld();};
  
  virtual void clientMoveAndDisplay();

  virtual void displayCallback();

  virtual void keyboardCallback(unsigned char key, int x, int y);

  virtual  void swapBuffers(){};
  virtual  void updateModifierKeys(){};

  static SimulationVisual* Create()
  {
    SimulationVisual* demo = new SimulationVisual();
    demo->myinit();
    return demo;
  }
};

#endif

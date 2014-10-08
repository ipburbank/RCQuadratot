#include "Simulation.h"
#include "btBulletDynamicsCommon.h"


int main(int argc,char** argv)
{
  Simulation* demo = new Simulation();

  demo->initPhysics();
  btDynamicsWorld* dynamicsWorld = demo->getDynamicsWorld();


  for (int i = 0; i < 500000; i++) {
                dynamicsWorld->stepSimulation(1 / 60.f, 10);
/*
                btTransform trans;
                fallRigidBody->getMotionState()->getWorldTransform(trans);

                std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;*/
        }

  delete demo;
  return 0;

}

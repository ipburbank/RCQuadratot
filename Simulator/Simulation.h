/*
  Bullet Continuous Collision Detection and Physics Library
  RagdollDemo
  Copyright (c) 2007 Starbreeze Studios

  This software is provided 'as-is', without any express or implied warranty.
  In no event will the authors be held liable for any damages arising from the use of this software.
  Permission is granted to anyone to use this software for any purpose, 
  including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Written by: Marten Svanfeldt
*/

#ifndef SIMULATION_H
#define SIMULATION_H

#include "RobotGeometry/Ludobot.h"
#include "ANN/neuralNet.h"

#include <math.h>

#include "LinearMath/btAlignedObjectArray.h"
class btBroadphaseInterface;
class btCollisionShape;
class btOverlappingPairCache;
class btCollisionDispatcher;
class btConstraintSolver;
struct btCollisionAlgorithmCreateFunc;
class btDefaultCollisionConfiguration;

class Simulation : public virtual DemoApplication
{
  btAlignedObjectArray<class RagDoll*> m_ragdolls;

  //keep the collision shapes, for deletion/cleanup
  btAlignedObjectArray<btCollisionShape*>	m_collisionShapes;

  btBroadphaseInterface*	m_broadphase;

  btCollisionDispatcher*	m_dispatcher;

  btConstraintSolver*	m_solver;

  btDefaultCollisionConfiguration* m_collisionConfiguration;
  
 public:
  Simulation(){}
  
  void initPhysics();
  
  void exitPhysics();
  
  static Simulation* Create()
  {
    Simulation* sim = new Simulation();
    sim->initPhysics();
    return sim;
  }

  ~Simulation()
    {
      exitPhysics();
    }
  
  void spawnRagdoll(const btVector3& startOffset);

  void jointTickCallback(btScalar timeStep);
};


#endif

/*
  Bullet Continuous Collision Detection and Physics Library
  Ragdoll Demo
  Copyright (c) 2007 Starbreeze Studios

  This software is provided 'as-is', without any express or implied warranty.
  In no event will the authors be held liable for any damages arising from the use of this software.
  Permission is granted to anyone to use this software for any purpose, 
  including commercial applications, and to alter it and redistribute it freely, 
  subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Written by: Marten Svanfeldt
*/

#include "btBulletDynamicsCommon.h"

#include "Simulation.h"

//for debug
#include <iostream>


// Enrico: Shouldn't these three variables be real constants and not defines?

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2     1.57079632679489661923
#endif

#ifndef M_PI_4
#define M_PI_4     0.785398163397448309616
#endif

void Simulation::initPhysics()
{
  // Setup the basic world

  m_collisionConfiguration = new btDefaultCollisionConfiguration();

  m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

  btVector3 worldAabbMin(-10000,-10000,-10000);
  btVector3 worldAabbMax(10000,10000,10000);
  m_broadphase = new btAxisSweep3 (worldAabbMin, worldAabbMax);

  m_solver = new btSequentialImpulseConstraintSolver;

  m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase,
                                                m_solver,m_collisionConfiguration);
  //m_dynamicsWorld->getDispatchInfo().m_useConvexConservativeDistanceUtil = true;
  //m_dynamicsWorld->getDispatchInfo().m_convexConservativeDistanceThreshold = 0.01f;



  // Setup a big ground box
  {
    btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(200.),
                                                             btScalar(10.),btScalar(200.)));
    m_collisionShapes.push_back(groundShape);
    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(0,-10,0));

#define CREATE_GROUND_COLLISION_OBJECT 1
#ifdef CREATE_GROUND_COLLISION_OBJECT
    btCollisionObject* fixedGround = new btCollisionObject();
    fixedGround->setCollisionShape(groundShape);
    fixedGround->setWorldTransform(groundTransform);
    m_dynamicsWorld->addCollisionObject(fixedGround);
#else
    localCreateRigidBody(btScalar(0.),groundTransform,groundShape);
#endif //CREATE_GROUND_COLLISION_OBJECT

  }

  // Spawn one ragdoll
  btVector3 startOffset(1,0.5,0);
  spawnRagdoll(startOffset);
}

void Simulation::spawnRagdoll(const btVector3& startOffset)
{
  RagDoll* ragDoll = new RagDoll (m_dynamicsWorld, startOffset);
  m_ragdolls.push_back(ragDoll);
}	

void	Simulation::exitPhysics()
{

  int i;

  for (i=0;i<m_ragdolls.size();i++)
    {
      RagDoll* doll = m_ragdolls[i];
      std::cout << "tada: " << doll->getLocation().getOrigin().getY() << std::endl;
      delete doll;
    }

  //cleanup in the reverse order of creation/initialization

  //remove the rigidbodies from the dynamics world and delete them
	
  for (i=m_dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
    {
      btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
      btRigidBody* body = btRigidBody::upcast(obj);
      if (body && body->getMotionState())
        {
          delete body->getMotionState();
        }
      m_dynamicsWorld->removeCollisionObject( obj );
      delete obj;
    }

  //delete collision shapes
  for (int j=0;j<m_collisionShapes.size();j++)
    {
      btCollisionShape* shape = m_collisionShapes[j];
      delete shape;
    }

  //delete dynamics world
  delete m_dynamicsWorld;

  //delete solver
  delete m_solver;

  //delete broadphase
  delete m_broadphase;

  //delete dispatcher
  delete m_dispatcher;

  delete m_collisionConfiguration;

	
}

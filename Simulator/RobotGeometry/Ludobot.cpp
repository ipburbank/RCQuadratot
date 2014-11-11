/*
  
 */
#include "Ludobot.h"
//for debug
#include <iostream>

#define CONSTRAINT_DEBUG_SIZE 0.2f

btRigidBody* RagDoll::localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape)
{
  bool isDynamic = (mass != 0.f);

  btVector3 localInertia(0,0,0);
  if (isDynamic)
    shape->calculateLocalInertia(mass,localInertia);

  btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);
  btRigidBody* body = new btRigidBody(rbInfo);

  m_ownerWorld->addRigidBody(body);

  return body;
}

RagDoll::RagDoll (btDynamicsWorld* ownerWorld, const btVector3& positionOffset)
  : m_ownerWorld (ownerWorld)
{
  // Setup the geometry
  m_shapes[BODYPART_BODY] = new btBoxShape(btVector3(1., .5, 1.));
  
  m_shapes[BODYPART_LEG1_TOP] = new btCylinderShape(btVector3(.25, 1., .5));
  m_shapes[BODYPART_LEG2_TOP] = new btCylinderShape(btVector3(.25, 1., .5));
  m_shapes[BODYPART_LEG3_TOP] = new btCylinderShape(btVector3(.25, 1., .5));
  m_shapes[BODYPART_LEG4_TOP] = new btCylinderShape(btVector3(.25, 1., .5));

  m_shapes[BODYPART_LEG1_BOTTOM] = new btCylinderShape(btVector3(.25, 1., .5));
  m_shapes[BODYPART_LEG2_BOTTOM] = new btCylinderShape(btVector3(.25, 1., .5));
  m_shapes[BODYPART_LEG3_BOTTOM] = new btCylinderShape(btVector3(.25, 1., .5));
  m_shapes[BODYPART_LEG4_BOTTOM] = new btCylinderShape(btVector3(.25, 1., .5));
  
  // Setup all the rigid bodies
  btTransform offset;
  offset.setIdentity();
  offset.setOrigin(positionOffset);

  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(btVector3(btScalar(0.), btScalar(1.75), btScalar(0.)));
  m_bodies[BODYPART_BODY] = localCreateRigidBody(btScalar(0), offset*transform, m_shapes[BODYPART_BODY]);
  
  transform.setIdentity();
  transform.setOrigin(btVector3(btScalar(2.), btScalar(1.75), btScalar(0.)));
  transform.getBasis().setEulerZYX(0,0,M_PI_2);
  m_bodies[BODYPART_LEG1_TOP] = localCreateRigidBody(btScalar(1.75), offset*transform, m_shapes[BODYPART_LEG1_TOP]);

  transform.setIdentity();
  transform.setOrigin(btVector3(btScalar(0.), btScalar(1.75), btScalar(2.)));
  transform.getBasis().setEulerZYX(M_PI_2,0,-M_PI_2);
  m_bodies[BODYPART_LEG2_TOP] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEG2_TOP]);

  transform.setIdentity();
  transform.setOrigin(btVector3(btScalar(-2.), btScalar(1.75), btScalar(0.)));
  transform.getBasis().setEulerZYX(0,0,M_PI_2);
  m_bodies[BODYPART_LEG3_TOP] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEG3_TOP]);

  transform.setIdentity();
  transform.setOrigin(btVector3(btScalar(0.), btScalar(1.75), btScalar(-2.)));
  transform.getBasis().setEulerZYX(M_PI_2,0,-M_PI_2);
  m_bodies[BODYPART_LEG4_TOP] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEG4_TOP]);

  transform.setIdentity();
  transform.setOrigin(btVector3(btScalar(3.), btScalar(0.), btScalar(0.)));
  transform.getBasis().setEulerZYX(0,0,0);
  m_bodies[BODYPART_LEG1_BOTTOM] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEG1_BOTTOM]);

  transform.setIdentity();
  transform.setOrigin(btVector3(btScalar(0.), btScalar(0.), btScalar(3.)));
  transform.getBasis().setEulerZYX(0,-M_PI_2,0);
  m_bodies[BODYPART_LEG2_BOTTOM] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEG2_BOTTOM]);

  transform.setIdentity();
  transform.setOrigin(btVector3(btScalar(-3.), btScalar(0.), btScalar(0.)));
  transform.getBasis().setEulerZYX(0,0,0);
  m_bodies[BODYPART_LEG3_BOTTOM] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEG3_BOTTOM]);

  transform.setIdentity();
  transform.setOrigin(btVector3(btScalar(0.), btScalar(0.), btScalar(-3.)));
  transform.getBasis().setEulerZYX(0,-M_PI_2,0);
  m_bodies[BODYPART_LEG4_BOTTOM] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEG4_BOTTOM]);


  // Setup some damping on the m_bodies
  for (int i = 0; i < BODYPART_COUNT; ++i)
    {
      m_bodies[i]->setDamping(0.05, 0.85);
      m_bodies[i]->setDeactivationTime(0.8);
      m_bodies[i]->setSleepingThresholds(1.6, 2.5);
    }

  // Now setup the constraints
  btHingeConstraint* hingeC;
  btTransform localA, localB;

  {
    localA.setIdentity();
    localA.getBasis().setEulerZYX(0,0,M_PI_2);
    localA.setOrigin(btVector3(btScalar(1.), btScalar(0.), btScalar(0.)));
  
    localB.setIdentity();
    localB.getBasis().setEulerZYX(0,0,0);
    localB.setOrigin(btVector3(btScalar(0.), btScalar(1.), btScalar(0.)));
  
    hingeC = new btHingeConstraint(*m_bodies[BODYPART_BODY], *m_bodies[BODYPART_LEG1_TOP], localA, localB);
    hingeC->setLimit(btScalar(-M_PI_2), btScalar(M_PI_2));
    m_joints[JOINT_LEG1_HIP] = hingeC;
    hingeC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

    m_ownerWorld->addConstraint(m_joints[JOINT_LEG1_HIP], true);
  }
  
  {
    localA.setIdentity();
    localA.getBasis().setEulerZYX(0,-M_PI_2,0);
    localA.setOrigin(btVector3(btScalar(0.), btScalar(0.), btScalar(1.)));
  
    localB.setIdentity();
    localB.getBasis().setEulerZYX(0,0,0);
    localB.setOrigin(btVector3(btScalar(0.), btScalar(-1.), btScalar(0.)));
  
    hingeC = new btHingeConstraint(*m_bodies[BODYPART_BODY], *m_bodies[BODYPART_LEG2_TOP], localA, localB);
    hingeC->setLimit(btScalar(0), btScalar(M_PI));
    m_joints[JOINT_LEG2_HIP] = hingeC;
    hingeC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

    m_ownerWorld->addConstraint(m_joints[JOINT_LEG2_HIP], true);
  }
  
  {
    localA.setIdentity();
    localA.getBasis().setEulerZYX(0,0,-M_PI_2);
    localA.setOrigin(btVector3(btScalar(-1.), btScalar(0.), btScalar(0.)));
  
    localB.setIdentity();
    localB.getBasis().setEulerZYX(0,0,0);
    localB.setOrigin(btVector3(btScalar(0.), btScalar(-1.), btScalar(0.)));
  
    hingeC = new btHingeConstraint(*m_bodies[BODYPART_BODY], *m_bodies[BODYPART_LEG3_TOP], localA, localB);
    hingeC->setLimit(btScalar(M_PI_2), btScalar(M_PI + M_PI_2));
    m_joints[JOINT_LEG3_HIP] = hingeC;
    hingeC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

    m_ownerWorld->addConstraint(m_joints[JOINT_LEG3_HIP], true);
  }
  
  {
    localA.setIdentity();
    localA.getBasis().setEulerZYX(0,-M_PI_2,0);
    localA.setOrigin(btVector3(btScalar(0.), btScalar(0.), btScalar(-1.)));
  
    localB.setIdentity();
    localB.getBasis().setEulerZYX(0,0,0);
    localB.setOrigin(btVector3(btScalar(0.), btScalar(1.), btScalar(0.)));
  
    hingeC = new btHingeConstraint(*m_bodies[BODYPART_BODY], *m_bodies[BODYPART_LEG4_TOP], localA, localB);
    hingeC->setLimit(btScalar(0), btScalar(M_PI));
    m_joints[JOINT_LEG4_HIP] = hingeC;
    hingeC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

    m_ownerWorld->addConstraint(m_joints[JOINT_LEG4_HIP], true);
  }
  
  {
    localA.setIdentity();
    localA.getBasis().setEulerZYX(0,0,0);
    localA.setOrigin(btVector3(btScalar(0.), btScalar(-1.), btScalar(0.)));
  
    localB.setIdentity();
    localB.getBasis().setEulerZYX(0,0,0);
    localB.setOrigin(btVector3(btScalar(0.), btScalar(1.), btScalar(0.)));
  
    hingeC = new btHingeConstraint(*m_bodies[BODYPART_LEG1_TOP], *m_bodies[BODYPART_LEG1_BOTTOM], localA, localB);
    hingeC->setLimit(btScalar(-M_PI_2), btScalar(M_PI_2));
    m_joints[JOINT_LEG1_KNEE] = hingeC;
    hingeC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

    m_ownerWorld->addConstraint(m_joints[JOINT_LEG1_KNEE], true);
  }
  
  {
    localA.setIdentity();
    localA.getBasis().setEulerZYX(0,0,0);
    localA.setOrigin(btVector3(btScalar(0.), btScalar(1.), btScalar(0.)));
  
    localB.setIdentity();
    localB.getBasis().setEulerZYX(0,0,0);
    localB.setOrigin(btVector3(btScalar(0.), btScalar(1.), btScalar(0.)));
  
    hingeC = new btHingeConstraint(*m_bodies[BODYPART_LEG2_TOP], *m_bodies[BODYPART_LEG2_BOTTOM], localA, localB);
    hingeC->setLimit(btScalar(M_PI_2), btScalar(M_PI_2 + M_PI));
    m_joints[JOINT_LEG2_KNEE] = hingeC;
    hingeC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

    m_ownerWorld->addConstraint(m_joints[JOINT_LEG2_KNEE], true);
  }
  
  {
    localA.setIdentity();
    localA.getBasis().setEulerZYX(0,0,0);
    localA.setOrigin(btVector3(btScalar(0.), btScalar(1.), btScalar(0.)));
  
    localB.setIdentity();
    localB.getBasis().setEulerZYX(0,0,0);
    localB.setOrigin(btVector3(btScalar(0.), btScalar(1.), btScalar(0.)));
  
    hingeC = new btHingeConstraint(*m_bodies[BODYPART_LEG3_TOP], *m_bodies[BODYPART_LEG3_BOTTOM], localA, localB);
    hingeC->setLimit(btScalar(M_PI_2), btScalar(M_PI_2 + M_PI));
    m_joints[JOINT_LEG3_KNEE] = hingeC;
    hingeC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

    m_ownerWorld->addConstraint(m_joints[JOINT_LEG3_KNEE], true);
  }
  
  {
    localA.setIdentity();
    localA.getBasis().setEulerZYX(0,0,0);
    localA.setOrigin(btVector3(btScalar(0.), btScalar(-1.), btScalar(0.)));
  
    localB.setIdentity();
    localB.getBasis().setEulerZYX(0,0,0);
    localB.setOrigin(btVector3(btScalar(0.), btScalar(1.), btScalar(0.)));
  
    hingeC = new btHingeConstraint(*m_bodies[BODYPART_LEG4_TOP], *m_bodies[BODYPART_LEG4_BOTTOM], localA, localB);
    hingeC->setLimit(btScalar(-M_PI_2), btScalar(M_PI_2));
    m_joints[JOINT_LEG4_KNEE] = hingeC;
    hingeC->setDbgDrawSize(CONSTRAINT_DEBUG_SIZE);

    m_ownerWorld->addConstraint(m_joints[JOINT_LEG4_KNEE], true);
  }

  // add motors
  for (int i=0; i < JOINT_COUNT; ++i)
    {
      m_joints[i]->enableMotor(true);
      m_joints[i]->setMaxMotorImpulse(btScalar(1));
    }
  //disable deactivation for legs
  for (int i=0; i < BODYPART_COUNT; ++i)
    {
      m_bodies[i]->setActivationState(DISABLE_DEACTIVATION);
    }
}

RagDoll::~RagDoll ()
{
  int i;

  // Remove all constraints
  for ( i = 0; i < JOINT_COUNT; ++i)
    {
      m_ownerWorld->removeConstraint(m_joints[i]);
      delete m_joints[i]; m_joints[i] = 0;
    }

  // Remove all bodies and shapes
  for ( i = 0; i < BODYPART_COUNT; ++i)
    {
      m_ownerWorld->removeRigidBody(m_bodies[i]);
			
      delete m_bodies[i]->getMotionState();

      delete m_bodies[i]; m_bodies[i] = 0;
      delete m_shapes[i]; m_shapes[i] = 0;
    }
}

void RagDoll::setJointTarget(int jointId, float angle)
{
  auto joint = m_joints[jointId];
  angle = joint->getLowerLimit()
    + (joint->getUpperLimit() - joint->getLowerLimit()) * angle;

  joint->setMotorTarget(btScalar(angle), btScalar(1));
}

btTransform RagDoll::getLocation()
{
  btTransform trans;
  m_bodies[BODYPART_BODY]->getMotionState()->getWorldTransform(trans);
  return trans;
}

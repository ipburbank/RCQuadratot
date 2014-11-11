/*
  Ludobot robot geometery
*/

#ifndef LUDOBOT_H
#define LUDOBOT_H

#include "BulletDemoFiles/DemoApplication.h"
#include "LinearMath/btAlignedObjectArray.h"

#include "btBulletDynamicsCommon.h"

class RagDoll
{
  enum
  {
    BODYPART_BODY = 0,
    
    BODYPART_LEG1_TOP,
    BODYPART_LEG2_TOP,
    BODYPART_LEG3_TOP,
    BODYPART_LEG4_TOP,

    BODYPART_LEG1_BOTTOM,
    BODYPART_LEG2_BOTTOM,
    BODYPART_LEG3_BOTTOM,
    BODYPART_LEG4_BOTTOM,

    BODYPART_COUNT
  };

  enum
  {
    JOINT_LEG1_HIP = 0,
    JOINT_LEG2_HIP,
    JOINT_LEG3_HIP,
    JOINT_LEG4_HIP,
    JOINT_LEG1_KNEE,
    JOINT_LEG2_KNEE,
    JOINT_LEG3_KNEE,
    JOINT_LEG4_KNEE,

    JOINT_COUNT
  };

  btDynamicsWorld* m_ownerWorld;
  btCollisionShape* m_shapes[BODYPART_COUNT];
  btRigidBody* m_bodies[BODYPART_COUNT];
  btHingeConstraint* m_joints[JOINT_COUNT];

  btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape);

 public:
  RagDoll (btDynamicsWorld* ownerWorld, const btVector3& positionOffset);
  /**
   * set a joint position
   * @param joint which joint to control
   * @param angle in [0, 1]
   */
  void setJointTarget(int joint, float angle);
  btTransform getLocation();

  virtual ~RagDoll ();
};

#endif

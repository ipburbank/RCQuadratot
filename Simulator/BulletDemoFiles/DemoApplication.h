/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2006 Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef DEMO_APPLICATION_H
#define DEMO_APPLICATION_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include "LinearMath/btVector3.h"
#include "LinearMath/btMatrix3x3.h"
#include "LinearMath/btTransform.h"
#include "LinearMath/btQuickprof.h"
#include "LinearMath/btAlignedObjectArray.h"

class	btCollisionShape;
class	btDynamicsWorld;
class	btRigidBody;
class	btTypedConstraint;



class DemoApplication
{
protected:
	class CProfileIterator* m_profileIterator;

	protected:
#ifdef USE_BT_CLOCK
	btClock m_clock;
#endif //USE_BT_CLOCK

	///this is the most important class
	btDynamicsWorld*		m_dynamicsWorld;

	

	

	btCollisionShape*	m_shootBoxShape;

	int	m_debugMode;

	float m_ele;
	float m_azi;
	
protected:


	
	float	m_frustumZNear;
	float	m_frustumZFar;

	int	m_ortho;

	float	m_ShootBoxInitialSpeed;

	bool	m_stepping;
	bool m_singleStep;
	bool m_idle;
	int m_lastKey;

	
	
	btScalar		m_defaultContactProcessingThreshold;

public:

	DemoApplication();

	virtual ~DemoApplication();

	void 		setDynamicsWorld(btDynamicsWorld* world)
	{
		m_dynamicsWorld=world;
	}


	btDynamicsWorld*		getDynamicsWorld()
	{
		return m_dynamicsWorld;
	}

	virtual	void initPhysics() = 0;

	
	/*
	virtual void keyboardCallback(unsigned char key, int x, int y){}

	virtual void keyboardUpCallback(unsigned char key, int x, int y) {}

	virtual void specialKeyboard(int key, int x, int y){}
	
	virtual void specialKeyboardUp(int key, int x, int y){}

	virtual void reshape(int w, int h);

	virtual void mouseFunc(int button, int state, int x, int y);
*/


	int		getDebugMode()
	{
		return m_debugMode ;
	}

	void	setDebugMode(int mode);

	void	setAzi(float azi)
	{
		m_azi = azi;
	}

	void	setEle(float ele)
	{
		m_ele = ele;
	}


	void toggleIdle();

	
	btScalar	getDeltaTimeMicroseconds()
	{
#ifdef USE_BT_CLOCK
		btScalar dt = (btScalar)m_clock.getTimeMicroseconds();
		m_clock.reset();
		return dt;
#else
		return btScalar(16666.);
#endif
	}
	void setFrustumZPlanes(float zNear, float zFar)
	{
		m_frustumZNear = zNear;
		m_frustumZFar = zFar;
	}



	///Demo functions
	virtual void setShootBoxShape ();
	virtual void	shootBox(const btVector3& destination);


	
	btRigidBody*	localCreateRigidBody(float mass, const btTransform& startTransform,btCollisionShape* shape);

	bool	isIdle() const
	{
		return	m_idle;
	}

	void	setIdle(bool idle)
	{
		m_idle = idle;
	}


};

#endif //DEMO_APPLICATION_H



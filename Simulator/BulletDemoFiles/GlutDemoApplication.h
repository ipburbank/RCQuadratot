/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2009 Erwin Coumans  http://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/


#ifndef GLUT_DEMO_APPLICATION_H
#define GLUT_DEMO_APPLICATION_H

#include "DemoApplication.h"
#include "GlutStuff.h"
#include "GL_ShapeDrawer.h"


ATTRIBUTE_ALIGNED16(class) GlutDemoApplication : public virtual DemoApplication
{
private:
	float	m_cameraDistance;
	btVector3 m_cameraPosition;
	btVector3 m_cameraTargetPosition;//look at

	int	m_mouseOldX;
	int	m_mouseOldY;
	int	m_mouseButtons;
public:
	
	virtual void myinit();
	int	m_modifierKeys;

	GlutDemoApplication() :
		m_glutScreenWidth(0),
m_pickConstraint(0),
m_cameraDistance(15.0),
m_cameraPosition(0.f,0.f,0.f),
m_cameraTargetPosition(0.f,0.f,0.f),
m_mouseOldX(0),
m_mouseOldY(0),
m_mouseButtons(0),
m_modifierKeys(0),
m_scaleBottom(0.5f),
m_scaleFactor(2.f),
m_cameraUp(0,1,0),
m_forwardAxis(2),
m_zoomStepSize(0.4),
m_sundirection(btVector3(1,-2,1)*1000),
m_enableshadows(false),
		m_glutScreenHeight(0)
{
	m_shapeDrawer = new GL_ShapeDrawer ();
	m_shapeDrawer->enableTexture(true);
	m_enableshadows = false;
}

~GlutDemoApplication()
{
	if (m_shootBoxShape)
		delete m_shootBoxShape;

	if (m_shapeDrawer)
		delete m_shapeDrawer;

}

	BT_DECLARE_ALIGNED_ALLOCATOR();



	void overrideGLShapeDrawer (GL_ShapeDrawer* shapeDrawer);

bool	setTexturing(bool enable) { return(m_shapeDrawer->enableTexture(enable)); }
	bool	setShadows(bool enable)	{ bool p=m_enableshadows;m_enableshadows=enable;return(p); }
	bool	getTexturing() const
	{
		return m_shapeDrawer->hasTextureEnabled();
	}
	bool	getShadows() const
	{
		return m_enableshadows;
	}

void	setCameraUp(const btVector3& camUp)
	{
		m_cameraUp = camUp;
	}
	void	setCameraForwardAxis(int axis)
	{
		m_forwardAxis = axis;
	}

	///glut callbacks

	float	getCameraDistance();
	void	setCameraDistance(float dist);
	void	moveAndDisplay();

	virtual void clientMoveAndDisplay() = 0;

	virtual void	clientResetScene();

	///callback methods by glut

	virtual void keyboardCallback(unsigned char key, int x, int y);

	virtual void keyboardUpCallback(unsigned char key, int x, int y) {}

	virtual void specialKeyboard(int key, int x, int y);

	virtual void specialKeyboardUp(int key, int x, int y);

	virtual void reshape(int w, int h);

	virtual void mouseFunc(int button, int state, int x, int y);

	virtual void	mouseMotionFunc(int x,int y);

	virtual void displayCallback();

	virtual 	void renderme();

	virtual		void swapBuffers() = 0;

	virtual		void	updateModifierKeys() = 0;

	void stepLeft();
	void stepRight();
	void stepFront();
	void stepBack();
	void zoomIn();
	void zoomOut();

virtual	void setDrawClusters(bool drawClusters)
	{

	}
void setOrthographicProjection();
	void resetPerspectiveProjection();

	virtual void updateCamera();

	btVector3	getCameraPosition()
	{
		return m_cameraPosition;
	}
	btVector3	getCameraTargetPosition()
	{
		return m_cameraTargetPosition;
	}

btVector3	getRayTo(int x,int y);



protected:
float m_scaleBottom;
	float m_scaleFactor;
	int	m_forwardAxis;
	float m_zoomStepSize;
	

	void	displayProfileString(int xOffset,int yStart,char* message);
	virtual void removePickingConstraint();

///constraint for mouse picking
	btTypedConstraint*		m_pickConstraint;

virtual void pickObject(const btVector3& pickPos, const class btCollisionObject* hitObj);

void showProfileInfo(int& xOffset,int& yStart, int yIncr);
	void renderscene(int pass);


btVector3 m_cameraUp;

int m_glutScreenWidth;
	int m_glutScreenHeight;


GL_ShapeDrawer*	m_shapeDrawer;
	bool			m_enableshadows;
	btVector3		m_sundirection;

};
#endif //GLUT_DEMO_APPLICATION_H


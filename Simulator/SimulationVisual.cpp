#include "SimulationVisual.h"

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2     1.57079632679489661923
#endif

#ifndef M_PI_4
#define M_PI_4     0.785398163397448309616
#endif

void SimulationVisual::clientMoveAndDisplay()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

  //simple dynamics world doesn't handle fixed-time-stepping
  float ms = getDeltaTimeMicroseconds();

  float minFPS = 1000000.f/60.f;
  if (ms > minFPS)
    ms = minFPS;

  if (Simulation::m_dynamicsWorld)
    {
      Simulation::m_dynamicsWorld->stepSimulation(ms / 1000000.f);
		
      //optional but useful: debug drawing
      Simulation::m_dynamicsWorld->debugDrawWorld();


    }

  renderme(); 

  glFlush();

  glutSwapBuffers();
}

void SimulationVisual::displayCallback()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

  renderme();

  //optional but useful: debug drawing
  if (Simulation::m_dynamicsWorld)
    Simulation::m_dynamicsWorld->debugDrawWorld();

  glFlush();
  glutSwapBuffers();
}

void SimulationVisual::keyboardCallback(unsigned char key, int x, int y)
{
  switch (key)
    {
    case 'e':
      {
        btVector3 startOffset(0,2,0);
        spawnRagdoll(startOffset);
        break;
      }
    default:
      GlutDemoApplication::keyboardCallback(key, x, y);
    }	
}

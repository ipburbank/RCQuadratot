add_library(BulletDemoFiles DemoApplication.cpp)

if(BUILD_VISUAL)
add_library(BulletDemoGlut GLDebugFont.cpp GlutDemoApplication.cpp GL_ShapeDrawer.cpp RenderTexture.cpp GLDebugDrawer.cpp GlutStuff.cpp GL_DialogDynamicsWorld.cpp GL_DialogWindow.cpp stb_image.cpp)
endif(BUILD_VISUAL)

#include "ParticleSystem.hpp"
#include "Project7a.hpp"

ParticleSystem * ParticleSystem::particleSystemSingleton;

ParticleSystem::ParticleSystem()
{
	ParticleSystem::particleSystemSingleton = this;
	// random parameters:
	WINDOWTITLE = "OpenCL/OpenGL Particle System -- Jeremy Prater";
	GLUITITLE = "User Interface Window";

	VMIN = -100.;
	VMAX = 100.;

	NUM_PARTICLES = 8 * 1024 * 1024;
	LOCAL_SIZE = 32;
	CL_FILE_NAME = "src/particles.cl";
	CL_BINARY_NAME = "src/particles.nv";

	INIT_WINDOW_SIZE = 700; // window size in pixels

	drawDistance = 10000000.;
	ANGFACT = (float)M_PI / 512.0f;
	SCLFACT = 250.0f;
	MINSCALE = 0.001f;
	
	memset(&BACKCOLOR, 0, sizeof(BACKCOLOR));

	AXES_COLOR.x = 1.0f;
	AXES_COLOR.y = 0.5f;
	AXES_COLOR.z = 0.0f;
	
	AXES_WIDTH = 3.0f;

	GlobalWorkSize[0] = NUM_PARTICLES;
	GlobalWorkSize[1] = 1;
	GlobalWorkSize[2] = 1;
  
	LocalWorkSize[0] = LOCAL_SIZE;
	LocalWorkSize[1] = 1;
	LocalWorkSize[2] = 1;
}

ParticleSystem::~ParticleSystem()
{
    
}

//
// exit gracefully:
//

void ParticleSystem::Quit()
{
	Glui->close();
	glutSetWindow(MainWindow);
	glFinish();
	glutDestroyWindow(MainWindow);


	// 13. clean everything up:

	clReleaseKernel(Kernel);
	clReleaseProgram(Program);
	clReleaseCommandQueue(CmdQueue);
	clReleaseMemObject(CLParticlePosition);
	clReleaseMemObject(CLParticleColor);

	free(GLParticleVelocity);
}
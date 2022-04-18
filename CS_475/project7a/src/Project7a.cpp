#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <omp.h>

#include "Project7a.hpp"

//
// main Program:
//

int
main(int argc, char *argv[])
{
	ParticleSystem * particleSystem = new ParticleSystem();
	glutInit(&argc, argv);
	particleSystem->InitGraphics();
	particleSystem->InitLists();
	particleSystem->InitCL();
	particleSystem->Reset();
	particleSystem->InitGlui();
	glutMainLoop();

	delete particleSystem;
	return 0;
}


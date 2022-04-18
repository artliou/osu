#include "Project7a.hpp"

// fraction of the length to use as height of the characters:
#define LENFRAC		0.10f

// fraction of length to use as start location of the characters:
#define BASEFRAC	1.10f

/////////////////////////////////////////////////////////////////
//
//
// OpenGL Static variables.
//
//
/////////////////////////////////////////////////////////////////


// the stroke characters 'X' 'Y' 'Z' :

static float xx[] = {
	0., 1., 0., 1.
};

static float xy[] = {
	-.5, .5, .5, -.5
};

static int xorder[] = {
	1, 2, -3, 4
};


static float yx[] = {
	0., 0., -.5, .5
};

static float yy[] = {
	0., .6f, 1., 1.
};

static int yorder[] = {
	1, 2, 3, -2, 4
};


static float zx[] = {
	1., 0., 1., 0., .25, .75
};

static float zy[] = {
	.5, .5, -.5, -.5, 0., 0.
};

static int zorder[] = {
	1, 2, 3, 4, -5, 6
};

/////////////////////////////////////////////////////////////////
//
//
// OpenGL Functions
//
//
/////////////////////////////////////////////////////////////////
//
// initialize the glut and OpenGL libraries:
//	also setup display lists and callback functions
//

void ParticleSystem::InitGraphics()
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(INIT_WINDOW_SIZE, INIT_WINDOW_SIZE);

	MainWindow = glutCreateWindow(WINDOWTITLE);
	glutSetWindowTitle(WINDOWTITLE);
	glClearColor(BACKCOLOR.x, BACKCOLOR.y, BACKCOLOR.y, BACKCOLOR.z);


	// setup the callback routines:

	glutSetWindow(MainWindow);
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(NULL);
	glutVisibilityFunc(Visibility);
	glutEntryFunc(NULL);
	glutSpecialFunc(NULL);
	glutSpaceballMotionFunc(NULL);
	glutSpaceballRotateFunc(NULL);
	glutSpaceballButtonFunc(NULL);
	glutButtonBoxFunc(NULL);
	glutDialsFunc(NULL);
	glutTabletMotionFunc(NULL);
	glutTabletButtonFunc(NULL);
	glutMenuStateFunc(NULL);
	glutTimerFunc(0, NULL, 0);

#ifdef WIN32
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		printf("glewInit Error\n");
	}
#endif
}

//
// draw the complete scene:
//

void ParticleSystem::Display()
{
	ParticleSystem * context = ParticleSystem::particleSystemSingleton;
	glutSetWindow(context->MainWindow);
	glDrawBuffer(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	GLsizei vx = glutGet(GLUT_WINDOW_WIDTH);
	GLsizei vy = glutGet(GLUT_WINDOW_HEIGHT);
	GLsizei v = vx < vy ? vx : vy;			// minimum dimension
	GLint xl = (vx - v) / 2;
	GLint yb = (vy - v) / 2;
	glViewport(xl, yb,  v, v);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(context->WhichProjection == ORTHO)
		glOrtho(-300., 300.,  -300., 300., 0.1, context->drawDistance);
	else
		gluPerspective(50., 1.,	0.1, context->drawDistance);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float4 eyePosition = ParticleSystem::GetXYZfromPolar(context->eyeDistance, context->mouseTheta, context->mousePhi);
	gluLookAt(eyePosition.x, eyePosition.y, eyePosition.z,
				0.0f ,0.0f, 0.0f,
				0.0f, 1.0f, 0.0f);
	glTranslatef((GLfloat)context->TransXYZ[0], (GLfloat)context->TransXYZ[1], -(GLfloat)context->TransXYZ[2]);
	//glRotatef((GLfloat)context->mousePhi, 0., 1., 0.);
	//glRotatef((GLfloat)context->mouseTheta, 1., 0., 0.);
	glMultMatrixf((const GLfloat *)context->RotMatrix);
	glScalef((GLfloat)context->Scale, (GLfloat)context->Scale, (GLfloat)context->Scale);
	float scale2 = 1.f + context->Scale2;		// because glui translation starts at 0.
	if(scale2 < context->MINSCALE)
		scale2 = context->MINSCALE;
	glScalef((GLfloat)scale2, (GLfloat)scale2, (GLfloat)scale2);

	glDisable(GL_FOG);

	if(context->AxesOn != false)
		glCallList(context->AxesList);

	// ****************************************
	// Here is where you draw the current state of the particles:
	// ****************************************

	glBindBuffer(GL_ARRAY_BUFFER, context->GLParticlePosition);
	glVertexPointer(4, GL_FLOAT, 0, (void *)0);
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, context->GLParticleColor);
	glColorPointer(4, GL_FLOAT, 0, (void *)0);
	glEnableClientState(GL_COLOR_ARRAY);

	glPointSize(3.);
	glDrawArrays(GL_POINTS, 0, context->NUM_PARTICLES);
	glPointSize(1.);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glCallList(context->SphereList);

	//if((Frame%100) == 0)
		//WriteFrame();

	context->Frame++;
	if(context->ShowPerformance)
	{
		char str[128];
		sprintf(str, "Frame %8d -- %6.1f GigaParticles/Sec --  %d particles", context->Frame, (float)context->NUM_PARTICLES / context->ElapsedTime / 1000000000., context->NUM_PARTICLES);
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0., 100.,     0., 100.);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1., 1., 1.);
		context->DoRasterString(5., 95., 0., str);
	}

	glutSwapBuffers();
	glFlush();
}

//
// initialize the display lists that will not change:
//

void ParticleSystem::InitLists()
{
	ParticleSystem * context = ParticleSystem::particleSystemSingleton;
	SphereList = glGenLists(1);
	glNewList(SphereList, GL_COMPILE);
		glColor3f(.9f, .9f, 0.);
		glPushMatrix();
			//glTranslatef(-100., -800., 0.);
			glutWireSphere(50000., 20, 20);
		glPopMatrix();
	glEndList();

	AxesList = glGenLists(1);
	glNewList(AxesList, GL_COMPILE);
		glColor3fv((GLfloat*)&context->AXES_COLOR);
		glLineWidth(context->AXES_WIDTH);
			Axes(150.);
		glLineWidth(1.);
	glEndList();
}



void ParticleSystem::WriteFrame()
{
        char filename[128];
        sprintf(filename, "jparallel.%03d.particles", Frame); // use your engr login instead
        FILE *fp = fopen(filename, "w");
        if(fp == NULL)
        {
                printf("Cannot create file '%s'\n", filename);
                return;
       }

        fprintf(fp, "%5d  %10d\n", Frame, NUM_PARTICLES);

        glBindBuffer(GL_ARRAY_BUFFER, GLParticlePosition);
        float4 * points = (float4 *) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
        for(int i = 0; i < NUM_PARTICLES; i++)
        {
                fprintf(fp, "%8.2f  %8.2f  %8.2f\n", points[i].x, points[i].y, points[i].z);
		}
        glUnmapBuffer(GL_ARRAY_BUFFER);

        glBindBuffer(GL_ARRAY_BUFFER, GLParticleColor);
        float3 *colors = (float3 *) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
        for(int i = 0; i < NUM_PARTICLES; i++)
        {
                fprintf(fp, "%8.2f  %8.2f  %8.2f\n", colors[i].x, colors[i].y, colors[i].z);
       }
        glUnmapBuffer(GL_ARRAY_BUFFER);

        fclose(fp);
}

//
//	Draw a set of 3D axes:
//	(length is the axis length in world coordinates)
//

void ParticleSystem::Axes(float length)
{
	glBegin(GL_LINE_STRIP);
	glVertex3f(length, 0., 0.);
	glVertex3f(0., 0., 0.);
	glVertex3f(0., length, 0.);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0., 0., 0.);
	glVertex3f(0., 0., length);
	glEnd();

	float fact = LENFRAC * length;
	float base = BASEFRAC * length;

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 4; i++)
	{
		int j = xorder[i];
		if (j < 0)
		{

			glEnd();
			glBegin(GL_LINE_STRIP);
			j = -j;
		}
		j--;
		glVertex3f(base + fact*xx[j], fact*xy[j], 0.0);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 5; i++)
	{
		int j = yorder[i];
		if (j < 0)
		{

			glEnd();
			glBegin(GL_LINE_STRIP);
			j = -j;
		}
		j--;
		glVertex3f(fact*yx[j], base + fact*yy[j], 0.0);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 6; i++)
	{
		int j = zorder[i];
		if (j < 0)
		{

			glEnd();
			glBegin(GL_LINE_STRIP);
			j = -j;
		}
		j--;
		glVertex3f(0.0, fact*zy[j], base + fact*zx[j]);
	}
	glEnd();

}
//
// reset the transformations and the colors:
//
// this only sets the global variables --
// the glut main loop is responsible for redrawing the scene
//

void ParticleSystem::Reset()
{
	ActiveButton = 0;
	AxesOn = false;
	Frame = 0;
	Paused = false;
	Scale  = 1.0;
	Scale2 = 0.0;		// because add 1. to it in Display()
	ShowPerformance = false;
	WhichProjection = PERSP;
	mouseTheta = mousePhi = 0.;
	eyeDistance = 100000;
	TransXYZ[0] = TransXYZ[1] = TransXYZ[2] = 0.;

	                  RotMatrix[0][1] = RotMatrix[0][2] = RotMatrix[0][3] = 0.;
	RotMatrix[1][0]                   = RotMatrix[1][2] = RotMatrix[1][3] = 0.;
	RotMatrix[2][0] = RotMatrix[2][1]                   = RotMatrix[2][3] = 0.;
	RotMatrix[3][0] = RotMatrix[3][1] = RotMatrix[3][3]                   = 0.;
	RotMatrix[0][0] = RotMatrix[1][1] = RotMatrix[2][2] = RotMatrix[3][3] = 1.;
}
void ParticleSystem::Resize(int width, int height)
{
	ParticleSystem * context = ParticleSystem::particleSystemSingleton;
	glutSetWindow(context->MainWindow);
	glutPostRedisplay();
}

void ParticleSystem::Visibility (int state)
{
	ParticleSystem * context = ParticleSystem::particleSystemSingleton;
	if(state == GLUT_VISIBLE)
	{
		glutSetWindow(context->MainWindow);
		glutPostRedisplay();
	}
	else
	{
		// could optimize by keeping track of the fact
		// that the window is not visible and avoid ParticleSystem::		// animating or redrawing it ...
	}
}
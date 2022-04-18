#include "Project7a.hpp"

#define ESCAPE		0x1b
#define LEFT		0x04
#define MIDDLE		0x02
#define RIGHT		0x01
//
// initialize the glui window:
//

void ParticleSystem::InitGlui()
{
	ShowPerformance = true;
	glutInitWindowPosition(INIT_WINDOW_SIZE + 50, 0);
	Glui = GLUI_Master.create_glui((char *) GLUITITLE);
	Glui->add_statictext((char *) GLUITITLE);
	Glui->add_separator();
	Glui->add_checkbox("Axes",             &AxesOn);
	Glui->add_checkbox("Perspective",      (int*)&WhichProjection);
	Glui->add_checkbox("Show Performance", &ShowPerformance);

	GLUI_Panel *panel = Glui->add_panel("Object Transformation");

		GLUI_Rotation *rot = Glui->add_rotation_to_panel(panel, "Rotation", (float *) RotMatrix);
		rot->set_spin(1.0);

		Glui->add_column_to_panel(panel, false);
		GLUI_Translation *scale = Glui->add_translation_to_panel(panel, "Scale",  GLUI_TRANSLATION_Y , &Scale2);
		scale->set_speed(0.01f);

		Glui->add_column_to_panel(panel, FALSE);
		GLUI_Translation *trans = Glui->add_translation_to_panel(panel, "Trans XY", GLUI_TRANSLATION_XY, &TransXYZ[0]);
		trans->set_speed(1.1f);

		Glui->add_column_to_panel(panel, FALSE);
		trans = Glui->add_translation_to_panel(panel, "Trans Z",  GLUI_TRANSLATION_Z , &TransXYZ[2]);
		trans->set_speed(1.1f);

		panel = Glui->add_panel("", FALSE);
		Glui->add_button_to_panel(panel, "Go !", GO, (GLUI_Update_CB) ParticleSystem::Buttons);
		Glui->add_column_to_panel(panel, FALSE);
		Glui->add_button_to_panel(panel, "Pause", PAUSE, (GLUI_Update_CB) ParticleSystem::Buttons);
		Glui->add_column_to_panel(panel, FALSE);
		Glui->add_button_to_panel(panel, "Reset", RESET, (GLUI_Update_CB) ParticleSystem::Buttons);
		Glui->add_column_to_panel(panel, FALSE);
		Glui->add_button_to_panel(panel, "Quit", QUIT, (GLUI_Update_CB) ParticleSystem::Buttons);

	Glui->set_main_gfx_window(MainWindow);
	GLUI_Master.set_glutIdleFunc(NULL);
}

//
// use glut to display a string of characters using a stroke font:
//

void ParticleSystem::DoStrokeString(float x, float y, float z, float ht, char *s)
{
	char c;			// one character to print

	glPushMatrix();
		glTranslatef((GLfloat)x, (GLfloat)y, (GLfloat)z);
		float sf = ht / (119.05f + 33.33f);
		glScalef((GLfloat)sf, (GLfloat)sf, (GLfloat)sf);
		for(; (c = *s) != '\0'; s++)
		{
			glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
		}
	glPopMatrix();
}

//
// glui buttons callback:
//

void ParticleSystem::Buttons(ButtonVals id)
{
	ParticleSystem * context = ParticleSystem::particleSystemSingleton;

	cl_int status;
	switch(id)
	{
		case GO:
			GLUI_Master.set_glutIdleFunc(ParticleSystem::Animate);
			break;

		case PAUSE:
			context->Paused = !context->Paused;
			if(context->Paused)
				GLUI_Master.set_glutIdleFunc(NULL);
			else
				GLUI_Master.set_glutIdleFunc(ParticleSystem::Animate);
			break;

		case RESET:
			context->Reset();
			context->ResetParticles();
			status = clEnqueueWriteBuffer(context->CmdQueue, context->CLParticleVelocity, CL_FALSE, 0, 4 * sizeof(float) * context->NUM_PARTICLES, context->GLParticleVelocity, 0, NULL, NULL);
			context->PrintCLError(status, "clEneueueWriteBuffer: ");
			GLUI_Master.set_glutIdleFunc(NULL);
			context->Glui->sync_live();
			glutSetWindow(context->MainWindow);
			glutPostRedisplay();
			break;

		case QUIT:
			context->Quit();
			break;

		default:
			printf("Don't know what to do with Button ID %d\n", id);
	}

}

//
// use glut to display a string of characters using a raster font:
//

void ParticleSystem::DoRasterString(float x, float y, float z, char *s)
{
	char c;			// one character to print

	glRasterPos3f((GLfloat)x, (GLfloat)y, (GLfloat)z);
	for(; (c = *s) != '\0'; s++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}
}

//
// the keyboard callback:
//

void ParticleSystem::Keyboard(unsigned char c, int x, int y)
{
	ParticleSystem * context = ParticleSystem::particleSystemSingleton;

	switch(c)
	{
		case 'o':
		case 'O':
			context->WhichProjection = ORTHO;
			break;

		case 'p':
		case 'P':
			context->WhichProjection = PERSP;
			break;

		case 'q':
		case 'Q':
		case ESCAPE:
			Buttons(QUIT);	// will not return here
			break;			// happy compiler

		default:
			printf("Don't know what to do with keyboard hit: '%c' (0x%0x)\n", c, c);
	}
	context->Glui->sync_live();
	glutSetWindow(context->MainWindow);
	glutPostRedisplay();
}

//
// called when the mouse button transitions down or up:
//

void ParticleSystem::MouseButton(int button, int state, int x, int y)
{
	ParticleSystem * context = ParticleSystem::particleSystemSingleton;

	int b;			// LEFT, MIDDLE, or RIGHT
	
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
			b = LEFT;		break;

		case GLUT_MIDDLE_BUTTON:
			b = MIDDLE;		break;

		case GLUT_RIGHT_BUTTON:
			b = RIGHT;		break;

		default:
			b = 0;
			printf("Unknown mouse button: %d\n", button);
	}


	// button down sets the bit, up clears the bit:

	if(state == GLUT_DOWN)
	{
		context->Xmouse = x;
		context->Ymouse = y;
		context->ActiveButton |= b;		// set the proper bit
	}
	else
	{
		context->ActiveButton &= ~b;		// clear the proper bit
	}
}

//
// called when the mouse moves while a button is down:
//

void ParticleSystem::MouseMotion(int x, int y)
{
	ParticleSystem * context = ParticleSystem::particleSystemSingleton;

	int dx = x - context->Xmouse;		// change in mouse coords
	int dy = y - context->Ymouse;

	if(context->ActiveButton & LEFT)
	{
		context->mouseTheta += (-context->ANGFACT*dx);
		context->mousePhi += (context->ANGFACT*dy);
	}


	if(context->ActiveButton & RIGHT)
	{
		context->eyeDistance += context->SCLFACT * (float)(dy);
		if (context->eyeDistance < 1)
		{
			context->eyeDistance = 1;
		}
	}

	context->Xmouse = x;			// new current position
	context->Ymouse = y;

	glutSetWindow(context->MainWindow);
	glutPostRedisplay();
}
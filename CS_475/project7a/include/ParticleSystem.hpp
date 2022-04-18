#ifndef PARTICLE_SYSTEM
#define PARTICLE_SYSTEM

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4996)
#endif

#ifdef WIN32
#include "glew.h"
#endif


#include <omp.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"
#include "glui.h"

#include "cl.h"
#include "cl_gl.h"

#include "OpenCL.hpp"
#include "dataTypes.hpp"

class ParticleSystem
{
public:
	static ParticleSystem * particleSystemSingleton;
	ParticleSystem();
    ~ParticleSystem();

private:
	// title of these windows:
	char *WINDOWTITLE;
	char *GLUITITLE;

	// random parameters:
	float XMIN;
	float XMAX;
	float YMIN;
	float YMAX;
	float ZMIN;
	float ZMAX;

	float VMIN;
	float VMAX;

	int NUM_PARTICLES;
	int LOCAL_SIZE;
	char *CL_FILE_NAME;
	char *CL_BINARY_NAME;

	int INIT_WINDOW_SIZE;

	float drawDistance;
	float ANGFACT;
	float SCLFACT;
	float MINSCALE;

	float4 BACKCOLOR;

	float3 AXES_COLOR;
	GLfloat AXES_WIDTH;

public:
	//
    // function prototypes:
    //

    inline
    float
    SQR( float x )
    {
        return x * x;
    }

	//////////////////////////////////////////////////
	//
	// Static openGL callbacks
	//
    static void Buttons( ButtonVals );
    static void Display( );
    static void Resize( int, int );
    static void Keyboard( unsigned char, int, int );
    static void MouseButton( int, int, int, int );
    static void MouseMotion( int, int );
	static void Visibility(int);
	static void Animate();

	//////////////////////////////////////////////////
	//
	// Static functions
	//
	static float Ranf(float, float);
	static float4 GetXYZfromPolar(float distanceFromOrigin, float theta, float phi);


	//////////////////////////////////////////////////
	//
	// Particle System Functions
	//

    void Axes( float );

    void DoRasterString( float, float, float, char * );
    void DoStrokeString( float, float, float, float, char * );
    void InitCL( );
    void InitGlui( );
    void InitGraphics( );
    void InitLists( );
    bool IsCLExtensionSupported( const char * );
    void PrintCLError( cl_int, char * = "", FILE * = stderr );
    void Quit( );
    void Reset( );
    void ResetParticles( );
    void Traces( int );
    void WriteFrame( );
    void Wait(cl_command_queue);

private:

    // non-constant global variables:
    int	ActiveButton;		// current button that is down
    GLuint	AxesList;		// list to hold the axes
    int	AxesOn;			// ON or OFF
    int	Frame;
    GLUI *	Glui;			// instance of glui window
    int	GluiWindow;		// the glut id for the glui window
    int	MainWindow;		// window id for main graphics window
    int	Paused;
    GLfloat	RotMatrix[4][4];	// set by glui rotation widget
    float	Scale, Scale2;		// scaling factors
    GLuint	SphereList;
    Projection	WhichProjection;	// ORTHO or PERSP
    int	Xmouse, Ymouse;		// mouse values
    float	mouseTheta, mousePhi;		// rotation angles in degrees
	float   eyeDistance;
    float	TransXYZ[3];		// set by glui translation widgets

    double	ElapsedTime;
    int		ShowPerformance;

    size_t GlobalWorkSize[3];
    size_t LocalWorkSize[3];

    float4 *	GLParticleVelocity;
    GLuint			GLParticlePosition;
    GLuint			GLParticleColor;

    cl_mem			CLParticlePosition;
    cl_mem			CLParticleColor;
    cl_mem			CLParticleVelocity;

    cl_command_queue	CmdQueue;
    cl_device_id		Device;
    cl_kernel		Kernel;
    cl_platform_id		Platform;
    cl_program		Program;
    cl_platform_id		PlatformID;
};

#endif // PARTICLE_SYSTEM
#include "Project7a.hpp"

struct errorcode
{
	cl_int		statusCode;
	char *		meaning;
}

ErrorCodes[] =
{
	{CL_SUCCESS,				""					},
	{CL_DEVICE_NOT_FOUND,			"Device Not Found"			},
	{CL_DEVICE_NOT_AVAILABLE,		"Device Not Available"			},
	{CL_COMPILER_NOT_AVAILABLE,		"Compiler Not Available"		},
	{CL_MEM_OBJECT_ALLOCATION_FAILURE,	"Memory Object Allocation Failure"	},
	{CL_OUT_OF_RESOURCES,			"Out of resources"			},
	{CL_OUT_OF_HOST_MEMORY,		"Out of Host Memory"			},
	{CL_PROFILING_INFO_NOT_AVAILABLE,	"Profiling Information Not Available"	},
	{CL_MEM_COPY_OVERLAP,			"Memory Copy Overlap"			},
	{CL_IMAGE_FORMAT_MISMATCH,		"Image Format Mismatch"			},
	{CL_IMAGE_FORMAT_NOT_SUPPORTED,	"Image Format Not Supported"		},
	{CL_BUILD_PROGRAM_FAILURE,		"Build Program Failure"			},
	{CL_MAP_FAILURE,			"Map Failure"				},
	{CL_INVALID_VALUE,			"Invalid Value"				},
	{CL_INVALID_DEVICE_TYPE,		"Invalid Device Type"			},
	{CL_INVALID_PLATFORM,			"Invalid Platform"			},
	{CL_INVALID_DEVICE,			"Invalid Device"			},
	{CL_INVALID_CONTEXT,			"Invalid Context"			},
	{CL_INVALID_QUEUE_PROPERTIES,		"Invalid Queue Properties"		},
	{CL_INVALID_COMMAND_QUEUE,		"Invalid Command Queue"			},
	{CL_INVALID_HOST_PTR,			"Invalid Host Pointer"			},
	{CL_INVALID_MEM_OBJECT,		"Invalid Memory Object"			},
	{CL_INVALID_IMAGE_FORMAT_DESCRIPTOR,	"Invalid Image Format Descriptor"	},
	{CL_INVALID_IMAGE_SIZE,		"Invalid Image Size"			},
	{CL_INVALID_SAMPLER,			"Invalid Sampler"			},
	{CL_INVALID_BINARY,			"Invalid Binary"			},
	{CL_INVALID_BUILD_OPTIONS,		"Invalid Build Options"			},
	{CL_INVALID_PROGRAM,			"Invalid Program"			},
	{CL_INVALID_PROGRAM_EXECUTABLE,	"Invalid Program Executable"		},
	{CL_INVALID_KERNEL_NAME,		"Invalid Kernel Name"			},
	{CL_INVALID_KERNEL_DEFINITION,		"Invalid Kernel Definition"		},
	{CL_INVALID_KERNEL,			"Invalid Kernel"			},
	{CL_INVALID_ARG_INDEX,			"Invalid Argument Index"		},
	{CL_INVALID_ARG_VALUE,			"Invalid Argument Value"		},
	{CL_INVALID_ARG_SIZE,			"Invalid Argument Size"			},
	{CL_INVALID_KERNEL_ARGS,		"Invalid Kernel Arguments"		},
	{CL_INVALID_WORK_DIMENSION,		"Invalid Work Dimension"		},
	{CL_INVALID_WORK_GROUP_SIZE,		"Invalid Work Group Size"		},
	{CL_INVALID_WORK_ITEM_SIZE,		"Invalid Work Item Size"		},
	{CL_INVALID_GLOBAL_OFFSET,		"Invalid Global Offset"			},
	{CL_INVALID_EVENT_WAIT_LIST,		"Invalid Event Wait List"		},
	{CL_INVALID_EVENT,			"Invalid Event"				},
	{CL_INVALID_OPERATION,			"Invalid Operation"			},
	{CL_INVALID_GL_OBJECT,			"Invalid GL Object"			},
	{CL_INVALID_BUFFER_SIZE,		"Invalid Buffer Size"			},
	{CL_INVALID_MIP_LEVEL,			"Invalid MIP Level"			},
	{CL_INVALID_GLOBAL_WORK_SIZE,		"Invalid Global Work Size"		},
};

//
// initialize the opencl stuff:
//
void ParticleSystem::InitCL()
{
	// see if we can even open the opencl Kernel Program
	// (no point going on if we can't):

	FILE *fp = fopen(CL_FILE_NAME, "rb");
	if(fp == NULL)
	{
		printf("Cannot open OpenCL source file '%s'\n", CL_FILE_NAME);
		return;
	}

	// 2. allocate the host memory buffers:

	cl_int status;		// returned status from opencl calls
				// test against CL_SUCCESS

	// get the platform id:

	cl_uint numPlatforms;
	status = clGetPlatformIDs(0, NULL, &numPlatforms);
	printf("Number of Platforms = %d\n", numPlatforms);
	cl_platform_id *platforms = new cl_platform_id[numPlatforms];
	status = clGetPlatformIDs(numPlatforms, platforms, NULL);
	PrintCLError(status, "clGetPlatformIDs: ");

	bool foundOne = false;
	for(int i = 0; i < (int)numPlatforms; i++)
	{
		Platform = platforms[i];
		// get the device id:
		status = clGetDeviceIDs(Platform, CL_DEVICE_TYPE_GPU, 1, &Device, NULL);
		if(status == CL_SUCCESS)
		{
			foundOne = true;
			printf("Using Platform %d\n", i);
			//break;
		}
	}

	if(! foundOne)
	{
		printf("Cannot find a device with a GPU!\n");
	}


	//status = clGetDeviceIDs(&platforms[2], CL_DEVICE_TYPE_GPU, 1, &Device, NULL);
	status = clGetDeviceIDs(Platform, CL_DEVICE_TYPE_GPU, 1, &Device, NULL);
	PrintCLError(status, "clGetDeviceIDs: ");


	// since this is an opengl interoperability program,
	// check if the opengl sharing extension is supported,
	// (no point going on if it isn't):
	// (we need the Device in order to ask, so can't do it any sooner than here)

	if( IsCLExtensionSupported("cl_khr_gl_sharing") )
	{
		printf("cl_khr_gl_sharing is supported.\n");
	}
	else
	{
		printf("cl_khr_gl_sharing is not supported -- sorry.\n");
		return;
	}



	// 3. create an opencl context based on the opengl context:

	cl_context_properties props[] =
	{
		CL_GL_CONTEXT_KHR,		(cl_context_properties) wglGetCurrentContext(),
		CL_WGL_HDC_KHR,			(cl_context_properties) wglGetCurrentDC(),
		CL_CONTEXT_PLATFORM,	(cl_context_properties) Platform,
		0
	};

	cl_context Context = clCreateContext(props, 1, &Device, NULL, NULL, &status);
	PrintCLError(status, "clCreateContext: ");

	// 4. create an opencl command queue:

	CmdQueue = clCreateCommandQueue(Context, Device, 0, &status);
	if(status != CL_SUCCESS)
		printf("clCreateCommandQueue failed\n");

	// create the velocity array and the opengl vertex array buffer and color array buffer:
	
	delete [] GLParticleVelocity;
	GLParticleVelocity = (float4 *)malloc(sizeof(float4) * NUM_PARTICLES);

	glGenBuffers(1, &GLParticlePosition);
	glBindBuffer(GL_ARRAY_BUFFER, GLParticlePosition);
	glBufferData(GL_ARRAY_BUFFER, 4 * NUM_PARTICLES * sizeof(float), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &GLParticleColor);
	glBindBuffer(GL_ARRAY_BUFFER, GLParticleColor);
	glBufferData(GL_ARRAY_BUFFER, 4 * NUM_PARTICLES * sizeof(float), NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);	// unbind the buffer

	// fill those arrays and buffers:

	ResetParticles();

	// 5. create the opencl version of the opengl buffers:

	CLParticlePosition = clCreateFromGLBuffer(Context, 0, GLParticlePosition, &status);
	PrintCLError(status, "clCreateFromGLBuffer (1)");

	CLParticleColor = clCreateFromGLBuffer(Context, 0, GLParticleColor, &status);
	PrintCLError(status, "clCreateFromGLBuffer (2)");

	// 5. create the opencl version of the velocity array:

	CLParticleVelocity = clCreateBuffer(Context, CL_MEM_READ_WRITE, 4*sizeof(float)*NUM_PARTICLES, NULL, &status);
	PrintCLError(status, "clCreateBuffer: ");
	 
	// 6. enqueue the command to write the data from the host buffers to the Device buffers:

	status = clEnqueueWriteBuffer(CmdQueue, CLParticleVelocity, CL_FALSE, 0, 4*sizeof(float)*NUM_PARTICLES, GLParticleVelocity, 0, NULL, NULL);
	PrintCLError(status, "clEneueueWriteBuffer: ");

	// 7. read the Kernel code from a file:

	fseek(fp, 0, SEEK_END);
	size_t fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *clProgramText = new char[fileSize+1];		// leave room for '\0'
	size_t n = fread(clProgramText, 1, fileSize, fp);
	clProgramText[fileSize] = '\0';
	fclose(fp);

	// create the text for the Kernel Program:

	char *strings[1];
	strings[0] = clProgramText;
	Program = clCreateProgramWithSource(Context, 1, (const char **)strings, NULL, &status);
	if(status != CL_SUCCESS)
		printf("clCreateProgramWithSource failed\n");
	delete [] clProgramText;

	// 8. compile and link the Kernel code:

	char *options = {""};
	status = clBuildProgram(Program, 1, &Device, options, NULL, NULL);
	if(status != CL_SUCCESS)
	{
		printf("clBuildProgram failed: %d\n", status);
		size_t size;
		clGetProgramBuildInfo(Program, Device, CL_PROGRAM_BUILD_LOG, 0, NULL, &size);
		cl_char *log = new cl_char[size];
		clGetProgramBuildInfo(Program, Device, CL_PROGRAM_BUILD_LOG, size, log, NULL);
		printf("clBuildProgram failed:\n%s\n", log);
		delete [] log;
	}

#define EXPORT_BINARY
#ifdef  EXPORT_BINARY
	size_t binary_sizes;
	status = clGetProgramInfo(Program, CL_PROGRAM_BINARY_SIZES, 0, NULL, &binary_sizes);
	PrintCLError(status, "clGetProgramInfo (1):");
	//printf("binary_sizes = %d\n", binary_sizes);
	size_t size;
	status = clGetProgramInfo(Program, CL_PROGRAM_BINARY_SIZES, sizeof(size_t), &size, NULL);
	PrintCLError(status, "clGetProgramInfo (2):");
	//printf("size = %d\n", size);
	unsigned char *binary = new unsigned char [size];
	status = clGetProgramInfo(Program, CL_PROGRAM_BINARIES, size, &binary, NULL);
	PrintCLError(status, "clGetProgramInfo (3):");
	FILE *fpbin = fopen(CL_BINARY_NAME, "wb");
	if(fpbin == NULL)
	{
		printf("Cannot create '%s'\n", CL_BINARY_NAME);
	}
	else
	{
		fwrite(binary, 1, size, fpbin);
		fclose(fpbin);
		printf("Binary written to '%s'\n", CL_BINARY_NAME);
	}
	delete [] binary;
#endif

	// 9. create the Kernel object:

	Kernel = clCreateKernel(Program, "Particle", &status);
	PrintCLError(status, "clCreateKernel failed: ");


	// 10. setup the arguments to the Kernel object:

	status = clSetKernelArg(Kernel, 0, sizeof(cl_mem), &CLParticlePosition);
	PrintCLError(status, "clSetKernelArg (1): ");

	status = clSetKernelArg(Kernel, 1, sizeof(cl_mem), &CLParticleVelocity);
	PrintCLError(status, "clSetKernelArg (2): ");

	status = clSetKernelArg(Kernel, 2, sizeof(cl_mem), &CLParticleColor);
	PrintCLError(status, "clSetKernelArg (3): ");
}


void ParticleSystem::Animate()
{
	ParticleSystem * context = ParticleSystem::particleSystemSingleton;
	cl_int  status;
	double time0, time1;

	// acquire the vertex buffers from opengl:

	glutSetWindow(context->MainWindow);
	glFinish();

	status = clEnqueueAcquireGLObjects(context->CmdQueue, 1, &context->CLParticlePosition, 0, NULL, NULL);
	context->PrintCLError(status, "clEnqueueAcquireGLObjects (1): ");
	status = clEnqueueAcquireGLObjects(context->CmdQueue, 1, &context->CLParticleColor, 0, NULL, NULL);
	context->PrintCLError(status, "clEnqueueAcquireGLObjects (2): ");
	context->Wait(context->CmdQueue);
	if(context->ShowPerformance)
		time0 = omp_get_wtime();

	// 11. enqueue the Kernel object for execution:

	cl_event wait;
	status = clEnqueueNDRangeKernel(context->CmdQueue, context->Kernel, 1, NULL, context->GlobalWorkSize, context->LocalWorkSize, 0, NULL, &wait);
	context->PrintCLError(status, "clEnqueueNDRangeKernel: ");
	if (context->ShowPerformance)
	{
		status = clWaitForEvents(1, &wait);
		context->PrintCLError(status, "clWaitForEvents: ");
		time1 = omp_get_wtime();
		context->ElapsedTime = time1 - time0;
	}

	context->Wait(context->CmdQueue);

	status = clEnqueueReleaseGLObjects(context->CmdQueue, 1, &context->CLParticleColor, 0, NULL, NULL);
	context->PrintCLError(status, "clEnqueueReleaseGLObjects (2): ");
	status = clEnqueueReleaseGLObjects(context->CmdQueue, 1, &context->CLParticlePosition, 0, NULL, NULL);
	context->PrintCLError(status, "clEnqueueReleaseGLObjects (2): ");
	context->Wait(context->CmdQueue);
	clFinish(context->CmdQueue);

	glutSetWindow(context->MainWindow);
	glutPostRedisplay();
	glFinish();
}

void ParticleSystem::PrintCLError(cl_int errorCode, char * prefix, FILE *fp)
{
	if(errorCode == CL_SUCCESS)
		return;
	
	const int numErrorCodes = sizeof(ErrorCodes) / sizeof(struct errorcode);
	char * meaning = "";
	for(int i = 0; i < numErrorCodes; i++)
	{
		if(errorCode == ErrorCodes[i].statusCode)
		{
			meaning = ErrorCodes[i].meaning;
			break;
		}
	}

	fprintf(fp, "%s %s\n", prefix, meaning);
}

// wait until all queued tasks have taken place:

void ParticleSystem::Wait(cl_command_queue  queue)
{
	cl_event wait;
	cl_int      status;

	status = clEnqueueMarker(queue, &wait);
	if (status != CL_SUCCESS)
		printf("Wait: clEnqueueMarker failed\n");

	status = clWaitForEvents(1, &wait);       // blocks until everything is done!
	if (status != CL_SUCCESS)
		printf("Wait: clWaitForEvents failed\n");
}

bool ParticleSystem::IsCLExtensionSupported(const char *extension)
{
	// see if the extension is bogus:

	if(extension == NULL  ||  extension[0] == '\0')
		return false;

	char * where = (char *) strchr(extension, ' ');
	if(where != NULL)
		return false;

	// get the full list of extensions:

	size_t extensionSize;
	clGetDeviceInfo(Device, CL_DEVICE_EXTENSIONS, 0, NULL, &extensionSize);
	char *extensions = new char [extensionSize];
	clGetDeviceInfo(Device, CL_DEVICE_EXTENSIONS, extensionSize, extensions, NULL);

	for(char * start = extensions; ;)
	{
		where = (char *) strstr((const char *) start, extension);
		if(where == 0)
		{
			delete [] extensions;
			return false;
		}

		char * terminator = where + strlen(extension);	// points to what should be the separator

		if(*terminator == ' '  ||  *terminator == '\0'  ||  *terminator == '\r'  ||  *terminator == '\n')
		{
			delete [] extensions;
			return true;
		}
		start = terminator;
	}

	delete [] extensions;
	return false;
}


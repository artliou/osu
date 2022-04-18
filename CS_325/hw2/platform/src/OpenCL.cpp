////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - CSV Logger
//
// Jeremy Prater
//

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "CL/cl.h"
#include "CL/cl_platform.h"

#include "OpenCL.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Open CL System Functions
//

OpenCL::OpenCL ()
{
    openCL_platform = NULL;
    openCL_device = NULL;
    openCL_context = NULL;
    openCL_cmdQueue = NULL;
	isInitialized = false;
}

OpenCL::~OpenCL ()
{
	if (isInitialized)
	{
		ReleaseOpenCL ();
	}
}

bool OpenCL::InitOpenCL ()
{
	cl_int status;

	status = clGetPlatformIDs (1, &openCL_platform, NULL);
	if (status != CL_SUCCESS)
	{
		fprintf (stderr, "clGetPlatformIDs failed (2)\n");
		exit(-1);
		return false;
	}
	
	status = clGetDeviceIDs (openCL_platform, CL_DEVICE_TYPE_GPU, 1, &openCL_device, NULL);
	if (status != CL_SUCCESS)
	{
		fprintf (stderr, "clGetDeviceIDs failed (2)\n");
		exit(-1);
		return false;
	}

	status = clGetDeviceInfo (openCL_device, CL_DEVICE_NAME, 256, deviceName, NULL);
	if (status != CL_SUCCESS)
	{
		fprintf (stderr, "clGetDeviceInfo failed\n");
		exit(-1);
		return false;
	}

	openCL_context = clCreateContext (NULL, 1, &openCL_device, NULL, NULL, &status);
	if (status != CL_SUCCESS)
	{
		fprintf (stderr, "clCreateContext failed\n");
		exit(-1);
		return false;
	}

	openCL_cmdQueue = clCreateCommandQueue (openCL_context, openCL_device, 0, &status);
	if (status != CL_SUCCESS)
	{
		fprintf (stderr, "clCreateCommandQueue failed\n");
		exit(-1);
		return false;
	}
	isInitialized = true;
	return true;
}

bool OpenCL::IsInitialized ()
{
	return isInitialized;
}

cl_command_queue OpenCL::GetCmdQueue ()
{
	return openCL_cmdQueue;
}

cl_context OpenCL::GetContext ()
{
	return openCL_context;
}

cl_device_id OpenCL::GetDevice ()
{
	return openCL_device;
}

cl_device_id * OpenCL::GetDeviceAddr ()
{
	return &openCL_device;
}

void OpenCL::ReleaseOpenCL ()
{
	clReleaseCommandQueue (openCL_cmdQueue);
	isInitialized = false;
}

void OpenCL::WaitForQueue ()
{
	cl_event wait;
	cl_int status;

	status = clEnqueueMarker (openCL_cmdQueue, &wait);
	if (status != CL_SUCCESS)
	{
		fprintf (stderr, "Wait: clEnqueueMarker failed\n");
	}

	status = clWaitForEvents (1, &wait);
	if (status != CL_SUCCESS)
	{
		fprintf (stderr, "Wait: clWaitForEvents failed (%d)\n", status);
	}
}

char * OpenCL::GetDeviceName()
{
	return deviceName;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Open CL Buffer Functions
//

OpenCLBuffer * OpenCLBuffer::CreateBuffer (OpenCL * parent, cl_mem_flags accessMode, size_t size)
{
	if (parent->IsInitialized ())
	{
		return new OpenCLBuffer (parent, accessMode, size);
	}
	else
	{
		exit(-1);
		return NULL;
	}
}

OpenCLBuffer::OpenCLBuffer (OpenCL * parent, cl_mem_flags accessMode, size_t size)
{
	openCL_parent = parent;
	bufferSize = size;
	cl_int status;
	buffer = clCreateBuffer (parent->GetContext (), accessMode, size, NULL, &status);
	if (status != CL_SUCCESS)
	{
		fprintf (stderr, "clCreateBuffer failed\n");
		exit(-1);
	}
}

bool OpenCLBuffer::CopyBufferFromHost (void * source)
{
	cl_int status = clEnqueueWriteBuffer (openCL_parent->GetCmdQueue(), buffer, CL_FALSE, 0, bufferSize, source, 0, NULL, NULL);
	if (status != CL_SUCCESS)
	{
		fprintf (stderr, "clEnqueueWriteBuffer failed\n");
		exit(-1);
		return false;
	}
	return true;
}

bool OpenCLBuffer::CopyBufferToHost (void * dest)
{
	cl_int status = clEnqueueReadBuffer(openCL_parent->GetCmdQueue(), buffer, CL_FALSE, 0, bufferSize, dest, 0, NULL, NULL );
	if( status != CL_SUCCESS )
	{
		fprintf (stderr, "clEnqueueReadBuffer failed (%d)\n", status);
		exit(-1);
		return false;
	}
	return true;
}

void OpenCLBuffer::ReleaseBuffer()
{
	clReleaseMemObject (buffer);
}

OpenCLBuffer::~OpenCLBuffer()
{
	ReleaseBuffer ();
}

cl_mem OpenCLBuffer::GetBuffer()
{
	return buffer;
}

cl_mem * OpenCLBuffer::GetBufferAddr()
{
	return &buffer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Open CL Program/Compilier Functions
//

OpenCLProgram * OpenCLProgram::CreateProgram (OpenCL * parent, const char * filename, const char * options)
{
	return new OpenCLProgram (parent, filename, options);
}

OpenCLProgram::OpenCLProgram (OpenCL * parent, const char * filename, const char * options)
{
	openCL_parent = parent;
	FILE *fp;
	fp = fopen (filename, "r");
	if (fp == NULL)
	{
		fprintf (stderr, "Cannot open OpenCL source file '%s'\n", filename);
		exit(-1);
		return;
	}

	fseek (fp, 0, SEEK_END);
	size_t fileSize = ftell (fp);
	fseek (fp, 0, SEEK_SET);
	char * clProgramText = (char*)malloc (fileSize+1);
	size_t n = fread (clProgramText, 1, fileSize, fp);
	clProgramText[fileSize] = '\0';
	fclose (fp);
	if (n != fileSize)
	{
		fprintf (stderr, "Expected to read %d bytes read from '%s' -- actually read %d.\n", fileSize, filename, n);
		exit(-1);
		return;
	}

	char *strings[1];
	strings[0] = clProgramText;
	cl_int status;
	program = clCreateProgramWithSource (parent->GetContext (), 1, (const char **)strings, NULL, &status);
	if (status != CL_SUCCESS)
	{
		fprintf (stderr, "clCreateProgramWithSource failed\n");
		exit(-1);
		return;
	}
	free (clProgramText);

	status = clBuildProgram (program, 1, parent->GetDeviceAddr (), options, NULL, NULL);
	if (status != CL_SUCCESS)
	{
		size_t size;
		clGetProgramBuildInfo (program, parent->GetDevice (), CL_PROGRAM_BUILD_LOG, 0, NULL, &size);
		cl_char *log = new cl_char[ size ];
		clGetProgramBuildInfo (program, parent->GetDevice (), CL_PROGRAM_BUILD_LOG, size, log, NULL);
		fprintf (stderr, "clBuildProgram failed:\n%s\n", log);
		delete [ ] log;
		exit(-1);
	}
}

OpenCLProgram::~OpenCLProgram ()
{
	ReleaseProgram ();
}

void OpenCLProgram::ReleaseProgram ()
{
	clReleaseProgram (program);
}

cl_program OpenCLProgram::GetProgram ()
{
	return program;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Open CL Kernel Functions
//

OpenCLKernel * OpenCLKernel::CreateKernel(OpenCL * parent, OpenCLProgram * program, const char * name)
{
	return new OpenCLKernel (parent, program, name);
}

OpenCLKernel::OpenCLKernel (OpenCL * parent, OpenCLProgram * program, const char * name)
{
	openCL_parent = parent;
	cl_int status;
	globalWorkSize[0] = globalWorkSize[1] = globalWorkSize[2] = 1;
	localWorkSize[0] = localWorkSize[1] = localWorkSize[2] = 1;

	kernel = clCreateKernel (program->GetProgram(), name, &status);
	if (status != CL_SUCCESS)
	{
		fprintf (stderr, "clCreateKernel failed\n");
		exit(-1);
	}
}

OpenCLKernel::~OpenCLKernel ()
{
	ReleaseKernel ();
}

void OpenCLKernel::SetArgument (cl_uint index, OpenCLBuffer * buffer)
{
	cl_int status;
	status = clSetKernelArg (kernel, index, sizeof (cl_mem), buffer->GetBufferAddr());
	if (status != CL_SUCCESS)
	{
		fprintf (stderr, "clSetKernelArg failed (%d) [%d]\n", index, status);
		exit(-1);
	}
}

void OpenCLKernel::SetArgumentLocal (cl_uint index, size_t size)
{
	cl_int status;
	status = clSetKernelArg (kernel, index, size, NULL);
	if (status != CL_SUCCESS)
	{
		fprintf (stderr, "clSetKernelArg failed (%d) [%d]\n", index, status);
		exit(-1);
	}
}

void OpenCLKernel::SetGlobalWorkSize (int dimension, size_t size)
{
	if ((dimension >= 0) && (dimension <= 2))
	{
		globalWorkSize[dimension] = size;
	}
}

void OpenCLKernel::SetLocalWorkSize (int dimension, size_t size)
{
	if ((dimension >= 0) && (dimension <= 2))
	{
		localWorkSize[dimension] = size;
	}
}

void OpenCLKernel::EnqueueWork ()
{
	cl_int status = clEnqueueNDRangeKernel (openCL_parent->GetCmdQueue (), kernel, 1, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
	if (!((status == CL_SUCCESS) || (status == CL_INVALID_WORK_ITEM_SIZE)))
	{
		fprintf (stderr, "clEnqueueNDRangeKernel failed: %d\n", status);
		exit(-1);
	}
}

void OpenCLKernel::ReleaseKernel ()
{
	clReleaseKernel (kernel);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - OpenCL wrapper class
//
// Jeremy Prater
//

#include <stdio.h>
#include <CL/cl.h>

class OpenCL;

class OpenCLBuffer
{
private:
    OpenCLBuffer(OpenCL * parent, cl_mem_flags accessMode, size_t size);

public:
    ~OpenCLBuffer();
    static OpenCLBuffer * CreateBuffer (OpenCL * parent, cl_mem_flags accessMode, size_t size);
    bool CopyBufferFromHost (void * source);
    bool CopyBufferToHost (void * dest);
    void ReleaseBuffer();
    cl_mem GetBuffer();
    cl_mem * GetBufferAddr();

private:
    OpenCL * openCL_parent;
    size_t bufferSize;
    cl_mem buffer;
};

class OpenCLProgram
{
private:
    OpenCLProgram (OpenCL * parent, const char * filename, const char * options);

public:
    ~OpenCLProgram();
    static OpenCLProgram * CreateProgram (OpenCL * parent, const char * filename, const char * options);
    void ReleaseProgram();
    cl_program GetProgram();

private:
    OpenCL * openCL_parent;
    cl_program program;
};

class OpenCLKernel
{
private:
    OpenCLKernel (OpenCL * parent, OpenCLProgram * program, const char * name);

public:
    ~OpenCLKernel();
    static OpenCLKernel * CreateKernel(OpenCL * parent, OpenCLProgram * program, const char * name);
    void ReleaseKernel();

    void SetArgument (cl_uint index, OpenCLBuffer * buffer);
    void SetArgumentLocal (cl_uint index, size_t size);
    void EnqueueWork ();

    void SetGlobalWorkSize (int dimension, size_t size);
    void SetLocalWorkSize (int dimension, size_t size);

private:
    OpenCL * openCL_parent;
    cl_kernel kernel;
    OpenCLProgram * program;
    const char * name;
	size_t globalWorkSize[3];
	size_t localWorkSize[3];
};

class OpenCL
{
public:
    OpenCL();
    ~OpenCL();

    bool InitOpenCL();
    void ReleaseOpenCL();
    void WaitForQueue();
    bool IsInitialized();

    cl_command_queue GetCmdQueue();
    cl_context GetContext();
    cl_device_id GetDevice();
    cl_device_id * GetDeviceAddr();

    OpenCLBuffer * CreateBuffer (cl_mem_flags accessMode, size_t size);

    char * GetDeviceName();

private:
	char deviceName[256];
    bool isInitialized;
    cl_platform_id openCL_platform;
    cl_device_id openCL_device;
    cl_context openCL_context;
    cl_command_queue openCL_cmdQueue;
};

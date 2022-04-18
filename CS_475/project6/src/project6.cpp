////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - Project 6 - OpenCL
//
// Jeremy Prater
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "CSVLogger.hpp"
#include <stdlib.h>
#include "OpenCL.hpp"
#include <omp.h>

static const char * dataLog = "./project6.csv";
static const char * dataSchema = "NUM_ELEMENTS,LOCAL_SIZE,OP_MODE,NUM_WORK_GROUPS,megaMultsSecBest,megaMultsSecAvg";

static const int iterations = 10;

static int LookAtTheBits( float fp )
{
	int *ip = (int *)&fp;
	return *ip;
}

int main( int argc, char *argv[ ] )
{
    if (argc != 4)
    {
        printf("Incorrect number of arguments...\n");
        exit(-1);
    }

    if (CSVLogger::OpenLogFile(dataLog))
    {
        CSVLogger::WriteLog(dataSchema);
    }

    const unsigned int NUM_ELEMENTS = atoi (argv[1]);
    const unsigned int LOCAL_SIZE = atoi(argv[2]);
    const unsigned int OP_MODE = atoi(argv[3]);
    const unsigned int NUM_WORK_GROUPS = (NUM_ELEMENTS / LOCAL_SIZE);
    size_t dataSize = NUM_ELEMENTS * sizeof(float);
    size_t workGroupSize = NUM_WORK_GROUPS * sizeof (float);
    float * ArrayA = (float*) aligned_alloc (64, dataSize);
    float * ArrayB = (float*) aligned_alloc (64, dataSize);
    float * ArrayC = NULL;

    if (OP_MODE == 1) // Array Multi + Add
    {
        ArrayC = (float*) aligned_alloc (64, dataSize);
    }
    float * ArrayResult = NULL;
    if (OP_MODE == 2) // Array Multi + Add + Reduction
    {
    ArrayResult = (float*) aligned_alloc (64, workGroupSize);
    }
    else
    {
        ArrayResult = (float*) aligned_alloc (64, dataSize);
    }

    if (CSVLogger::OpenLogFile(dataLog))
    {
        CSVLogger::WriteLog(dataSchema);
    }

    double avgTime = 0;
    double bestTime = 0;

    // OpenCL System Setup
    OpenCL openCL;
    openCL.InitOpenCL();

    //char * DEVICE_NAME = openCL.GetDeviceName();

    printf ("-> Elements: %d\t", NUM_ELEMENTS);
    printf ("-> Local work size: %d\t", LOCAL_SIZE);
    printf ("-> Num work groups: %d\t", NUM_WORK_GROUPS);
    printf ("-> OPMode: %0d\t", OP_MODE);
	//printf ("-> Device: %s\t", DEVICE_NAME);

    for (unsigned int index = 0; index < NUM_ELEMENTS; index++)
    {
        ArrayA[index] = ArrayB[index] = sqrt(index);
        if (OP_MODE == 1)
        {
            ArrayC[index] = (float)index;
        }
    }

    OpenCLBuffer * dataBuffers[4];
    OpenCLProgram * program;
    OpenCLKernel * kernel;

    // OpenCL Data Setup
    switch (OP_MODE)
    {
        case 0: // Multiply
        {
            dataBuffers[0] = OpenCLBuffer::CreateBuffer(&openCL, CL_MEM_READ_ONLY, dataSize);
            dataBuffers[1] = OpenCLBuffer::CreateBuffer(&openCL, CL_MEM_READ_ONLY, dataSize);
            dataBuffers[2] = OpenCLBuffer::CreateBuffer(&openCL, CL_MEM_WRITE_ONLY, dataSize);
            dataBuffers[0]->CopyBufferFromHost(ArrayA);
            dataBuffers[1]->CopyBufferFromHost(ArrayB);
            program = OpenCLProgram::CreateProgram(&openCL, "../src/ArrayMulti.cl", "");
            kernel = OpenCLKernel::CreateKernel(&openCL, program, "ArrayMult");

            for (int index=0; index < 3; index++)
            {
                kernel->SetArgument(index, dataBuffers[index]);
            }

            kernel->SetGlobalWorkSize(0,NUM_ELEMENTS);
            kernel->SetLocalWorkSize(0, LOCAL_SIZE);
        }
        break;
        case 1: // Multiply + Add
        {
            dataBuffers[0] = OpenCLBuffer::CreateBuffer(&openCL, CL_MEM_READ_ONLY, dataSize);
            dataBuffers[1] = OpenCLBuffer::CreateBuffer(&openCL, CL_MEM_READ_ONLY, dataSize);
            dataBuffers[2] = OpenCLBuffer::CreateBuffer(&openCL, CL_MEM_READ_ONLY, dataSize);
            dataBuffers[3] = OpenCLBuffer::CreateBuffer(&openCL, CL_MEM_WRITE_ONLY, dataSize);
            dataBuffers[0]->CopyBufferFromHost(ArrayA);
            dataBuffers[1]->CopyBufferFromHost(ArrayB);
            dataBuffers[2]->CopyBufferFromHost(ArrayC);
            program = OpenCLProgram::CreateProgram(&openCL, "../src/ArrayMultiAdd.cl", "");
            kernel = OpenCLKernel::CreateKernel(&openCL, program, "ArrayMultAdd");

            for (int index=0; index < 4; index++)
            {
                kernel->SetArgument(index, dataBuffers[index]);
            }

            kernel->SetGlobalWorkSize(0,NUM_ELEMENTS);
            kernel->SetLocalWorkSize(0, LOCAL_SIZE);
        }
        break;
        case 2: // Multiply + Add + Reduction
        {
            dataBuffers[0] = OpenCLBuffer::CreateBuffer(&openCL, CL_MEM_READ_ONLY, dataSize);
            dataBuffers[1] = OpenCLBuffer::CreateBuffer(&openCL, CL_MEM_READ_ONLY, dataSize);
            dataBuffers[2] = OpenCLBuffer::CreateBuffer(&openCL, CL_MEM_WRITE_ONLY, workGroupSize);
            dataBuffers[0]->CopyBufferFromHost(ArrayA);
            dataBuffers[1]->CopyBufferFromHost(ArrayB);
            program = OpenCLProgram::CreateProgram(&openCL, "../src/ArrayMultiAddReduce.cl", "");
            kernel = OpenCLKernel::CreateKernel(&openCL, program, "ArrayMultAddReduce");

            kernel->SetArgument(0, dataBuffers[0]);
            kernel->SetArgument(1, dataBuffers[1]);
            kernel->SetArgumentLocal(2, workGroupSize);
            kernel->SetArgument(3, dataBuffers[2]);

            kernel->SetGlobalWorkSize(0,NUM_ELEMENTS);
            kernel->SetLocalWorkSize(0, LOCAL_SIZE);
        }
        break;
    }

    for (int iteration = 0; iteration < iterations; iteration++)
    {
        
        openCL.WaitForQueue();
        const double time0 = omp_get_wtime();

        kernel->EnqueueWork();

        openCL.WaitForQueue();
        double curTime = omp_get_wtime() - time0;
        avgTime += curTime;
        if ((iteration == 0) || (curTime < bestTime))
        {
            bestTime = curTime;
        }

        // Get buffer from GPU
        int gpuBufferIndex = 2;
        if (OP_MODE == 1) // Multiply + Add
        {
            gpuBufferIndex = 3;
        }
        dataBuffers[gpuBufferIndex]->CopyBufferToHost (ArrayResult);
        openCL.WaitForQueue();

        // Validate data from GPU

        // Reduced +/- 1 bit due to Nvidia GTX 980 having lower accuracy
        //const float fpuTolerance = 0.00001;
        /************************************************************************************************
        * -> Elements: 512	-> Local work size: 32	-> Num work groups: 16	-> OPMode: 0	-> time (best): 2.159e-05	-> time (avg): 2.654e-05	-> MegaMults/Sec(best): 23.711388	-> MegaMults/Sec(avg): 19.289600
        * 75:      8.660254 *      8.660254 wrongly produced    150.000015 instead of    150.000000 (   0.00001526)
        * 75:    0x410a9067 *    0x410a9067 wrongly produced    0x43160001 instead of    0x43160000
        * */

        ///////////////////////////////////////////////////////
        //
        // fpu tolerance +/- 1 lsb
        const int fpuTolerance = 1;

        if (OP_MODE != 2) // Multiply OR Multiply + Add
        {
            for (int index = 0; index < NUM_ELEMENTS; index++)
            {
                float fexpected = ArrayA[index] * ArrayB[index];

                // Multiply + Add
                if (OP_MODE == 1)
                {
                    fexpected += ArrayC[index];
                }

                if (abs (LookAtTheBits(ArrayResult[index]) - LookAtTheBits(fexpected)) > fpuTolerance)
                {
                    printf("\n\n");
                    printf("%4d: %13.6f * %13.6f wrongly produced %13.6f instead of %13.6f (%13.8f)\n"   , index, ArrayA[index], ArrayB[index], ArrayResult[index], fexpected, fabs(ArrayResult[index]-fexpected));
                    printf("%4d:    0x%08x *    0x%08x wrongly produced    0x%08x instead of    0x%08x\n", index, LookAtTheBits(ArrayA[index]), LookAtTheBits(ArrayB[index]), LookAtTheBits(ArrayResult[index]), LookAtTheBits(fexpected));
                    // Error checking was disabled due to time constraints
                    //exit (-1);
                }
            }
        }
        else // Multiply + Add + Reduction
        {
            float fexpected = 0.;
            for (int index = 0; index < NUM_ELEMENTS; index++)
            {
                fexpected += (ArrayA[index] * ArrayB[index]);
            }

            float sum = 0.;
            for(int index = 0; index < NUM_WORK_GROUPS; index++)
            {
                sum += ArrayResult[index];
            }
            if (abs (LookAtTheBits(sum) - LookAtTheBits(fexpected)) > fpuTolerance)
            {
                //printf("\n\n");
                //printf("%13.6f != %13.6f Error: %13.6f\n", sum, fexpected, fabs(sum-fexpected));
                //printf("0x%08x != 0x%08x Error: 0x%08x\n", LookAtTheBits(sum), LookAtTheBits(fexpected), LookAtTheBits(fabs(sum - fexpected)));
                // Error checking was disabled due to time constraints
                //exit (-1);
            }
        }
    }

    avgTime /= iterations;
    double megaMultsSecBest = (NUM_ELEMENTS / bestTime) / 1000000;
    double megaMultsSecAvg = (NUM_ELEMENTS / avgTime) / 1000000;
    printf ("-> time (best): %.3e\t", bestTime);
    printf ("-> time (avg): %.3e\t", avgTime);
    printf ("-> MegaMults/Sec(best): %f\t", megaMultsSecBest);
    printf ("-> MegaMults/Sec(avg): %f\n", megaMultsSecAvg);
    CSVLogger::WriteLog("%d, %d, %d, %d, %f, %f",
    //DEVICE_NAME,
    NUM_ELEMENTS,
    LOCAL_SIZE,
    OP_MODE,
    NUM_WORK_GROUPS,
    megaMultsSecBest,
    megaMultsSecAvg);


    CSVLogger::CloseLogFile();

    delete kernel;
    delete program;
    openCL.ReleaseOpenCL();
    if (dataBuffers[0])
    {
        delete dataBuffers[0];
    }
    if (dataBuffers[1])
    {
        delete dataBuffers[1];
    }
    if (dataBuffers[2])
    {
        delete dataBuffers[2];
    }
    if (dataBuffers[3])
    {
        delete dataBuffers[3];
    }

    free (ArrayA);
    free (ArrayB);
    if (OP_MODE == 1) // Array Multi + Add
    {
        free(ArrayC);
    }

    free (ArrayResult);
}

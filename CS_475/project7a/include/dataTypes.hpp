#ifndef PROJECT_7A_DATA_TYPES
#define PROJECT_7A_DATA_TYPES

typedef struct
{
    float x;
    float y;
    float z;
    float w;
} float4;

typedef struct
{
	float x;
	float y;
	float z;
} float3;

typedef enum
{
	ORTHO,
	PERSP
} Projection;

typedef enum
{
	GO,
	PAUSE,
	RESET,
	QUIT
} ButtonVals;


#endif // PROJECT7A_DATA_TYPES
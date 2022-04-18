#include "nonSimd.h"


void
Mul( float *a, float *b,   float *c,   int len )
{
	int newLen = len;
	while (newLen >= 16)
	{
		int i = len - newLen;
		c[i+0] = a[i+0] * b[i+0];
		c[i+1] = a[i+1] * b[i+1];
		c[i+2] = a[i+2] * b[i+2];
		c[i+3] = a[i+3] * b[i+3];
		c[i+4] = a[i+4] * b[i+4];
		c[i+5] = a[i+5] * b[i+5];
		c[i+6] = a[i+6] * b[i+6];
		c[i+7] = a[i+7] * b[i+7];
		c[i+8] = a[i+8] * b[i+8];
		c[i+9] = a[i+9] * b[i+9];
		c[i+10] = a[i+10] * b[i+10];
		c[i+11] = a[i+11] * b[i+11];
		c[i+12] = a[i+12] * b[i+12];
		c[i+13] = a[i+13] * b[i+13];
		c[i+14] = a[i+14] * b[i+14];
		c[i+15] = a[i+15] * b[i+15];
		newLen -= 16;
	}
	for( int i = newLen; i > 0; i-- )
	{
		int index = len-i;
		c[index] += a[index] * b[index];
	}
}



float
MulSum( float *a, float *b, int len )
{
	int newLen = len;
	float sum = 0.;
	while (newLen >= 16)
	{
		int i = len - newLen;
		sum += a[i+0] * b[i+0];
		sum += a[i+1] * b[i+1];
		sum += a[i+2] * b[i+2];
		sum += a[i+3] * b[i+3];
		sum += a[i+4] * b[i+4];
		sum += a[i+5] * b[i+5];
		sum += a[i+6] * b[i+6];
		sum += a[i+7] * b[i+7];
		sum += a[i+8] * b[i+8];
		sum += a[i+9] * b[i+9];
		sum += a[i+10] * b[i+10];
		sum += a[i+11] * b[i+11];
		sum += a[i+12] * b[i+12];
		sum += a[i+13] * b[i+13];
		sum += a[i+14] * b[i+14];
		sum += a[i+15] * b[i+15];
		newLen -= 16;
	}
	for( int i = newLen; i > 0; i-- )
	{
		int index = len-i;
		sum += a[index] * b[index];
	}

	return sum;
}

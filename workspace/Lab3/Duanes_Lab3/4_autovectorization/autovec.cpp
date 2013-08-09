#include <stdio.h>

int main()
{	
	float A[10];
	float B[10] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f };
	float C[10] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f };
	#pragma loop(hint_parallel(4))
	for (int i=0; i<10; ++i)
	{
		A[i] = B[i] * C[i];
	}

	#pragma loop(hint_parallel(4))
	for (int i=0; i<10; ++i)
	{
		printf("\n[%d]=%f", i, A[i]);
	}

	return 0;
}
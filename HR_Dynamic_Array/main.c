#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int TestSize = 5;
	int *arraysize[2] = (int**) calloc(sizeof(int), TestSize * 2);

	if(!arraysize) {return 1;}

	arraysize[0][0] = 1;
	arraysize[1][1] = 2;

	printf("Arraysize: %p\n", arraysize);

	int x;
	for(x = 0; x < 5; x++)
	{
		x = x;
		//printf("Array[%d][0] = %d - Array[%d][1] = %d\n", x, arraysize[x][0], x, arraysize[x][1]);
	}
	
	free(arraysize);

	return 0;
}

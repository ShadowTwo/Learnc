#include <stdio.h>
#include <stdlib.h>

typedef struct Graph
{
	int x;
	int y;
	int z;
	char *map;
}

void Graph_Print(Graph graph, int z)
{
	//Check z is in bounds and graph is not null
	if(z < 1 || x < 1 || y < 1)
	{
		//Bounds must be greater then 0;
		return;
	}
	int x, y;
	for(y = 0; y < graph->y; y++)
	{
		for(x = 0; x < graph->x; x++)
		{
			printf("%c", map[z][y][x]);
		}
	}
}

Graph *Graph_Create(int x, int y, int z)
{
	
	if(z < 1 || x < 1 || y < 1)
	{
		//Bounds must be greater then 0;
		return 0;
	}

	Graph *NewGraph = calloc(sizeof(Graph),1);
	if(NewGraph)
	{
		NewGraph->x = x;
		NewGraph->y = y;
		NewGraph->z = z;

		int Graph_Points = sizeof(char) * x * y * z

		Graph_Points->map = calloc(Graph_Points,1);
		
		if(Graph_Points->map)
		{
			return Graph_Points;
		}
	}
	
	return 0;
}

int Graph_Destroy(Graph *graph)
{
	return 1;
}

int main(int argc, char *argv)
{
	printf("Hello World");

	return 1;
}

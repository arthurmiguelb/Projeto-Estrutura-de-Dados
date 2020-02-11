#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "graph.h"
#include "node.h"

int main()
{
	int edges, i, vertex1, vertex2, cost, heuristic, begin, end;
	printf("Type how many edges the graph will need >> ");
	scanf("%d", &edges);

	GRAPH *new_graph = create_graph();
	
	printf("Type your edges and the costs:\n");

	for (i = 0; i < edges; i++)
	{
		scanf("%d %d %d", &vertex1, &vertex2, &cost);
		new_graph->exist[vertex1] = 1;
		new_graph->exist[vertex2] = 1;
		add_edge(new_graph, vertex1, vertex2, cost);
	}
	printf("Type the begin and end >> ");
	scanf("%d %d", &begin, &end);

	printf("Type your heuristic value for every node:\n");
	for (i = 0; i < MAX; i++)
	{
		if (new_graph->exist[i])
		{	
			printf("%d >> ", i);
			if (i != end) 
			{
				scanf("%d", &heuristic);
				new_graph->heuristic[i] = heuristic;
			}
			else
			{
				printf("0\n");
				new_graph->heuristic[i] = 0;
			}
		}
	}

	printf("%d\n",Astar(new_graph, begin, end));

	
}

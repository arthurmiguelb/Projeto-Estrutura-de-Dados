#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "graph.h"
#include "node.h"
#include "queue.h"

GRAPH *create_graph()
{
	GRAPH *new_graph = (GRAPH *)malloc(sizeof(GRAPH));
	int i;
	for (i = 0; i < MAX; i++)
	{
		new_graph->visited[i] = 0;
		new_graph->elements[i] = NULL;
		new_graph->exist[i] = 0;
	}
	return new_graph;
}
void add_edge(GRAPH * graph, int vertex1, int vertex2, int cost)
{
	NODE *node_for_vertex2 = create_node(vertex2, cost);
	node_for_vertex2->next = graph->elements[vertex1];
	graph->elements[vertex1] = node_for_vertex2;
}

int Astar(GRAPH *graph, int begin, int end)
{
	QUEUE* priority_queue = create_queue();
	NODE* dequeued;
	NODE* adj_list;
	enqueue(priority_queue, begin, graph->heuristic[begin],NULL, 0);
	while(!is_empty(priority_queue))
	{
		dequeued = dequeue(priority_queue);
		if(dequeued->item == end)break;
		if(!graph->visited[dequeued->item])
		{
			graph->visited[dequeued->item]=1;
			adj_list = graph->elements[dequeued->item];
			while(adj_list != NULL)
			{
				adj_list->previous = dequeued;
				enqueue(priority_queue, adj_list->item, (calculate_distance(adj_list) + graph->heuristic[adj_list->item]), dequeued, adj_list->cost);
				adj_list=adj_list->next;
			}
		}
	}
	
	print_way(dequeued);
	printf("\n\n");
	return calculate_distance(dequeued);
}

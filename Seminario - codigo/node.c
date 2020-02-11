#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "node.h"

NODE *create_node(int vertex, int cost)
{
	NODE *new_node = (NODE *)malloc(sizeof(NODE));
	new_node->item = vertex;
	new_node->next = NULL;
	new_node->previous = NULL;
	new_node->cost = cost;
	new_node->fx=0;
	return new_node;
}

int calculate_distance(NODE* current)
{
	if(current->previous != NULL)return current->cost + calculate_distance(current->previous);
	return 0;
}

void print_way(NODE* current)
{
	if(current->previous != NULL)
	{
		print_way(current->previous);
		printf(" -> ");
	}
	printf("%d", current->item);
}
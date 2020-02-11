#define MAX 300
typedef struct NODE
{
	int item;
	int cost;
	int fx;
	struct NODE *next;
	struct NODE *previous;
}NODE;

typedef struct GRAPH
{
	NODE *elements[MAX];
	int exist[MAX];
	int visited[MAX];
	int heuristic[MAX];
}GRAPH;

typedef struct QUEUE
{
	NODE* head;
	int size;
}QUEUE;
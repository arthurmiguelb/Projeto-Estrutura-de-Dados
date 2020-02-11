GRAPH *create_graph();
void add_edge(GRAPH * graph, int vertex1, int vertex2, int cost);
int Astar(GRAPH *graph, int begin, int end);
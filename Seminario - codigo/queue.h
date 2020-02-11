QUEUE* create_queue();
void enqueue(QUEUE *pq, int i, int fx, NODE* previous, int cost);
NODE* dequeue(QUEUE *queue);
int is_empty(QUEUE* queue);
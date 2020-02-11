#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "queue.h"

QUEUE* create_queue()
{
  QUEUE* new_queue = (QUEUE*) malloc(sizeof(QUEUE));
  new_queue->head= NULL;
  new_queue->size= 0;
  return new_queue;
}

void enqueue(QUEUE *pq, int i, int fx, NODE* previous, int cost)
{
  NODE *new_node = (NODE*) malloc(sizeof(NODE));
  new_node->item = i;
  new_node->cost= cost;
  new_node->fx = fx;
  new_node->previous = previous;
  if ((is_empty(pq)) || (fx < pq->head->fx)) 
  {
    new_node->next = pq->head;
    pq->head = new_node;
  } 
  else 
  {
    NODE *current = pq->head;
    while ((current->next != NULL) && (current->next->fx < fx)) 
    {
      current = current->next;
    }
  new_node->next = current->next;
  current->next = new_node;
  }
  pq->size++;
}

NODE* dequeue(QUEUE *queue)
{
    NODE* dequeued = queue->head;
    queue->head = queue->head->next;
    queue->size--;
    dequeued->next = NULL;
    return dequeued;
}

int is_empty(QUEUE* queue)
{
  if(queue->size == 0)return 1;
  return 0;
}
#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>

typedef struct Node {
    void * data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} Queue;

Queue* createQueue();
void enqueue(Queue* queue, void * data);
void * dequeue(Queue* queue);

#endif

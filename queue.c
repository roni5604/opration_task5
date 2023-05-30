#include <stdlib.h>
#include "queue.h"

Queue* createQueue() {
    Queue* queue = malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    pthread_mutex_init(&queue->lock, NULL);
    pthread_cond_init(&queue->cond, NULL);
    return queue;
}

void enqueue(Queue* queue, void* data) {
    pthread_mutex_lock(&queue->lock);
    
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if(queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        pthread_cond_signal(&queue->cond);
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    pthread_mutex_unlock(&queue->lock);
}

void* dequeue(Queue* queue) {
    pthread_mutex_lock(&queue->lock);
    
    while(queue->front == NULL) {
        pthread_cond_wait(&queue->cond, &queue->lock);
    }

    Node* temp = queue->front;
    void * item = temp->data;

    queue->front = queue->front->next;

    if(queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);

    pthread_mutex_unlock(&queue->lock);
    
    return item;
}

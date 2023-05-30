#ifndef ACTIVEOBJECT_H
#define ACTIVEOBJECT_H

#include <pthread.h>
#include "queue.h"

typedef void (*TaskFunction)(void*);

typedef struct ActiveObject {
    Queue* queue;
    int stop;
    int isFirst;
    struct ActiveObject* next;
    TaskFunction task;
    pthread_t thread;
} ActiveObject;

ActiveObject* createActiveObject(TaskFunction task, ActiveObject *nextActiveObject);
Queue* getQueue(ActiveObject* ao);
void stopActiveObject(ActiveObject* ao);

#endif

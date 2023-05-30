#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "activeObject.h"

void *run(void *arg)
{
    ActiveObject *this = (ActiveObject *)arg;
    while (!this->stop)
    {
        if (this->isFirst)
        {
            void *data = dequeue(this->queue);
            if (data != (void *)-1)
            {
                this->task(data);
            }
        }
        else
        {
            int data = (int)dequeue(this->queue);
            if (data != -1)
            {
                if (data == -3)
                {
                    this->stop = 1;
                }
                else
                {
                    this->task(&data);
                }
                if (this->next != NULL)
                {
                    enqueue(this->next->queue, (void *)data);
                }
            }
        }
    }
    return NULL;
}

ActiveObject *createActiveObject(TaskFunction task, ActiveObject *nextActiveObject)
{
    ActiveObject *this = malloc(sizeof(ActiveObject));
    this->queue = createQueue();
    this->stop = 0;
    this->isFirst = 0;
    this->next = nextActiveObject;
    this->task = task;
    pthread_create(&this->thread, NULL, run, this);
    return this;
}

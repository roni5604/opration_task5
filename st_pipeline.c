#include <unistd.h>
#include "activeObject.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int is_prime(int num)
{
    for (int i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

void firstFunc(void *argv);
void secondFunc(void *data);
void thirdFunc(void *data);
void forthFunc(void *data);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s N [seed]\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    int seed = argc > 2 ? atoi(argv[2]) : time(NULL);
    void **array_to_first = (void **)malloc(sizeof(void *) * 3);
    if (array_to_first == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    ActiveObject *ao4 = createActiveObject(forthFunc, NULL);
    ActiveObject *ao3 = createActiveObject(thirdFunc, ao4);
    ActiveObject *ao2 = createActiveObject(secondFunc, ao3);
    ActiveObject *ao1 = createActiveObject(firstFunc, ao2);
    array_to_first[0] =(void*)(uintptr_t) N;
    array_to_first[1] = (void*)(uintptr_t) seed;
    array_to_first[2] = ao1;
    ao1->isFirst = 1;
    enqueue(ao1->queue, (void *)array_to_first);
    
    sleep(1);

    stopActiveObject(ao1);
    stopActiveObject(ao2);
    stopActiveObject(ao3);
    stopActiveObject(ao4);

    free(array_to_first);


    return 0;
}

void firstFunc(void *argv)
{
    void **array_to_first = (void **)argv;
    int N = (int)(uintptr_t)array_to_first[0];  // Casting void* to int
    int seed = (int)(uintptr_t)array_to_first[1];  // Casting void* to int
    ActiveObject *ao1 = (ActiveObject *)array_to_first[2];  // Casting void* to ActiveObject*
    srand(seed);// Setting seed for rand()
    for (size_t i = 0; i < N; i++)
    {
        int number = (rand()%999999)+100000;
        printf("First %d\n", number);
        enqueue(ao1->next->queue, (void *)(uintptr_t)number);
        usleep(1000);
    }
   
    enqueue(ao1->next->queue, (void *)-3);
    ao1->stop = 1;
}
void secondFunc(void *data)
{
    int *number = (int *)data;
    printf("Second- Function: %d, is prime: %s\n", *number, is_prime(*number) ? "true" : "false");
    // printf("%s\n",  is_prime(*number) ? "true" : "false");
    *number += 11;
}

void thirdFunc(void *data)
{
    int *number = (int *)data;
    printf("Third- Function: %d, is prime: %s\n", *number, is_prime(*number) ? "true" : "false");
    // printf("%d\n", *number);
    // printf("%s\n",is_prime(*number) ? "true" : "false");
    *number -= 13;
}
void forthFunc(void *data)
{
    int *number = (int *)data;
    // printf("%d\n", *number);
    // printf("%s\n",is_prime(*number) ? "true" : "false");

    printf("Forth- the given Number: %d\n", *number);
    *number += 2;
    printf("Forth- End Number: %d\n", *number);
    // printf("%d\n", *number);

}

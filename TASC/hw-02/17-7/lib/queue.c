/*
 * File: queue.c
 * -------------
 * This file implements the queue.h abstraction using an array.
 */

#include <stdio.h>

#include "genlib.h"
#include "queue.h"

/*
 * Constants:
 * ----------
 * MaxQueueSize -- Maximum number of elements in the queue
 */

#define MaxQueueSize 10

/*
 * Type: queueCDT
 * --------------
 * This type provides the concrete counterpart to the queueADT.
 * The representation used here consists of an array coupled
 * with two integers representing the head pointer and the tail
 * pointer of the array. The head pointer points to the first 
 * element in the array if there exists one, otherwise it will
 * points to where the elements should begin to be put. The 
 * tail pointer points to the place after the last element if 
 * there exists one. otherwise it will points to where the next
 * element will be put.
 */


struct queueCDT {
    void *array[MaxQueueSize + 1];
    int head, tail;
};

/* Exported entries */

/*
 * Function: NewQueue
 * ------------------
 * This function allocates and initializes the storage for a
 * new queue.
 */

queueADT NewQueue(void)
{
    queueADT queue;

    queue = New(queueADT);
    queue->head = 0;
    queue->tail = 0;
    return (queue);
}

/*
 * Function: FreeQueue
 * -------------------
 * This function frees the queue storage.
 */

void FreeQueue(queueADT queue)
{
    FreeBlock(queue);
}
int TrueIndex(int x)
{
    return x % MaxQueueSize;
}

/*
 * Function: Enqueue
 * -----------------
 * This function adds a new element to the queue.
 */

void Enqueue(queueADT queue, void *obj)
{
    if (TrueIndex(queue->tail + 1) == TrueIndex(queue->head)) {
        Error("Enqueue called on a full queue");
    }
    queue->array[(queue->tail)++] = obj;
}

/*
 * Function: QueueLength
 * ---------------------
 * This function returns the number of elements in the queue.
 */

int QueueLength(queueADT queue)
{
    return TrueIndex(queue->tail - queue->head + MaxQueueSize * 2);
}

/*
 * Function: Dequeue
 * -----------------
 * This function removes and returns the data value at the
 * head of the queue.
 */

void *Dequeue(queueADT queue)
{
    void *result;
    int i;

    if (QueueLength(queue) == 0) Error("Dequeue of empty queue");
    result = queue->array[(queue->head)++];
    
    return (result);
}


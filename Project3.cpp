Project3.cpp  →  Project 3/Project3.cpp
/**
 * NAME: Vidita Bhotika 
 * EID: vb9359
 * Spring 2025
 * Speight
 */

#include "UTQueue.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h> 
#include <stdlib.h>

/*
 * ALREADY DONE FOR YOU
 * Prints the passed in queue to make it easy to visualize.
 */
void utqueueprint(UTQueue *src) {
  printf("[");
  for (int i = 0; i < src->size - 1; i++)
    printf("%d, ", src->data[i]);
  printf("%d]\n", src->data[src->size - 1]);
}

/*
 * Allocate a UTQueue on the heap.
 * The size of the input array is n.
 * Initialize the queue correctly by copying src
 * Return a pointer to the newly created UTQueue.
 * 
 * Create a UTQueue on the heap that
holds a copy of source (which has n items) and sets the size. Return a pointer to the
UTQueue.
 */
UTQueue *utqueuedup(const int *src, int n) { 
  
  UTQueue* newUTQueue = (UTQueue*)malloc(sizeof(UTQueue));
  newUTQueue->data = (int*)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    newUTQueue->data[i] = src[i];
  }
  newUTQueue->size = n;

  return newUTQueue; 
}



/*
 * Free all memory associated with the given UTQueue.
 */
void utqueuefree(UTQueue *self) {
  free(self->data);
  free(self);
}

/*
 * Push (enqueue) an integer "value" into the queue.
 */
UTQueue *utqueuepush(UTQueue *src, int value) { 
  (src->size) += 1;
  src->data = (int*)realloc(src->data, (src->size) * sizeof(int));
  src->data[(src->size) - 1] = value;
  return src; 
}

/*
 * Pop (dequeue) an element from the queue
 * should fail an assertion if the queue is empty
 */
int utqueuepop(UTQueue *src) {
  assert(src->size != 0);  // change false to make this assertion fail only if src has 0 elements.
  int popped = src->data[0];
  int newSize = (src->size) - 1;

  UTQueue* newQueue = (UTQueue*)malloc(sizeof(UTQueue));
  newQueue->data = (int*)malloc(newSize*sizeof(int));

  for (int i = 0; i < newSize; i++) {
    newQueue->data[i] = src->data[i+1];
  }

  int* dataPointer = newQueue->data;

  src->size = newSize;
  free(src->data);
  src->data = dataPointer;
  free(newQueue);

  return popped;
}

/*
 * Reverses the queue in src.
 */
UTQueue *utqueuerev(UTQueue *src) { 
  int size = src->size;
  for (int i = 0; i < size/2; i++) {
    int temp = src->data[i];
    src->data[i] = src->data[size-1-i];
    src->data[size-1-i] = temp;
  }
  return src; 
}

/*
 * combines the elements of UTQueues dst and src INTO dst.
 * src should be deleted after the combination
 */
UTQueue *utqueuecombine(UTQueue *dst, UTQueue *src) { 
  int srcSize = src->size;
  int dstSize = dst->size;

  dst->size = srcSize + dstSize;
  dst->data = (int*)realloc(dst->data, (dst->size) * sizeof(int));
  for (int i = 0; i < srcSize; i++) {
    dst->data[i+dstSize] = src->data[i];
  }

  free(src->data);
  free(src);
  return dst; 
}

/*
 * Swap the two queues.
 * q1 should "have" the contents of q2 and vice verse.
 * There is more than one way to do this
 */
void utqueueswap(UTQueue *q1, UTQueue *q2) {
  int size1 = q1->size;
  int size2 = q2->size;

  int* tempData = q1->data;
  q1->data = q2->data;
  q2->data = tempData;

  q1->size = size2;
  q2->size = size1;

}

/*
 * Copy values from src array into dst.
 * Assume dst is a valid UTQueue.
 * src is an array of numbers.
 * Do not allocate any additional storage: only copy as many numbers
 * as will actually fit into the current UTQueue dst.
 * If all of src can fit into dst, leave the remaining ints in dst.
 * return the pointer to dst with the changes.
 */
UTQueue *utqueuecpy(UTQueue *dst, const int *src, int n) {
  if (n < dst->size) {
    for (int i = 0; i < n; i++) {
        dst->data[i] = src[i];
    }
  } else {
    for (int j = 0; j < dst->size; j++) {
      dst->data[j] = src[j];
    }
  }

  return dst;
}

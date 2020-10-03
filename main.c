/**
 * Sample program for testing the chaos queue.
 *
 * Author: Rick Coogle, PhD
 */
#include <stdio.h>
#include <stdint.h>
#include "chaos_queue.h"

#define QUEUE_SIZE 100

int main(int argc, char** argv)
{
    chaos_queue queue;
    int64_t int_data, i;
    
    chaos_queue_init(&queue);
    
    /* Add a bunch of data to the queue */
    for(i = 1; i < (QUEUE_SIZE+1); i++) {
        chaos_queue_enqueue(&queue, (void*)i);
    }
    
    /* Dequeue one piece */
    int_data = (int64_t)chaos_queue_dequeue(&queue);
    
    printf("fifo data = %ld\n", int_data);
    
    /* Dequeue random data until the queue is empty */
    while(chaos_queue_size(&queue) > 0) {
        int_data = (int64_t)chaos_queue_rand_dequeue(&queue);
        printf("firo data = %ld\n", int_data);
    }
    
    chaos_queue_destroy(&queue);
    
    return EXIT_SUCCESS;
}

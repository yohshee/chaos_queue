/**
 * chaos_queue.c - A FIRO (First in-random out) queue intended to model some managers' time management
 *   methodologies.  This is for fun, please don't actually use this for anything critical, except for
 *   instructional reasons.
 *
 * Author: Rick Coogle, PhD
 *
 */
 
#include <stdlib.h>

#include "chaos_queue.h"

/* Prototypes */
static queue_entry* alloc_entry(void);

/*
 * Private functions
 */
 
/* Allocates and initializes a new queue entry */
static
queue_entry* alloc_entry(void)
{
    queue_entry* entry;
    
    if((entry = malloc(sizeof(queue_entry))) != NULL) {
        entry->data = NULL;
        entry->prev = NULL;
        entry->next = NULL;
    }
    
    return entry;
}

/*
 * Public functions
 */

/* Initializes a queue */
void chaos_queue_init(chaos_queue* queue)
{
    if(queue != NULL) {
        queue->count = 0;
        queue->head = NULL;
        queue->tail = NULL;
    }
}

/* Clears out all contents of a queue */
void chaos_queue_destroy(chaos_queue* queue)
{
    queue_entry* walk;
    queue_entry* dead;
    
    /* Sanity check */
    if(queue == NULL)
        return;
    
    walk = queue->head;
    while(walk != NULL) {
        dead = walk;
        walk = walk->next;
        
        free(dead);
    }
    
    chaos_queue_init(queue);
}

/* Returns the size of the queue */
int chaos_queue_size(chaos_queue* queue)
{
    /* Sanity check */
    if(queue == NULL) {
        return 0;
    }
    else {
        return queue->count;
    }
}

/* Adds the data to the front of the queue */
int chaos_queue_enqueue(chaos_queue* queue, void* data)
{
    queue_entry* entry;
    
    /* Sanity check */
    if(queue == NULL)
        return 1;
    
    entry = alloc_entry();
    entry->data = data;
    
    if(queue->head == NULL) {
        /* Queue is empty! */
        queue->head = entry;
        queue->tail = entry;
        queue->count++;
    }
    else {
        /* It's a queue, so we add to the front */
        entry->next = queue->head;
        queue->head->prev = entry;
        queue->head = entry;
        
        queue->count++;
    }
    
    return 0;
}

/* Removes data from the end of the queue; i.e.,
   the standard queue operation. */
void* chaos_queue_dequeue(chaos_queue* queue)
{
    queue_entry* entry;
    void* data;
    
    /* Sanity check */
    if(queue == NULL)
        return NULL;
    
    data = NULL;
    
    if(queue->tail != NULL) {
        entry = queue->tail;
        queue->tail = queue->tail->prev;
        
        if(queue->tail != NULL) {
            queue->tail->next = NULL;
        }
        else {
            /* Queue is empty */
            queue->head = NULL;
        }
        
        queue->count--;
        data = entry->data;
        free(entry);
    }
    
    return data;
}

/* Removes data from a random point in the queue */
void* chaos_queue_rand_dequeue(chaos_queue* queue)
{
    queue_entry* entry;
    void* data;
    int index;
    
    /* Sanity check */
    if(queue == NULL)
        return NULL;
    
    if(queue->count == 0)
        return NULL;
    
    data = NULL;
    
    index = rand() % queue->count;
    
    if(index == (queue->count-1)) {
        /* Tail of the list, just dequeue as normal */
        data = chaos_queue_dequeue(queue);
    }
    else {
        if(index == 0) {
            /* This is the head */
            entry = queue->head;
            queue->head = queue->head->next;
            
            if(queue->head == NULL) {
                queue->tail = NULL;
            }
            else {
                queue->head->prev = NULL;    
            }
        }
        else {
            /* Remove from middle; move forward the number of elements */
            entry = queue->head;
            while(index > 0) {
                entry = entry->next;
                index--;
            }
            
            entry->prev->next = entry->next;
            entry->next->prev = entry->prev;
        }
        
        queue->count--;
        data = entry->data;
        free(entry);
    }
    
    return data;
}

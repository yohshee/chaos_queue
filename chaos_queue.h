/**
 * chaos_queue.h - A FIRO (First in-random out) queue intended to model some managers' time management
 *   methodologies.  This is for fun, please don't actually use this for anything critical, except for
 *   instructional reasons.
 *
 * This header contains type definitions and function prototypes.
 *
 * Author: Rick Coogle, PhD
 *
 */
 
#ifndef _CHAOS_QUEUE_H_INCLUDED
#define _CHAOS_QUEUE_H_INCLUDED

/* Basic doubly linked list typedefs */
typedef struct _queue_entry {
    void* data;                   /* Arbitrary data pointer */
    struct _queue_entry* prev;    /* Previous pointer; this is NULL if at head of list */
    struct _queue_entry* next;    /* Next pointer; this is NULL if at tail of list */
} queue_entry;

/* Definition of the queue */
typedef struct _chaos_queue {
    int count;                    /* Current size of queue */
    queue_entry* head;            /* Head pointer */
    queue_entry* tail;            /* Tail pointer */
} chaos_queue;

/* Function prototypes */
void chaos_queue_init(chaos_queue* queue);
void chaos_queue_destroy(chaos_queue* queue);
int chaos_queue_size(chaos_queue* queue);
int chaos_queue_enqueue(chaos_queue* queue, void* data);
void* chaos_queue_dequeue(chaos_queue* queue);
void* chaos_queue_rand_dequeue(chaos_queue* queue);




#endif /* _CHAOS_QUEUE_H_INCLUDED */
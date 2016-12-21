/* Queue implementation using linked list*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef QUEUE_H
#define QUEUE_H

struct q_node {
    char *qn_data;
    struct q_node *qn_next;
};

struct queue {
    size_t q_data_size;
    struct q_node *q_head;
    struct q_node *q_tail;
};

int queue_init(struct queue *q, size_t data_size);

int enqueue(struct queue *q, void *data);

int dequeue(struct queue *q, void *data);

int queue_free(struct queue *q);

#endif

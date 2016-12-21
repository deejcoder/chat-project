#include "./queue.h"

/*Frees the node pointed by qn */

void queue_node_free(struct q_node *qn) {
    free(qn->qn_data);
    qn->qn_data = NULL;
    free(qn);
    qn = NULL;
}

/*Initilize a queue q with data_size bytes for each element. Return 1 on success -1 on failure*/

int queue_init(struct queue *q, size_t data_size) {
    if(data_size <= 0) {
        //TODO: err
    }

    if(q == NULL) {
        //TODO:err
    }

    q->q_data_size = data_size;

    q->q_head = NULL;
    q->q_tail = NULL;
    return 1;
}

/* Insert data into queue q. Return 1 on sucess -1 on failure */

int enqueue(struct queue *q, void *data) {
    if(q == NULL || data == NULL) {
        //TODO: err
    }
    
    struct q_node *new_node = malloc(sizeof(struct q_node));
    if(!new_node){
        perror("enqueue");
        return -1;
    }

    new_node->qn_data = malloc(q->q_data_size);
    if(!(new_node->qn_data)){
        perror("enqueue");
        return -1;
    }
    
    memcpy(new_node->qn_data, data, q->q_data_size);
    new_node->qn_next = NULL;

    if(q->q_head == NULL){
        q->q_head = q->q_tail = new_node;
        return 1;
    }
    
    q->q_tail->qn_next = new_node;
    q->q_tail = new_node;
    return 1;
}

/* Dequeue into data from queue q. Return 1 on success -1 on failure */

int dequeue(struct queue *q, void *data) {
    if(q == NULL || data == NULL) {
        //TODO: err
    }

    if(q->q_head == NULL){
        //TODO:err empty queue
    }

    memcpy(data, q->q_head->qn_data, q->q_data_size);

    if(q->q_head == q->q_tail){
        q->q_head = q->q_tail = NULL;
        return 1;
    }
    
    struct q_node *tmp = q->q_head->qn_next;
    queue_node_free(q->q_head);
    
    q->q_head = tmp;
    return 1;
}

/*Frees all queue nodes and their data in queue q. Return 1 on success and -1 on failure*/

int queue_free(struct queue *q) {
    if(q == NULL) {
        //TODO:err
    }

    if(q->q_head == NULL) 
        return 1;
    
    struct q_node *curr_node = q->q_head;
    while(curr_node) {
        struct q_node *tmp = curr_node->qn_next;
        queue_node_free(curr_node);
        curr_node = tmp;
    }

    q->q_head = q->q_tail = NULL;
    q->q_data_size = 0;
    return 1;
}

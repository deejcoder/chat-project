/* Red-Black tree algorithem partially taken from CLRS 3rd edition*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef RB_TREE_H
#define RB_TREE_H

#define RBTN_BLACK  0
#define RBTN_RED    1

struct rbt_node {
    unsigned char rbtn_color;
    int rbtn_key;
    char *rbtn_data;
    struct rbt_node *rbtn_parent;
    struct rbt_node *rbtn_left;
    struct rbt_node *rbtn_right;    
};

struct rb_tree {
    unsigned int rbt_size;
    size_t rbt_data_size;
    struct rbt_node *rbt_root;
    struct rbt_node *rbt_null;
};


int rb_tree_init(struct rb_tree *t, size_t data_size);

int rb_tree_insert(struct rb_tree *t, int key, void *data);

int rb_tree_delete(struct rb_tree *t, int key);

int rb_tree_find(struct rb_tree *t, int key, void *data);

#endif

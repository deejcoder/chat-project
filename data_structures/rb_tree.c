#include "rb_tree.h"

/* rotations */

void rbt_left_rotate(struct rb_tree *t, struct rbt_node *n) {
    struct rbt_node *tmp = n->rbtn_right;

    n->rbtn_right = tmp->rbtn_left;
    
    if(tmp->rbtn_left != t->rbt_null) 
        tmp->rbtn_left->rbtn_parent = n;
    
    tmp->rbtn_parent = n->rbtn_parent;

    if(n->rbtn_parent == NULL)
        t->rbt_root = tmp;
    else if(n == n->rbtn_parent->rbtn_left)
        n->rbtn_parent->rbtn_left = tmp;
    else
        n->rbtn_parent->rbtn_right = tmp;

    tmp->rbtn_left = n;
    n->rbtn_parent = tmp;
}

void rbt_right_rotate(struct rb_tree *t, struct rbt_node *n) {
    struct rbt_node *tmp = n->rbtn_left;

    n->rbtn_left = tmp->rbtn_right;
    
    if(tmp->rbtn_right != t->rbt_null) 
        tmp->rbtn_right->rbtn_parent = n;
    
    tmp->rbtn_parent = n->rbtn_parent;

    if(n->rbtn_parent == NULL)
        t->rbt_root = tmp;
    else if(n == n->rbtn_parent->rbtn_right)
        n->rbtn_parent->rbtn_right = tmp;
    else
        n->rbtn_parent->rbtn_left = tmp;

    tmp->rbtn_right = n;
    n->rbtn_parent = tmp;
}


/*Change of colors + rotations */

void rbt_insert_fixup(struct rb_tree *t, struct rbt_node *n) {
    while(n->rbtn_parent->rbtn_color == RBTN_RED) {
        
        if(n->rbtn_parent == n->rbtn_parent->rbtn_parent->rbtn_left) {
            
            struct rbt_node *tmp = n->rbtn_parent->rbtn_parent->rbtn_right;
            if(tmp->rbtn_color == RBTN_RED) {
                
                n->rbtn_parent->rbtn_color = RBTN_BLACK;
                tmp->rbtn_color = RBTN_BLACK;
                n->rbtn_parent->rbtn_parent->rbtn_color = RBTN_RED;
                n = n->rbtn_parent->rbtn_parent;
            
            } else {
                if(n == n->rbtn_parent->rbtn_right) {    
                    n = n->rbtn_parent;
                    rbt_left_rotate(t, n);
                }
                n->rbtn_parent->rbtn_color = RBTN_BLACK;
                n->rbtn_parent->rbtn_parent->rbtn_color = RBTN_RED;
                rbt_right_rotate(t, n->rbtn_parent->rbtn_parent);
            }
        
        } else {

            struct rbt_node *tmp = n->rbtn_parent->rbtn_parent->rbtn_left;
            if(tmp->rbtn_color == RBTN_RED) {
                
                n->rbtn_parent->rbtn_color = RBTN_BLACK;
                tmp->rbtn_color = RBTN_BLACK;
                n->rbtn_parent->rbtn_parent->rbtn_color = RBTN_RED;
                n = n->rbtn_parent->rbtn_parent;
            
            } else {
                if(n == n->rbtn_parent->rbtn_left) {    
                    n = n->rbtn_parent;
                    rbt_right_rotate(t, n);
                }
                n->rbtn_parent->rbtn_color = RBTN_BLACK;
                n->rbtn_parent->rbtn_parent->rbtn_color = RBTN_RED;
                rbt_left_rotate(t, n->rbtn_parent->rbtn_parent);
            }
        } 
    }
    t->rbt_root->rbtn_color = RBTN_BLACK;
}

/*Puts new node in place as red */

void rbt_insert_node(struct rb_tree *t, struct rbt_node *n) {
    struct rbt_node *tmp = t->rbt_null;
    struct rbt_node *tmp2 = t->rbt_root;

    while(tmp2 != t->rbt_null) {
        tmp = tmp2;
        
        if(n->rbtn_key < tmp2->rbtn_key)
            tmp2 = tmp2->rbtn_left;
        else
            tmp2 = tmp2->rbtn_right;

        n->rbtn_parent = tmp;
        if(tmp == t->rbt_null)
            t->rbt_root = n;
        else if(n->rbtn_key < tmp->rbtn_key)
            tmp->rbtn_left = n;
        else
            tmp->rbtn_right = n;

        n->rbtn_left = t->rbt_null;
        n->rbtn_right = t->rbt_null;
        n->rbtn_color = RBTN_RED;
        
        rbt_insert_fixup(t, n);
    }
}

/* Find the node with key k */

struct rbt_node *rbt_find_node(struct rb_tree *t, int k) {
    
    struct rbt_node *curr_node = t->rbt_root;
    while(curr_node != t->rbt_null) {
        
        if(curr_node->rbtn_key == k)
            return curr_node;

        if(k < curr_node->rbtn_key) 
            curr_node = curr_node->rbtn_left;
        else
            curr_node = curr_node->rbtn_right;
    }
    return NULL;
}

/* Transplant */

void rbt_transplant(struct rb_tree *t, struct rbt_node *n1, struct rbt_node *n2) {

    if(n1->rbtn_parent == t->rbt_null)
        t->rbt_root = n2;
    else if(n1 == n1->rbtn_parent->rbtn_left)
        n1->rbtn_parent->rbtn_left = n2;
    else
        n1->rbtn_parent->rbtn_right = n2;
    
    n2->rbtn_parent = n1->rbtn_parent; 
}

/* Find the node with mininum key of tree rooted at n */

struct rbt_node *rbt_minimum(struct rb_tree *t, struct rbt_node *n) {
    
    struct rbt_node *curr_node = n;
    while(curr_node != t->rbt_null) {
        
        if(curr_node->rbtn_left == t->rbt_null)
            return curr_node;

        curr_node = curr_node->rbtn_left;
    }
    return n;
}

/* Change of colors + rotation */

void rbt_delete_fixup(struct rb_tree *t, struct rbt_node *n) {
    while(n != t->rbt_root && n->rbtn_color == RBTN_BLACK) {
        
        if(n == n->rbtn_parent->rbtn_left) {

            struct rbt_node *tmp = n->rbtn_parent->rbtn_right;
            if(tmp->rbtn_color == RBTN_RED) {
                
                tmp->rbtn_color = RBTN_BLACK;
                n->rbtn_parent->rbtn_color = RBTN_RED;
                rbt_left_rotate(t, n->rbtn_parent);
                tmp = n->rbtn_parent->rbtn_right;
            }

            if( tmp->rbtn_left->rbtn_color == RBTN_BLACK &&
                tmp->rbtn_right->rbtn_color == RBTN_BLACK) {

                tmp->rbtn_color = RBTN_RED;
                n = n->rbtn_parent;
            } else {

                if(tmp->rbtn_right->rbtn_color == RBTN_BLACK) {

                    tmp->rbtn_left->rbtn_color = RBTN_BLACK;
                    tmp->rbtn_color = RBTN_RED;
                    rbt_right_rotate(t, tmp);
                    tmp = n->rbtn_parent->rbtn_right;
                }

                tmp->rbtn_color = n->rbtn_parent->rbtn_color;
                n->rbtn_parent->rbtn_color = RBTN_BLACK;
                tmp->rbtn_right->rbtn_color = RBTN_BLACK;
                rbt_left_rotate(t, n->rbtn_parent);
                n = t->rbt_root;
            }
        } else {

            struct rbt_node *tmp = n->rbtn_parent->rbtn_left;
            if(tmp->rbtn_color == RBTN_RED) {
                
                tmp->rbtn_color = RBTN_BLACK;
                n->rbtn_parent->rbtn_color = RBTN_RED;
                rbt_right_rotate(t, n->rbtn_parent);
                tmp = n->rbtn_parent->rbtn_left;
            }

            if( tmp->rbtn_left->rbtn_color == RBTN_BLACK &&
                tmp->rbtn_right->rbtn_color == RBTN_BLACK) {

                tmp->rbtn_color = RBTN_RED;
                n = n->rbtn_parent;
            } else {

                if(tmp->rbtn_left->rbtn_color == RBTN_BLACK) {

                    tmp->rbtn_right->rbtn_color = RBTN_BLACK;
                    tmp->rbtn_color = RBTN_RED;
                    rbt_left_rotate(t, tmp);
                    tmp = n->rbtn_parent->rbtn_left;
                }

                tmp->rbtn_color = n->rbtn_parent->rbtn_color;
                n->rbtn_parent->rbtn_color = RBTN_BLACK;
                tmp->rbtn_left->rbtn_color = RBTN_BLACK;
                rbt_right_rotate(t, n->rbtn_parent);
                n = t->rbt_root;
            }
        }
    }
    n->rbtn_color = RBTN_BLACK;
}

/* Delete node n from tree t */

void rbt_delete_node(struct rb_tree *t, struct rbt_node *n) {
    
    struct rbt_node *tmp = n;
    struct rbt_node *tmp2;
    unsigned char tmp_color = tmp->rbtn_color;        

    if(n->rbtn_left == t->rbt_null) {
        tmp2 = n->rbtn_right;
        rbt_transplant(t, n, n->rbtn_right);
    } else if(n->rbtn_right == t->rbt_null) {
        tmp2 = n->rbtn_left;
        rbt_transplant(t, n, n->rbtn_left);
    } else {

        tmp = rbt_minimum(t, n->rbtn_right);
        tmp_color = tmp->rbtn_color;
        tmp2 = tmp->rbtn_right;

        if(tmp->rbtn_parent == n) {
            tmp2->rbtn_parent = tmp;
        } else {
            rbt_transplant(t, tmp, tmp->rbtn_right);
            tmp->rbtn_right = n->rbtn_right;
            tmp->rbtn_right->rbtn_parent = tmp;
        }

        rbt_transplant(t, n, tmp);
        tmp->rbtn_left = n->rbtn_left;
        tmp->rbtn_left->rbtn_parent = tmp;
        tmp->rbtn_color = n->rbtn_color;
    }

    if(tmp_color == RBTN_BLACK)
        rbt_delete_fixup(t, tmp2);
}

/* =======================================================================*/

/* Initialize a new red and black tree */

int rb_tree_init(struct rb_tree *t, size_t data_size) {
    if(data_size <= 0) {
        //TODO:err
    }

    if(t == NULL) {
        //TODO:err
    }

    t->rbt_null = (struct rbt_node *) calloc(1, sizeof(struct rbt_node));
    if(t->rbt_null == NULL) {
        perror("rb_tree_init");
        return -1;
    }

    t->rbt_null->rbtn_color = RBTN_BLACK;
    t->rbt_size = 0;
    t->rbt_data_size = data_size;
    t->rbt_root = t->rbt_null;
    return 1;
}

/*Insert a node with key k and content data into tree t */

int rb_tree_insert(struct rb_tree *t, int k, void *data) {
    if(t == NULL || data == NULL) {
        //TODO:err
    }

    struct rbt_node *new_node = (struct rbt_node *) malloc(sizeof(struct rbt_node));
    if(new_node == NULL) {
        perror("rb_tree_insert");
        return -1;
    }

    new_node->rbtn_key = k;
    new_node->rbtn_data = malloc(t->rbt_data_size);
    if(new_node->rbtn_data == NULL) {
        perror("rb_tree_insert");
        return -1;
    }    

    memcpy(new_node->rbtn_data, data, t->rbt_data_size);
    rbt_insert_node(t, new_node); 
    t->rbt_size++;
    return 1;
}

/*Find node with key k and copies content to data in tree t. If data is null no content is copied */

int rb_tree_find(struct rb_tree *t, int k, void *data) {
    if(t == NULL) {
        //TODO:err
    }

    if(t->rbt_size == 0 || t->rbt_root == t->rbt_null) {
        //TODO:err
    }
    
    struct rbt_node *tmp = rbt_find_node(t, k);
    if(tmp == NULL) {
        //TODO: err not found
    }
    
    if(data != NULL)
        memcpy(data, tmp->rbtn_data, t->rbt_data_size);
    
    return 1;
}

/*Delete a node with key k from tree t */

int rb_tree_delete(struct rb_tree *t, int k) {
    if(t == NULL) {
        //TODO:err
    }

    if(t->rbt_size == 0 || t->rbt_root == t->rbt_null) {
        //TODO:err tree empty
    }
    
    struct rbt_node *tmp = rbt_find_node(t, k);
    if(tmp == NULL) {
        //TODO:err not found
    }
    
    rbt_delete_node(t, tmp);
    t->rbt_size--;
    return 1;
}

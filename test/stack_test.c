#include "../data_structures/stack.h"

#include <stdlib.h>
#include <stdio.h>

int init_without_count() {
    struct stack s;
    if(stack_init(&s, sizeof(int), 0) < 0) {
        fprtinf(stderr, "ERROR: stack_init");
        return 0;
    }

    if(s.s_data_size != sizeof(int)) {
        fprintf(stderr, "ERROR: s_data_size mismatch\tDumping struct:\n");
        memdump(&s, sizeof(struct stack), MEMD_DISPLAY_OFF);
        return 0;
    }

    if(s.s_size != 2) {
        fprintf(stderr, "ERROR: s_size mismatch\tDumping struct:\n");
        memdump(&s, sizeof(struct stack), MEMD_DISPLAY_OFF);
        return 0;
    }

    for(int i = 0; i < sizeof(int) * 2; i++) {
        if(s.s_arr[i] != 0) {
            
            fprintf(stderr, "ERROR: s_arr content corrupt\tDumping buffer:\n");
            memdump(s.s_arr, sizeof(int) * 2, MEMD_DISPLAY_OFF);
            return 0;
        }
    } 

    if(s.s_top != s.s_arr) {
        
        fprintf(stderr, "ERROR: s_top does not reference to s_arr\tDumping struct:\n");
        memdump(&s, sizeof(struct stack), MEMD_DISPLAY_OFF);
        return 0;
    }

    return 1;
}

int init_with_count() {
    struct stack s;
    if(stack_init(&s, sizeof(int), 64) < 0) {
        fprtinf(stderr, "ERROR: stack_init");
        return 0;
    }

    if(s.s_data_size != sizeof(int)) {
        fprintf(stderr, "ERROR: s_data_size mismatch\tDumping struct:\n");
        memdump(&s, sizeof(struct stack), MEMD_DISPLAY_OFF);
        return 0;
    }

    if(s.s_size != 64) {
        fprintf(stderr, "ERROR: s_size mismatch\tDumping struct:\n");
        memdump(&s, sizeof(struct stack), MEMD_DISPLAY_OFF);
        return 0;
    }

    for(int i = 0; i < sizeof(int) * 64; i++) {
        if(s.s_arr[i] != 0) {
            
            fprintf(stderr, "ERROR: s_arr content corrupt\tDumping buffer:\n");
            memdump(s.s_arr, sizeof(int) * 64, MEMD_DISPLAY_OFF);
            return 0;
        }
    } 

    if(s.s_top != s.s_arr) {
        
        fprintf(stderr, "ERROR: s_top does not reference to s_arr\tDumping struct:\n");
        memdump(&s, sizeof(struct stack), MEMD_DISPLAY_OFF);
        return 0;
    }

    return 1;
}

int push_one() {
    struct stack s;
    if(!stack_init(&s, sizeof(double), 0)) {
        fprtinf(stderr, "ERROR: stack_init\n");
        return 0;
    }



    
    return 1;
}

int push_three() {
    struct stack s;
    if(!stack_init(&s, sizeof(double), 0)) {
        fprtinf(stderr, "ERROR: stack_init\n");
        return 0;
    }

    return 1;
}

int pop_one() {
    struct stack s;
    if(!stack_init(&s, sizeof(double), 0)) {
        fprtinf(stderr, "ERROR: stack_init\n");
        return 0;
    }
}

int pop_three() {
    struct stack s;
    if(!stack_init(&s, sizeof(double), 0)) {
        fprtinf(stderr, "ERROR: stack_init\n");
        return 0;
    }
}

int (*tests[])(void) = {    push_one,
                            push_three};

char **test_names = {   "push_one",
                        "push_three"};


int main() {

}

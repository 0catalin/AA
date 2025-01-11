#ifndef BACKTRACKING_H
#define BACKTRACKING_H

typedef struct node {
    // Value to include
    unsigned int value;
    unsigned int sum_so_far;
    struct node *include;
    struct node *exclude;
    struct node *parent;
} Node, *Tree;



#endif
//
// Created by veljk on 12/14/2021.
//
#ifndef UNTITLED_PHEAP_H
#define UNTITLED_PHEAP_H
//TYPES USED IN HEAP
#define true 1
#define false 0
#define MAX_HEAP_SIZE 64
#define MAX_NODES_PER_HEAP 64
typedef unsigned char bool;
typedef unsigned int VAL;
typedef unsigned char PROC_POINTER;
//STRUCTURE USED IN PAIRED HEAP IMPLEMENTATION
struct NODE {
    struct NODE *left;
    struct NODE *right;
    struct NODE *prev;
    void *data;
    bool ISUSED;
    unsigned char allocated_at;
};
typedef struct NODE NODE;
//HEAP STRUCTURE
struct HEAP {
    NODE nodes[MAX_NODES_PER_HEAP];
    unsigned char size;
    unsigned char allocate_node;
    unsigned char free_node;
    NODE *root;

    bool (*cmp)(NODE *nodeA, NODE *nodeB);

    unsigned char freemem[MAX_NODES_PER_HEAP];
};
typedef struct HEAP HEAP;
//GLOBAL VARIABLES
extern HEAP heaps[MAX_HEAP_SIZE];
extern unsigned char free_heap;
extern unsigned char number_of_heaps;
//CREATES HEAP
void create_heap(HEAP *heap);
//FUNCTION USED FOR MERGING TWO SUBTREES
static inline NODE *merge(NODE *subA, NODE *subB, bool (*cmp)(NODE *nodeA, NODE *nodeB)) {
    if (cmp(subA, subB)) {
        if (subA->left) {
            subA->left->prev = subB;
        }
        if (subB->right) {
            subB->right->prev = subA;
        }
        subA->right = subB->right;
        subB->right = subA->left;
        subA->left = subB;
        subB->prev = subA;
        return subA;
    }
    if (subB->left) {
        subB->left->prev = subA;
    }
    if (subA->prev && subA->prev->left != subA) {
        subA->prev->right = subB;
    }
    subB->prev = subA->prev;
    subA->prev = subB;
    subA->right = subB->left;
    subB->left = subA;
    return subB;
}
//FUNCTION USED FOR INSERTING A NODE INTO A HEAP
void insert(HEAP *heap, void *data);
//MERGE RIGHT LEFT
static inline NODE *lmerge(HEAP *heap, NODE *node) {
    NODE *sub = node->prev;
    while (sub) {
        node = merge(sub, node, heap->cmp);
        sub = node->prev;
    }
    return node;
}
//MERGE LEFT RIGHT
static inline NODE *rmerge(HEAP *heap, NODE *node) {
    NODE *sub = 0;
    while (node) {
        if (!(sub = node->right)) {
            return node;
        }
        sub = merge(node, sub, heap->cmp);
        node = sub->right;
    }
    return sub;
}
//MERGE TWO HEAPS
static inline NODE *mergetwo(HEAP *heap, NODE *subA) {
    subA->left->prev = 0;
    NODE *sub;
    sub = rmerge(heap, subA->left);
    sub = lmerge(heap, sub);
    return sub;
}
//POP MIN
void *pop(HEAP *heap);
#endif //UNTITLED_PHEAP_H
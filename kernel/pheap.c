//
// Created by veljk on 12/14/2021.
//
#include "pheap.h"
//GLOBAL VARIABLES
HEAP heaps[MAX_HEAP_SIZE];
unsigned char free_heap = 0;
unsigned char number_of_heaps = 0;
//CREATES HEAP
void
create_heap(HEAP* heap) {
    for(int i = 0;i<MAX_NODES_PER_HEAP;i++){
        heap->freemem[i] = i;
    }
    heap->free_node = 0;
    heap->allocate_node = 0;
}
//INSERTS NODE INTO A HEAP; USES MERGE TO MERGE NEW NODE WITH EXISTING HEAP
void
insert(HEAP *heap, void *data) {
    heap->size++;
    NODE* node = &heap->nodes[heap->freemem[heap->allocate_node]];
    node->allocated_at = heap->freemem[heap->allocate_node];
    heap->allocate_node = (heap->allocate_node+1)%MAX_NODES_PER_HEAP;
    node->right = 0;
    node->prev = 0;
    node->left = 0;
    node->data = data;
    node->ISUSED = true;
    if (!heap->root) {
        heap->root = node;
    } else {
        heap->root = merge(node, heap->root,heap->cmp);
    }
}
//POPS ELEMENT FROM HEAP DEPENDING ON FUNCTION USED
void *
pop(HEAP *heap) {
    if (heap->size == 0)return 0;
    NODE *node = heap->root;
    heap->freemem[heap->free_node] = node->allocated_at;
    heap->free_node = (heap->free_node+1)%MAX_NODES_PER_HEAP;
    heap->size--;
    if (!node->left) {
        heap->root = 0;
        return node->data;
    }
    node->ISUSED = false;
    heap->root = mergetwo(heap,node);
    return node->data;
}
//PEEK MIN
void*
peek(HEAP *heap){
    return heap->root;
}
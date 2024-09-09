#ifndef DS_HEAP_H
#define DS_HEAP_H

typedef struct heap_node
{
    int key;
} heap_node;

typedef struct heap_tree
{
    heap_node* nodes;
    int size;
    int(*predicate)(int, int);
} heap_tree;

heap_tree* min_heap_new();
heap_tree* max_heap_new();
void heap_insert(heap_tree* tree, int key);
void heap_delete(heap_tree* tree, heap_node* del);
heap_node heap_pop(heap_tree* tree);
int heap_validate(heap_tree* tree);

#endif
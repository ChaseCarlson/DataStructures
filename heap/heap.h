#ifndef DS_HEAP_H
#define DS_HEAP_H

typedef struct heap_node {
    int data;
} heap_node;

typedef struct heap_tree {
    heap_node* nodes;
    int nodesSize;
    int size;
    int(*predicate)(int, int);
} heap_tree;

heap_tree* min_heap_new();
heap_tree* max_heap_new();
void heap_insert(heap_tree* tree, int val);
void heap_delete(heap_tree* tree, int idx);
int heap_pop(heap_tree* tree);
int heap_parent_index(int idx);
int heap_left_child_index(int idx);
int heap_right_child_index(int idx);
int min_heap_predicate(int parent, int child);
int max_heap_predicate(int parent, int child);
int heap_check_property(heap_tree* tree);

#endif
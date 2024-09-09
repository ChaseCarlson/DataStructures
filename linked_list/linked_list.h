#ifndef DS_LINKED_LIST_H
#define DS_LINKED_LIST_H

typedef struct list_node {
    struct list_node* prev;
    struct list_node* next;
    int data;
} list_node;

list_node* list_node_new(int data);
list_node* list_node_insert_after(list_node* node, int data);
list_node* list_node_insert_before(list_node* node, int data);
void list_node_delete(list_node* node);
list_node* list_node_get_root(list_node* node);
list_node* list_node_get_tail(list_node* node);
list_node* list_push_back(list_node* node, int data);
list_node* list_push_front(list_node* node, int data);
int list_pop_back(list_node* node);
int list_pop_front(list_node* node);
list_node* list_find(list_node* node, int data);
list_node* list_node_at(list_node* node, int index);
int list_size(list_node* node);

#endif
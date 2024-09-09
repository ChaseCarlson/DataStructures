#include "linked_list.h"

#include <stdlib.h>

list_node *list_node_new(int data)
{
    list_node* node = malloc(sizeof(list_node));
    node->prev = NULL;
    node->next = NULL;
    node->data = data;

    return node;
}

list_node *list_node_insert_after(list_node *node, int data)
{
    list_node* ins = list_node_new(data);
    
    ins->prev = node;
    ins->next = node->next;

    if (node->next)
    {
        node->next->prev = ins;
    }
    node->next = ins;

    return ins;
}

list_node* list_node_insert_before(list_node* node, int data)
{
    list_node* ins = list_node_new(data);

    ins->prev = node->prev;
    ins->next = node;

    if (node->prev)
    {
        node->prev->next = ins;
    }
    node->prev = ins;

    return ins;
}

void list_node_delete(list_node *node)
{
    if (node->prev)
    {
        node->prev->next = node->next;
    }
    if (node->next)
    {
        node->next->prev = node->prev;
    }

    node->data = 0;
    node->prev = NULL;
    node->next = NULL;
    free(node);
}

list_node *list_node_get_root(list_node *node)
{
    if (node->prev == NULL)
    {
        return node;
    }

    return list_node_get_root(node->prev);
}

list_node *list_node_get_tail(list_node *node)
{
    if (node->next == NULL)
    {
        return node;
    }

    return list_node_get_tail(node->next);
}

list_node *list_push_back(list_node *node, int data)
{
    return list_node_insert_after(list_node_get_tail(node), data);
}

list_node *list_push_front(list_node *node, int data)
{
    return list_node_insert_before(list_node_get_root(node), data);
}

int list_pop_back(list_node *node)
{
    list_node* tail = list_node_get_tail(node);
    int tail_data = tail->data;
    list_node_delete(tail);
    return tail_data;
}

int list_pop_front(list_node *node)
{
    list_node* root = list_node_get_root(node);
    int root_data = root->data;
    list_node_delete(root);
    return root_data;
}

list_node* _list_find_recurse(list_node* root, int data) /* assumes root start */
{
    if (root->data == data)
    {
        return root;
    }

    if (root->next == NULL)
    {
        return NULL;
    }

    return _list_find_recurse(root->next, data);
}

list_node *list_find(list_node *node, int data)
{
    return _list_find_recurse(list_node_get_root(node), data);
}

list_node* _list_node_at_recurse(list_node* root, int atIndex, int currentIndex)
{
    if (currentIndex == atIndex)
    {
        return root;
    }

    if (root->next == NULL)
    {
        return NULL;
    }

    return _list_node_at_recurse(root->next, atIndex, currentIndex+1);
}

list_node *list_node_at(list_node *node, int index)
{
    return _list_node_at_recurse(list_node_get_root(node), index, 0);
}

int _list_size_recurse(list_node* root, int size)
{
    if (root->next == NULL)
    {
        return size;
    }

    return _list_size_recurse(root->next, size+1);
}

int list_size(list_node *node)
{
    _list_size_recurse(list_node_get_root(node), 1);
}

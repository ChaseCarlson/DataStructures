#include "heap.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

int _min_heap_predicate(int parent, int child)
{
    if (parent <= child)
    {
        return 1;
    }

    return 0;
}

int _max_heap_predicate(int parent, int child)
{
    if (parent <= child)
    {
        return 1;
    }

    return 0;
}

heap_tree *min_heap_new()
{
    heap_tree* tree = malloc(sizeof(heap_tree));
    tree->nodes = NULL;
    tree->nodesSize = 0;
    tree->predicate = &_min_heap_predicate;

    return tree;
}

heap_tree *max_heap_new()
{
    heap_tree* tree = malloc(sizeof(heap_tree));
    tree->nodes = NULL;
    tree->nodesSize = 0;
    tree->predicate = &_min_heap_predicate;

    return tree;
}

void _heap_resize(heap_tree* tree, int nodesSize)
{
    if (tree->nodes)
    {
        tree->nodes = realloc(tree->nodes, nodesSize * sizeof(heap_node));
    }
    else
    {
        tree->nodes = malloc(nodesSize * sizeof(heap_node));
    }
    tree->nodesSize = nodesSize;
}

int _heap_index_by_node(heap_tree* tree, heap_node* node)
{
    return node - &tree->nodes[0];
}

heap_node* _heap_node_by_index(heap_tree* tree, int idx)
{
    if (idx <= tree->nodesSize-1)
    {
        return &tree->nodes[idx];
    }

    return NULL;
}

heap_node* _heap_node_parent(heap_tree* tree, heap_node* node)
{

    heap_node* parent = _heap_node_by_index(tree, (_heap_index_by_node(tree, node)-1)/2);
    if (node == parent)
    {
        return NULL;
    }
    else
    {
        return parent;
    }
}

heap_node* _heap_node_left_child(heap_tree* tree, heap_node* node)
{
    return _heap_node_by_index(tree, (2*_heap_index_by_node(tree, node)) + 1);
}

heap_node* _heap_node_right_child(heap_tree* tree, heap_node* node)
{
    return _heap_node_by_index(tree, (2*_heap_index_by_node(tree, node)) + 2);
}

heap_node* _heap_swap(heap_node* parent, heap_node* child)
{
    heap_node v = *parent;
    *parent = *child;
    *child = v;
}

heap_node* _heap_reheapify_up(heap_tree* tree, heap_node* node)
{
    heap_node* parent = _heap_node_parent(tree, node);
    if (parent)
    {
        if (!tree->predicate(parent->key, node->key))
        {
            _heap_swap(parent, node); /* Not in right order, swap them */
            return _heap_reheapify_up(tree, parent);
        }
    }

    return node;
}

heap_node* _heap_reheapify_down(heap_tree* tree, heap_node* node)
{
    heap_node* left = _heap_node_left_child(tree, node);
    heap_node* right = _heap_node_right_child(tree, node);
    heap_node* best = NULL;

    if (left && right)
    {
        best = tree->predicate(left->key, right->key);
    }
    else if (left)
    {
        best = left;
    }
    else if (right)
    {
        best = right;
    }

    if (best && !tree->predicate(node->key, best->key))
    {
        _heap_swap(node, best);
        return _heap_reheapify_down(tree, best);
    }

    return node;
}

heap_node *heap_insert(heap_tree *tree, int key)
{
    heap_node ins;
    ins.key = key;
    return heap_insert_node(tree, ins);
}

heap_node *heap_insert_node(heap_tree *tree, heap_node ins)
{
    _heap_resize(tree, tree->nodesSize+1);
    tree->nodes[tree->nodesSize-1] = ins;
    return _heap_reheapify_up(tree, &tree->nodes[tree->nodesSize-1]);
}

void heap_delete(heap_tree *tree, heap_node *del)
{
    _heap_swap(del, &tree->nodes[tree->nodesSize-1]);
    _heap_resize(tree, tree->nodesSize - 1); /* downsize array by 1, effectively deleting last element */
    _heap_reheapify_down(tree, del); /* pointer is to last value we must reheapify down */
}

heap_node heap_pop(heap_tree *tree)
{
    heap_node root = tree->nodes[0];
    heap_delete(tree, &tree->nodes[0]);
    return root;
}

int _heap_validate_recurse(heap_tree* tree, heap_node* node)
{
    heap_node* left = _heap_node_left_child(tree, node);
    heap_node* right = _heap_node_right_child(tree, node);

    if (left)
    {
        if (!tree->predicate(node->key, left->key) || !_heap_validate_recurse(tree, left))
        {
            return 0;
        }
    }

    if (right)
    {
        if (!tree->predicate(node->key, right->key) || !_heap_validate_recurse(tree, right))
        {
            return 0;
        }
    }

    return 1;
}

int heap_validate(heap_tree *tree)
{
    if (tree->nodesSize > 0)
    {
        return _heap_validate_recurse(tree, &tree->nodes[0]);
    }

    return 1;
}

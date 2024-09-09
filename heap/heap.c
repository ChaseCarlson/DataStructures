#include "heap.h"

#include <stddef.h>
#include <stdlib.h>

int _min_heap_predicate(int parent, int child)
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
    tree->size = 0;
    tree->predicate = &_min_heap_predicate;
}

void _heap_resize(heap_tree* tree, int size)
{
    if (tree->nodes)
    {
        tree->nodes = realloc(tree->nodes, size*sizeof(heap_node));
    }
    else
    {
        tree->nodes = malloc(size*sizeof(heap_node));
    }

    tree->size = size;
}

int _heap_node_index(heap_tree* tree, heap_node* node)
{
    return node - &tree->nodes[0];
}

heap_node* _heap_node_by_index(heap_tree* tree, int idx)
{
    if (idx < tree->size)
    {
        return &tree->nodes[idx];
    }

    return NULL;
}

heap_node* _heap_node_parent(heap_tree* tree, heap_node* node)
{
    int idx = _heap_node_index(tree, node);
    int parentIdx = (idx-1)/2;
    if (parentIdx == idx)
    {
        return NULL; /* the math incorrectly gives us ourselves if we have no parent */
    }

    return _heap_node_by_index(tree, parentIdx);
}

heap_node* _heap_node_left_child(heap_tree* tree, heap_node* node)
{
    int idx = _heap_node_index(tree, node);
    int leftIdx = (2*idx)+1;
    heap_node* left = _heap_node_by_index(tree, leftIdx);

    return left;
}

heap_node* _heap_node_right_child(heap_tree* tree, heap_node* node)
{
    int idx = _heap_node_index(tree, node);
    int rightIdx = (2*idx)+2;
    heap_node* right = _heap_node_by_index(tree, rightIdx);

    return right;
}

void _heap_swap(heap_node* a, heap_node* b)
{
    if (a && b) /* a swap is a no-op if a or b is NULL, and could cause errors. same */
    {
        heap_node save = *a;
        *a = *b;
        *b = save;
    }
}

void _heapify_up(heap_tree* tree, heap_node* node)
{
    heap_node* parent = _heap_node_parent(tree, node);
    if (parent)
    {
        if (!tree->predicate(parent->key, node->key))
        {
            _heap_swap(parent, node);
            _heapify_up(tree, parent);
        }
    }
}

void _heapify_down(heap_tree* tree, heap_node* node)
{
    heap_node* left = _heap_node_left_child(tree, node);
    heap_node* right = _heap_node_right_child(tree, node);
    heap_node* predicate_better = NULL;

    if (left && right)
    {
        if (tree->predicate(left->key, right->key))
        {
            predicate_better = left; /* left fulfills predicate compared to right */
        }
        else
        {
            predicate_better = right; /* right wins if left loses */
        }
    }
    else if (left)
    {
        predicate_better = left;
    }
    else if (right)
    {
        predicate_better = right;
    }

    if (predicate_better && !tree->predicate(node->key, predicate_better->key))
    {
        _heap_swap(node, predicate_better);
        _heapify_down(tree, predicate_better); /* still points to the LOWER position */
    }
}

void heap_insert(heap_tree *tree, int key)
{
    heap_node node;
    node.key = key;
    _heap_resize(tree, tree->size+1);
    tree->nodes[tree->size-1] = node;
    _heapify_up(tree, &tree->nodes[tree->size-1]);
}

void heap_delete(heap_tree *tree, heap_node *del)
{
    heap_node* lastNode = &tree->nodes[tree->size-1];
    _heap_swap(del, lastNode);
    _heap_resize(tree, tree->size-1);
    if (tree->size > 1) /* IMPORTANT: you must not attempt to heapify down when there's only 1 element left. no reason to either  */
    {
        _heapify_down(tree, del); /* del still points to the location where the deleted node used to exist */
    }
}

heap_node heap_pop(heap_tree *tree) /* DON'T CALL ON EMPTY HEAP */
{
    heap_node node = tree->nodes[0];

    heap_delete(tree, &tree->nodes[0]);

    return node;
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
    if (tree->size > 0)
    {
        return _heap_validate_recurse(tree, &tree->nodes[0]);
    }

    return 1;
}

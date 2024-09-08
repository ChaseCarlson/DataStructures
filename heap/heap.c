#include "heap.h"

#include "stdlib.h"

heap_tree* min_heap_new()
{
    heap_tree* tree = malloc(sizeof(heap_tree));
    tree->nodes = NULL;
    tree->nodesSize = 0;
    tree->size = 0;
    tree->predicate = &min_heap_predicate;
}

heap_tree* max_heap_new()
{
    heap_tree* tree = malloc(sizeof(heap_tree));
    tree->nodes = NULL;
    tree->nodesSize = 0;
    tree->size = 0;
    tree->predicate = &max_heap_predicate;
}

void _heap_alloc(heap_tree* tree, int nodec)
{
    if (tree->nodes == NULL)
    {
        tree->nodes = malloc(nodec * sizeof(heap_node));
    }
    else if (tree->nodes)
    {
        tree->nodes = realloc(tree->nodes, nodec * sizeof(heap_node));
    }
    tree->nodesSize = nodec;
}

void _heap_swap(heap_tree* tree, int idx0, int idx1)
{
    heap_node n0 = tree->nodes[idx0];
    tree->nodes[idx0] = tree->nodes[idx1];
    tree->nodes[idx1] = n0;
}

int _heap_has_left(heap_tree* tree, int idx)
{
    int left_pos = heap_left_child_index(idx);
    return left_pos <= tree->size-1; /* has left child */
}

int _heap_has_right(heap_tree* tree, int idx)
{
    int right_pos = heap_right_child_index(idx);
    return right_pos <= tree->size-1; /* has right child */
}

void _heap_heapify_up(heap_tree* tree, int idx)
{
    heap_node node = tree->nodes[idx];
    heap_node parent = tree->nodes[heap_parent_index(idx)];

    if (!tree->predicate(parent.data, node.data)) /* Need to swap to fix heap property */
    {
        _heap_swap(tree, idx, heap_parent_index(idx));
        _heap_heapify_up(tree, heap_parent_index(idx));
    }
}

void _heap_heapify_down(heap_tree* tree, int idx)
{
    heap_node parent = tree->nodes[idx];
    int has_left = _heap_has_left(tree, idx);
    int has_right = _heap_has_right(tree, idx);
    int left_idx = heap_left_child_index(idx);
    int right_idx = heap_right_child_index(idx);

    if (has_left && has_right)
    {
        heap_node left = tree->nodes[left_idx];
        heap_node right = tree->nodes[right_idx];

        if (!tree->predicate(parent.data, left.data) && !tree->predicate(parent.data, right.data)) /* Need to fix the tree, both are wrong */
        {
            if (tree->predicate(left.data, right.data)) /* Left is <= (min) or >= (max) right */
            {
                _heap_swap(tree, idx, left_idx);
                _heap_heapify_down(tree, left_idx);
            }
            else
            {
                _heap_swap(tree, idx, right_idx);
                _heap_heapify_down(tree, right_idx);
            }
        }
    }
    else if (has_left && !has_right)
    {
        heap_node left = tree->nodes[left_idx];
        if (!tree->predicate(parent.data, left.data))
        {
            _heap_swap(tree, idx, left_idx);
            _heap_heapify_down(tree, left_idx);
        }
    }
    else if (has_right && !has_left)
    {
        heap_node right = tree->nodes[right_idx];
        if (!tree->predicate(parent.data, right.data))
        {
            _heap_swap(tree, idx, right_idx);
            _heap_heapify_down(tree, right_idx);
        }
    }

    /* Tree is fixed or never needed fixing */
}

void heap_insert(heap_tree *tree, int val)
{
    _heap_alloc(tree, tree->size+1);

    heap_node node;
    node.data = val;
    tree->nodes[tree->size] = node;
    tree->size++;

    _heap_heapify_up(tree, tree->size-1);
}

void heap_delete(heap_tree *tree, int idx)
{
    _heap_swap(tree, idx, tree->size-1); /* swaps node to be deleted with last node */
    _heap_alloc(tree, tree->size-1); /* sizes down 1, deleting last element */
    tree->size--;

    _heap_heapify_down(tree, idx); /* fix the heap */
}

int heap_pop(heap_tree *tree)
{
    int val = tree->nodes[0].data;

    heap_delete(tree, 0);

    return val;
}

int heap_parent_index(int idx)
{
    return (idx-1)/2;
}

int heap_left_child_index(int idx)
{
    return (2*idx) + 1;
}

int heap_right_child_index(int idx)
{
    return (2*idx) + 2;
}

int min_heap_predicate(int parent, int child)
{
    return parent <= child;
}

int max_heap_predicate(int parent, int child)
{
    return parent >= child;
}

int _heap_check_property_internal(heap_tree* tree, int idx)
{
    heap_node parent = tree->nodes[idx];
    if (_heap_has_left(tree, idx)) /* has left child */
    {
        int left_pos = heap_left_child_index(idx);
        heap_node left = tree->nodes[left_pos];
        if (tree->predicate(parent.data, left.data))
        {
            if (!_heap_check_property_internal(tree, left_pos))
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    if (_heap_has_right(tree, idx)) /* has right child */
    {
        int right_pos = heap_right_child_index(idx);
        heap_node right = tree->nodes[right_pos];
        if (tree->predicate(parent.data, right.data))
        {
            if (!_heap_check_property_internal(tree, right_pos))
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    return 1; /* no children */
}

int heap_check_property(heap_tree *tree)
{
    _heap_check_property_internal(tree, 0);
}

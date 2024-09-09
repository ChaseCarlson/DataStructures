#include "test.h"
#include <stdio.h>
#include <assert.h>

#include "heap.h"

heap_tree* gen_default_min_heap()
{
    heap_tree* tree = min_heap_new();

    heap_insert(tree, 1);

    heap_insert(tree, 3);
    heap_insert(tree, 2);

    heap_insert(tree, 5);
    heap_insert(tree, 7);
    heap_insert(tree, 3);
    heap_insert(tree, 3);

    heap_insert(tree, 9);
    heap_insert(tree, 6);
    heap_insert(tree, 8);
    heap_insert(tree, 10);
    heap_insert(tree, 11);
    heap_insert(tree, 12);
    heap_insert(tree, 5);
    heap_insert(tree, 7);

    return tree;
}

void test_pop_validate()
{
    heap_tree* tree = gen_default_min_heap();

    heap_node lastNode;
    heap_node node = heap_pop(tree);
    while (tree->nodesSize > 0)
    {
        lastNode = node;
        node = heap_pop(tree);
        assert(lastNode.key <= node.key);
    }
}

void test_default_min_heap()
{
    heap_tree* tree = gen_default_min_heap();

    assert(heap_validate(tree));

    /* Test adding elements out of order */
    heap_insert(tree, -5);
    heap_insert(tree, -8);
    assert(heap_validate(tree));
    assert(tree->nodes[0].key == -8);

    /* Test corrupting heap */
    tree->nodes[0].key = 500;
    assert(!heap_validate(tree));
    tree->nodes[0].key = -8;
    assert(heap_validate(tree));

    /* Test deleting element */
    heap_delete(tree, &tree->nodes[0]);
    assert(heap_validate(tree));
    heap_delete(tree, &tree->nodes[tree->nodesSize-1]);
    assert(heap_validate(tree));

}

void test_heap()
{
    printf("Heap Test Running\n");
    test_default_min_heap();
    test_pop_validate();
}
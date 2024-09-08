#include "heap.h"

#include "stdio.h"
#include "assert.h"

heap_tree* gen_example_min_heap()
{
    heap_tree* tree = min_heap_new();
    
    heap_insert(tree, 1);

    heap_insert(tree, 3);
    heap_insert(tree, 4);

    heap_insert(tree, 3);
    heap_insert(tree, 4);
    heap_insert(tree, 4);
    heap_insert(tree, 4);

    heap_insert(tree, 3);
    heap_insert(tree, 3);

    return tree;
}

void test_example_min_heap()
{
    heap_tree* tree = gen_example_min_heap();

    /* Check that heap property holds on default heap */
    assert(heap_check_property(tree));


    /* Check heap property after out-of-order insertions */
    heap_insert(tree, 2);
    heap_insert(tree, -10);
    heap_insert(tree, 30);

    assert(heap_check_property(tree));

    /* Check heap property after popping from the heap */

    heap_pop(tree);
    assert(heap_check_property(tree));


    /* Check heap property after deleting element with index 4 (5th element) */

    heap_delete(tree, 4);
    assert(heap_check_property(tree));

    /* Check heap_check_property on corrupted heap */
    tree->nodes[tree->size-1].data = -25;
    assert(!heap_check_property(tree));
}

void heap_run_all_tests()
{
    printf("Running Heap Tests\n");
    test_example_min_heap();
}

#include "test.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "heap.h"

heap_tree* gen_default_heap()
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

int rand_between(int a, int b)
{
    return a+((b-a)*((float)rand())/((float)RAND_MAX));
}

heap_tree* gen_random_heap()
{
    int min = -1000;
    int max = 1000;
    heap_tree* tree = min_heap_new();

    int i;
    for (i=0;i<rand_between(100, 1000); i++)
    {
        heap_insert(tree, rand_between(min, max));
    }

    return tree;
}

void test_pop_default_heap()
{
    heap_tree* tree = gen_default_heap();

    heap_node lastNode;
    heap_node node = heap_pop(tree);
    while (tree->size > 0)
    {
        lastNode = node;
        node = heap_pop(tree);
        /*printf("%i %i\n", lastNode.key, node.key);*/

        assert(lastNode.key <= node.key);
    }
    assert(heap_validate(tree));
}

void test_pop_random_heap()
{
    srand(time(NULL));

    int ti;
    for (ti=0; ti<10000; ti++)
    {
        heap_tree* tree = gen_random_heap();

        heap_node lastNode;
        heap_node node = heap_pop(tree);
        while (tree->size > 0)
        {
            lastNode = node;
            node = heap_pop(tree);
            /*printf("%i %i\n", lastNode.key, node.key);*/

            assert(lastNode.key <= node.key);
        }
        assert(heap_validate(tree));
    }
}

void test_default_heap()
{
    heap_tree* tree = gen_default_heap();

    assert(heap_validate(tree));

    tree->nodes[0].key = 1000;
    assert(!heap_validate(tree));
    tree->nodes[0].key = 1;
    assert(heap_validate(tree));
}

void test_heap()
{
    printf("Heap Test Init\n");
    test_default_heap();
    test_pop_default_heap();
    test_pop_random_heap();
}
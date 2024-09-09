#include "test.h"
#include <stdio.h>
#include <assert.h>

#include "linked_list.h"

list_node* gen_example_list()
{
    list_node* root = list_node_new(5);

    list_push_back(root, 7);
    list_push_back(root, 1);
    list_push_back(root, 1);
    list_push_back(root, 7);
    list_push_back(root, 48);
    list_push_back(root, 10);
    list_push_back(root, 5);
    list_push_back(root, -50);

    return root;
}

void test_example_list()
{
    list_node* root = gen_example_list();
    list_node* middle_node = root->next->next;
    assert(list_size(middle_node) == 9);
    assert(list_node_at(middle_node, 0)->data == 5);
    assert(list_node_at(middle_node, 1)->data == 7);
    assert(list_node_at(middle_node, 8)->data == -50);

    assert(list_find(middle_node, 7)->prev == root); /* should return 7 which is after root */
    assert(list_find(middle_node, -50)->data == -50);

    list_node_delete(list_find(root, 48));
    assert(list_node_get_tail(root)->data == -50);

    list_node_insert_before(root, 10);
    assert(list_node_get_root(middle_node)->data == 10);
    list_node_delete(list_node_get_root(middle_node));
    assert(list_node_get_root(middle_node)->data == 5);

    list_node_insert_after(middle_node, 15);
    assert(list_find(root, 15)->prev == middle_node);

    list_node_insert_before(middle_node, 15);
    assert(list_find(root, 15)->next == middle_node);

    assert(list_node_get_tail(root));
    assert(list_node_get_root(list_find(root, -50)) == root);

    list_push_front(middle_node, 100);
    assert(list_node_get_root(middle_node)->data == 100);
    list_pop_front(middle_node);
    assert(list_node_get_root(middle_node) == root);

    list_push_back(middle_node, 123);
    assert(list_node_get_tail(middle_node)->data == 123);
    list_pop_back(middle_node);
    assert(list_node_get_tail(middle_node)->data == -50);
}

void linked_list_test()
{
    printf("Running Linked List Tests\n");
    test_example_list();
}
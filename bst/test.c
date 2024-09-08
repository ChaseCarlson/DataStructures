#include "test.h"

#include "bst.h"

#include "stdio.h"
#include "assert.h"

bst_node* gen_bst_example_tree()
{
    bst_node* root = bst_node_new(30);

    bst_node_insert(root, 20);
    bst_node_insert(root, 40);

    bst_node_insert(root, 5);
    bst_node_insert(root, 25);
    bst_node_insert(root, 35);
    bst_node_insert(root, 55);

    bst_node_insert(root, 1);
    bst_node_insert(root, 7);
    bst_node_insert(root, 21);
    bst_node_insert(root, 29);
    bst_node_insert(root, 33);
    bst_node_insert(root, 37);
    bst_node_insert(root, 45);
    bst_node_insert(root, 100);

    bst_node_insert(root, -7);
    bst_node_insert(root, 23);
    bst_node_insert(root, 105);

    return root;
}

void bst_test_example_tree()
{
    bst_node* root = gen_bst_example_tree();

    /* Check tree positions */

    assert(root->data == 30);

    assert(root->left->data == 20);
    assert(root->right->data == 40);
    
    assert(root->left->left->data == 5);
    assert(root->left->right->data == 25);
    assert(root->right->left->data == 35);
    assert(root->right->right->data == 55);

    assert(root->left->left->left->data == 1);
    assert(root->left->left->right->data == 7);
    assert(root->left->right->left->data == 21);
    assert(root->left->right->right->data == 29);
    assert(root->right->left->left->data == 33);
    assert(root->right->left->right->data == 37);
    assert(root->right->right->left->data == 45);
    assert(root->right->right->right->data == 100);

    assert(root->left->left->left->left->data == -7);
    assert(root->left->right->left->right->data == 23);
    assert(root->right->right->right->right->data == 105);

    /* Is Leaf */
    assert(bst_node_is_leaf(root) == 0);
    assert(bst_node_is_leaf(root->left) == 0);

    assert(bst_node_is_leaf(root->left->left->left->left) == 1);
    assert(bst_node_is_leaf(root->left->right->left->right) == 1);
    assert(bst_node_is_leaf(root->right->right->right->right) == 1);

    assert(bst_check_property(root));

    /* Find node by value tests */

    assert(bst_node_find(root, 30) == root);

    assert(bst_node_find(root, 40) == root->right);

    assert(bst_node_find(root, 35) == root->right->left);

    assert(bst_node_find(root, 29) == root->left->right->right);
    assert(bst_node_find(root, 100) == root->right->right->right);

    /* Find node successor/predecessor */
    assert(bst_node_successor(bst_node_find(root, 30)) == bst_node_find(root, 33));
    assert(bst_node_predecessor(bst_node_find(root, 30)) == bst_node_find(root, 29));

    assert(bst_node_successor(bst_node_find(root, 40)) == bst_node_find(root, 45));
    assert(bst_node_predecessor(bst_node_find(root, 40)) == bst_node_find(root, 37));

    assert(bst_node_successor(bst_node_find(root, 7)) == bst_node_find(root, 5));
    assert(bst_node_predecessor(bst_node_find(root, 7)) == bst_node_find(root, 5));

    /* Delete nodes */
    bst_node_delete(bst_node_find(root, 25)); /* 2 children */
    assert(bst_check_property(root));
    bst_node_delete(bst_node_find(root, 55)); /* 2 children */
    assert(bst_check_property(root));
    bst_node_delete(bst_node_find(root, 100)); /* has right child */
    assert(bst_check_property(root));
    bst_node_delete(bst_node_find(root, 1)); /* has left child */
    assert(bst_check_property(root));
    bst_node_delete(bst_node_find(root, 23)); /* leaf */
    assert(bst_check_property(root));

    /* Got Root? */
    /*assert(root == bst_get_root(bst_node_find(root, 5))); */

    /* Test bst_check_property */
    /* We do this by intentionally corrupting the tree, so run this last */
    bst_node* corruptedNode = bst_node_find(root, 35);
    corruptedNode->data = 573;
    assert(!bst_check_property(root));
}

void bst_test_run_all()
{
    printf("Running all tests\n");
    bst_test_example_tree();
    printf("All tests passing\n");
}
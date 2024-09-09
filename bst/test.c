#include "test.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

bst_node* gen_default_bst()
{
    bst_node* root = bst_node_new(100);

    bst_insert(root, 50);
    bst_insert(root, 200);

    bst_insert(root, 25);
    bst_insert(root, 75);
    bst_insert(root, 150);
    bst_insert(root, 225);

    bst_insert(root, 12);
    bst_insert(root, 30);
    bst_insert(root, 55);
    bst_insert(root, 80);
    bst_insert(root, 120);
    bst_insert(root, 170);
    bst_insert(root, 205);
    bst_insert(root, 315);

    bst_insert(root, 6);
    bst_insert(root, 400);

    return root;
}

int random_between(int a, int b)
{
    return (((float)rand())/((float)RAND_MAX)*(b-a))+a;
}

bst_node* gen_random_bst()
{
    int min = -1000;
    int max = 1000;
    bst_node* root = bst_node_new(random_between(min, max));

    int i;
    for (i=0; i<random_between(100, 1000); i++)
    {
        bst_insert(root, random_between(min, max));
    }

    return root;
}

void test_default_bst()
{
    bst_node* root = gen_default_bst();

    assert(bst_validate(root)); /* Validate before we begin */

    /* Insert node and validate */
    bst_insert(root, 20);
    assert(bst_validate(root));
    
    /* Test find */
    assert(root == bst_find(root, 100));
    assert(root->left == bst_find(root, 50));
    assert(root->right == bst_find(root, 200));
    assert(root->right->right->left == bst_find(root, 205));

    /* Test inorder successor */
    assert(bst_inorder_successor(root) == root->right->left->left);
    assert(bst_inorder_successor(root->right->right->right->right) == root->right->right->right);

    /* Test inorder predecessor */
    assert(bst_inorder_predecessor(root) == root->left->right->right);
    assert(bst_inorder_predecessor(root->left->left->left->left) == root->left->left->left);

    /* Test min */
    assert(bst_min(root)->key == 6);
    assert(bst_min(root->right->right->right->right)->key == 400);

    /* Test max */
    assert(bst_max(root)->key == 400);
    assert(bst_max(root->left->left->left->left)->key == 6);

    /* Corrupt the BST and check that validation fails */
    root->left->right->key = 300;
    assert(!bst_validate(root));
    root->left->right->key = 75;
    assert(bst_validate(root));
    root->key = -500;
    assert(!bst_validate(root));
    root->key = 100;
    assert(bst_validate(root));

    /* Test delete */
    bst_delete(root->left->right->right); /* 0 children */
    assert(bst_validate(root));

    /* 1 child */
    bst_delete(root->left->left->left);
    assert(bst_validate(root));

    bst_delete(root->right->right->right);
    assert(bst_validate(root));

    /* 2 children */
    bst_delete(root->right);
    assert(bst_validate(root));
}

void test_random_bst()
{
    printf("Testing random BST\n");
    srand(time(NULL));
    int i;
    for (i=0;i<100000;i++)
    {
        bst_node* root = gen_random_bst();
        assert(bst_validate(root));
    }
}

void test_bst()
{
    printf("BST Tests Running\n");
    test_default_bst();
    test_random_bst();
}

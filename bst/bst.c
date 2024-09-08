#include "bst.h"

#include "stdlib.h"

bst_node *bst_node_new(int val)
{
    bst_node* node = malloc(sizeof(bst_node));
    node->data = val;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
}

void _bst_node_set_left(bst_node* root, bst_node* left)
{
    root->left = left;
    if (left)
    {
        left->parent = root;
    }
}

void _bst_node_set_right(bst_node* root, bst_node* right)
{
    root->right = right;
    if (right)
    {
        right->parent = root;
    }
}


bst_node* _bst_node_insert_node(bst_node* root, bst_node* ins)
{
    if (ins->data == root->data) return NULL;

    if (ins->data < root->data)
    {
        if (root->left)
        {
            return _bst_node_insert_node(root->left, ins);
        }
        else
        {
            _bst_node_set_left(root, ins);
            return ins;
        }
    }
    else
    {
        if (root->right)
        {
            return _bst_node_insert_node(root->right, ins);
        }
        else
        {
            _bst_node_set_right(root, ins);
            return ins;
        }
    }

    return NULL;
}

bst_node *bst_node_insert(bst_node *root, int val)
{
    bst_node* new = bst_node_new(val);
    _bst_node_insert_node(root, new);
    return new;
}

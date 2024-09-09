#include "bst.h"

#include <stddef.h>
#include <stdlib.h>

bst_node *bst_node_new(int key)
{
    bst_node* node = malloc(sizeof(bst_node));
    node->key = key;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
}

void _bst_node_set_left(bst_node* node, bst_node* left)
{
    if (left)
    {
        if (left->parent) /* remove ourselves from the parent */
        {
            if (left->parent->left == left)
            {
                left->parent->left = NULL;
            }
            else if (left->parent->right == left)
            {
                left->parent->right = NULL;
            }
        }
        left->parent = node;
    }
    if (node)
    {
        node->left = left;
    }
}

void _bst_node_set_right(bst_node* node, bst_node* right)
{
    if (right)
    {
        if (right->parent) /* remove ourselves from the parent */
        {
            if (right->parent->left == right)
            {
                right->parent->left = NULL;
            }
            else if (right->parent->right == right)
            {
                right->parent->right = NULL;
            }
        }
        right->parent = node;
    }
    if (node)
    {
        node->right = right;
    }
}

void _bst_node_replace_child(bst_node* parent, bst_node* current, bst_node* replacement)
{
    if (parent->left == current)
    {
        _bst_node_set_left(parent, replacement);
    }
    else if (parent->right == current)
    {
        _bst_node_set_right(parent, replacement);
    }
}

bst_node *bst_insert(bst_node *root, int key)
{
    if (key < root->key)
    {
        if (root->left)
        {
            bst_insert(root->left, key);
        }
        else
        {
            bst_node* ins = bst_node_new(key);
            _bst_node_set_left(root, ins);
        }
    }
    else if (key > root->key)
    {
        if (root->right)
        {
            bst_insert(root->right, key);
        }
        else
        {
            bst_node* ins = bst_node_new(key);
            _bst_node_set_right(root, ins);
        }
    }
}

bst_node *bst_find(bst_node *root, int find_key)
{
    if (root->key == find_key)
    {
        return root;
    }

    if (find_key < root->key)
    {
        if (root->left)
        {
            return bst_find(root->left, find_key);
        }
    }
    else if (find_key > root->key)
    {
        if (root->right)
        {
            return bst_find(root->right, find_key);
        }
    }

    return NULL;
}

bst_node *bst_inorder_successor(bst_node *node)
{
    if (!node->right)
    {
        return node->parent;
    }

    return bst_min(node->right);
}

bst_node *bst_inorder_predecessor(bst_node *node)
{
    if (!node->left)
    {
        return node->parent;
    }

    return bst_max(node->left);
}

bst_node *bst_min(bst_node *node)
{
    if (!node->left)
    {
        return node;
    }

    return bst_min(node->left);
}

bst_node *bst_max(bst_node *node)
{
    if (!node->right)
    {
        return node;
    }

    return bst_max(node->right);
}

void bst_delete(bst_node *node)
{
    if (!node->left && !node->right) /* Leaf node (no children) */
    {
        _bst_node_replace_child(node->parent, node, NULL);
        free(node);
    }
    else if (node->left && !node->right) /* Left child */
    {
        _bst_node_replace_child(node->parent, node, node->left);
        bst_delete(node);
    }
    else if (node->right && !node->left)
    {
        _bst_node_replace_child(node->parent, node, node->right);
        bst_delete(node);
    }
    else if (node->left && node->right)
    {
        bst_node* successor = bst_inorder_successor(node);
        node->key = successor->key;
        bst_delete(successor);
    }
}

int bst_validate(bst_node *root)
{
    if (root->left)
    {
        if (!(root->left->key < root->key && bst_validate(root->left)))
        {
            return 0;
        }
    }

    if (root->right)
    {
        if (!(root->right->key > root->key && bst_validate(root->right)))
        {
            return 0;
        }
    }

    return 1;
}

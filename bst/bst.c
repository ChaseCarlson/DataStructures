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

void _bst_node_set_left(bst_node* node, bst_node* left)
{
    if (node)
    {
        if (node->left)
        {
            node->left->parent = NULL;
        }
        node->left = left;
    }
    if (left)
    {
        left->parent = node;
    }
}

void _bst_node_set_right(bst_node* node, bst_node* right)
{
    if (node)
    {
        if (node->right)
        {
            node->right->parent = NULL;
        }
        node->right = right;
    }
    if (right)
    {
        right->parent = node;
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

bst_node *bst_node_find(bst_node *root, int val)
{
    if (val == root->data) return root;

    if (val < root->data && root->left)
    {
        return bst_node_find(root->left, val);
    }
    else if (val > root->data && root->right)
    {
        return bst_node_find(root->right, val);
    }

    return NULL;
}

void bst_node_replace_child(bst_node* parent, bst_node* child, bst_node* replacement)
{
    if (parent == NULL) return;

    if (parent->left == child)
    {
        _bst_node_set_left(parent, replacement);
    }
    else if (parent->right == child)
    {
        _bst_node_set_right(parent, replacement);
    }
}

void bst_node_delete(bst_node *toDel)
{
    if (toDel->left == NULL && toDel->right == NULL) /* No children (leaf node) */
    {
        bst_node_replace_child(toDel->parent, toDel, NULL);
        toDel->parent = NULL;
        free(toDel);
    }
    else if (toDel->left && !toDel->right) /* Left child only */
    {
        bst_node_replace_child(toDel->parent, toDel, toDel->left);
        toDel->left = NULL;
        bst_node_delete(toDel);
    }
    else if (!toDel->left && toDel->right) /* Right child only */
    {
        bst_node_replace_child(toDel->parent, toDel, toDel->right);
        toDel->right = NULL;
        bst_node_delete(toDel);
    }
    else if (toDel->left && toDel->right) /* Two children */
    {
        bst_node* successor = bst_node_successor(toDel);
        toDel->data = successor->data;
        bst_node_delete(successor);

        /* This works too: */
        /*
        bst_node* predecessor = bst_node_predecessor(toDel);
        toDel->data = predecessor->data;
        bst_node_delete(predecessor);
        */
    }
}

bst_node *bst_get_root(bst_node *node)
{
    if (node->parent == NULL)
    {
        return node;
    }

    return bst_get_root(node->parent);
}

bst_node *bst_node_successor(bst_node *node)
{
    if (!node->right)
    {
        return node->parent;
    }

    return bst_node_min(node->right);
}

bst_node *bst_node_predecessor(bst_node *node)
{
    if (!node->left)
    {
        return node->parent;
    }

    return bst_node_max(node->left);
}

bst_node *bst_node_min(bst_node *node)
{
    if (!node->left)
    {
        return node;
    }

    return bst_node_min(node->left);
}

bst_node *bst_node_max(bst_node *node)
{
    if (!node->right)
    {
        return node;
    }

    return bst_node_max(node->right);
}

int bst_node_is_leaf(bst_node *node)
{
    if (node->left == NULL && node->right == NULL)
    {
        return 1;
    }

    return 0;
}

int bst_check_property(bst_node *root)
{
    if (root->left)
    {
        if (!(root->left->data < root->data))
        {
            return 0;
        }
        if (!bst_check_property(root->left))
        {
            return 0;
        }
    }

    if (root->right)
    {
        if (!(root->right->data > root->data))
        {
            return 0;
        }
        if (!bst_check_property(root->right))
        {
            return 0;
        }
    }

    return 1;
}

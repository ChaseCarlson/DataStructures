#ifndef DSA_BST_H
#define DSA_BST_H

typedef struct bst_node
{
    int data;
    struct bst_node* parent; /* must write struct since we're in C89 */
    struct bst_node* left;
    struct bst_node* right;
} bst_node;

bst_node* bst_node_new(int val);
bst_node* bst_node_insert(bst_node* root, int val);
bst_node* bst_node_find(bst_node* root, int val);
void bst_node_delete(bst_node* toDel);
bst_node* bst_get_root(bst_node* node);
bst_node* bst_node_successor(bst_node* node);
bst_node* bst_node_predecessor(bst_node* node);
bst_node* bst_node_min(bst_node* node);
bst_node* bst_node_max(bst_node* node);
int bst_node_is_leaf(bst_node* node);
int bst_check_property(bst_node* root);

#endif
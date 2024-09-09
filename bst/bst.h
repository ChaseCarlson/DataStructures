#ifndef DS_BST_H
#define DS_BST_H

typedef struct bst_node {
    int key;
    struct bst_node* parent;
    struct bst_node* left;
    struct bst_node* right;
} bst_node;

bst_node* bst_node_new(int key);
bst_node* bst_insert(bst_node* root, int key);
bst_node* bst_find(bst_node* root, int find_key);
bst_node* bst_inorder_successor(bst_node* node);
bst_node* bst_inorder_predecessor(bst_node* node);
bst_node* bst_min(bst_node* node);
bst_node* bst_max(bst_node* node);
void bst_delete(bst_node* node);
int bst_validate(bst_node* root);

#endif
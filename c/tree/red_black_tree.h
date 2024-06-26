#ifndef INT_RED_BLACK_TREE_H
#define INT_RED_BLACK_TREE_H

#include "stdlib.h"
#include "assert.h"
#include "queue.h"

#define RED_COLOR "\033[31m"
#define WHITE_COLOR "\033[37m"
#define RESET_COLOR "\033[0m"

typedef struct RedBlackNode RedBlackNode;
struct RedBlackNode {
    bool is_black;
    int key;

    RedBlackNode* parent;
    RedBlackNode* left;
    RedBlackNode* right;
};

typedef RedBlackNode* RedBlackNodePtr;
QUEUE_DEFINE_FOR(RedBlackNodePtr);

typedef struct RedBlackTree {
    RedBlackNode* root;
} RedBlackTree;

RedBlackTree red_black_tree_new() {
    return (RedBlackTree) { NULL };
}

RedBlackNode* _red_black_node_new(int key, bool is_black, RedBlackNode* parent) {
    RedBlackNode* node = (RedBlackNode*)malloc(sizeof(RedBlackNode));
    assert(node != NULL);

    node->is_black = is_black;
    node->key = key;
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void _red_black_node_free_including_children(RedBlackNode* node) {
    if (node == NULL) return;
    _red_black_node_free_including_children(node->left);
    _red_black_node_free_including_children(node->right);
    free(node);
}

void red_black_tree_free(RedBlackTree* tree) {
    _red_black_node_free_including_children(tree->root);
    tree->root = NULL;
}

void _red_black_tree_left_rotate(RedBlackTree* tree, RedBlackNode* x) {
    RedBlackNode* y = x->right;

    y->parent = x->parent;
    x->parent = y;
    if (y->parent == NULL) {
        tree->root = y;
    }
    else if (y->parent->right == x) {
        y->parent->right = y;
    }
    else {
        y->parent->left = y;
    }
    x->right = y->left;
    if (x->right != NULL) {
        x->right->parent = x;
    }
    y->left = x;
}

void _red_black_tree_right_rotate(RedBlackTree* tree, RedBlackNode* x) {
    RedBlackNode* y = x->left;
    y->parent = x->parent;
    x->parent = y;
    if (y->parent == NULL) {
        tree->root = y;
    }
    else if (y->parent->right == x) {
        y->parent->right = y;
    }
    else {
        y->parent->left = y;
    }

    x->left = y->right;
    if (x->left != NULL) {
        x->left->parent = x;
    }
    y->right = x;
}

void _red_black_tree_fix_insert(RedBlackTree* tree, RedBlackNode* node) {
    while (node->parent != NULL && node->parent->is_black == false) {
        RedBlackNode* parent = node->parent;
        RedBlackNode* grand_parent = node->parent->parent;

        if (parent == grand_parent->left) {
            RedBlackNode* uncle = grand_parent->right;

            if (uncle != NULL && uncle->is_black == false) {
                grand_parent->is_black = false;
                parent->is_black = true;
                uncle->is_black = true;
                node = grand_parent;
            }
            else {
                if (node == parent->right) {
                    node = parent;
                    _red_black_tree_left_rotate(tree, node);
                }

                node->parent->is_black = true;
                node->parent->parent->is_black = false;
                _red_black_tree_right_rotate(tree, node->parent->parent);
            }
        }
        else {
            RedBlackNode* uncle = grand_parent->left;

            if (uncle != NULL && uncle->is_black == false) {
                grand_parent->is_black = false;
                parent->is_black = true;
                uncle->is_black = true;
                node = grand_parent;
            }
            else {
                if (node == parent->left) {
                    node = parent;
                    _red_black_tree_right_rotate(tree, node);
                }

                node->parent->is_black = true;
                node->parent->parent->is_black = false;
                _red_black_tree_left_rotate(tree, node->parent->parent);
            }
        }
    }
    tree->root->is_black = true;
}

bool red_black_tree_insert(RedBlackTree* tree, int key) {
    if (tree->root == NULL) {
        tree->root = _red_black_node_new(key, true, NULL);
        return;
    }

    RedBlackNode* parent = NULL;
    RedBlackNode* current = tree->root;
    while (current != NULL) {
        parent = current;
        if (key == current->key) {
            return false;
        }
        else if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    RedBlackNode* node = _red_black_node_new(key, false, parent);
    if (key < parent->key) {
        parent->left = node;
    }
    else {
        parent->right = node;
    }

    _red_black_tree_fix_insert(tree, node);

    return true;
}

void _red_black_tree_transplant(RedBlackTree* tree, RedBlackNode* u, RedBlackNode* v) {
    if (u->parent == NULL) {
        tree->root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

RedBlackNode* _red_black_tree_find_node(const RedBlackTree* tree, int key) {
    RedBlackNode* current = tree->root;
    while (current != NULL) {
        if (key == current->key) {
            return current;
        }
        else if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return NULL;
}

RedBlackNode* _red_black_tree_find_min_node(RedBlackNode* node) {
    /*while (node->left != NULL) {
        node = node->left;
    }*/
    if (node->left == NULL) return node;
    return node->left;
}

void _red_black_tree_fix_delete(RedBlackTree* tree, RedBlackNode* node) {
    while (node != tree->root && node->is_black) {
        RedBlackNode* parent = node->parent;

        if (node == parent->left) {
            RedBlackNode* brother = parent->right;
            if (!brother->is_black) {
                brother->is_black = true;
                parent->is_black = false;
                _red_black_tree_left_rotate(tree, parent);
                brother = parent->right;
            }
            if (brother->left->is_black && brother->right->is_black) {
                brother->is_black = false;
                node = parent;
            }
            else {
                if (brother->right->is_black) {
                    brother->left->is_black = true;
                    brother->is_black = false;
                    _red_black_tree_right_rotate(tree, brother);
                    brother = parent->right;
                }
                brother->is_black = parent->is_black;
                parent->is_black = true;
                brother->right->is_black = true;
                _red_black_tree_left_rotate(tree, parent);
                node = tree->root;
            }
        }
        else {
            // symmetric to the above 'if' block
            RedBlackNode* brother = parent->left;
            if (!brother->is_black) {
                brother->is_black = true;
                parent->is_black = false;
                _red_black_tree_right_rotate(tree, parent);
                brother = parent->left;
            }
            if (brother->right->is_black && brother->left->is_black) {
                brother->is_black = false;
                node = parent;
            }
            else {
                if (brother->left->is_black) {
                    brother->right->is_black = true;
                    brother->is_black = false;
                    _red_black_tree_left_rotate(tree, brother);
                    brother = parent->left;
                }
                brother->is_black = parent->is_black;
                parent->is_black = true;
                brother->left->is_black = true;
                _red_black_tree_right_rotate(tree, parent);
                node = tree->root;
            }
        }
    }
    node->is_black = true;
}

void red_black_tree_delete(RedBlackTree* tree, int key) {
    RedBlackNode* z = _red_black_tree_find_node(tree, key);
    if (z == NULL) return;

    RedBlackNode* y = z;
    bool y_original_is_black = y->is_black;
    RedBlackNode* x = NULL;

    if (z->left == NULL) {
        x = z->right;
        _red_black_tree_transplant(tree, z, z->right);
    }
    else if (z->right == NULL) {
        x = z->left;
        _red_black_tree_transplant(tree, z, z->left);
    }
    else {
        y = _red_black_tree_find_min_node(z->right);
        y_original_is_black = y->is_black;

        x = y->right;

        if (y->parent == z) {
            if (x != NULL) {
                x->parent = y;
            }
        }
        else {
            _red_black_tree_transplant(tree, y, x);

            y->right = z->right;
            y->right->parent = y;
        }

        _red_black_tree_transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->is_black = z->is_black;
    }

    if (y_original_is_black == true) {
        _red_black_tree_fix_delete(tree, x);
    }
}

void red_black_tree_print(RedBlackNode* node, int level) {
    if (node == NULL) {
        return;
    }

    red_black_tree_print(node->left, level + 1);

    for (int i = 0; i < 5 * level; i++) {
        printf(" ");
    }
    if (node->is_black) {
        printf("-->" WHITE_COLOR " %d\n" RESET_COLOR " ", node->key);
    }
    else {
        printf("-->" RED_COLOR " %d\n" RESET_COLOR " ", node->key);
    }

    red_black_tree_print(node->right, level + 1);
}

void red_black_tree_example() {
    RedBlackTree tree = red_black_tree_new();

    red_black_tree_insert(&tree, 7);
    red_black_tree_insert(&tree, 3);
    red_black_tree_insert(&tree, 18);
    red_black_tree_insert(&tree, 10);
    red_black_tree_insert(&tree, 22);
    red_black_tree_insert(&tree, 8);
    red_black_tree_insert(&tree, 11);
    red_black_tree_insert(&tree, 26);

    red_black_tree_print(tree.root, 0);

    printf("\n-------------------------------------\n");

    red_black_tree_delete(&tree, 18);

    red_black_tree_print(tree.root, 0);

    red_black_tree_free(&tree);
}

#endif // !INT_RED_BLACK_TREE_H

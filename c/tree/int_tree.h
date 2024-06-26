#ifndef INT_TREE_H
#define INT_TREE_H

#include "stdlib.h"
#include "stdio.h"
#include "stack/stack.h"

typedef struct IntTreeNode IntTreeNode;
struct IntTreeNode {
    int key;
    IntTreeNode* left;
    IntTreeNode* right;
};

// need to create type for pointer for stack working right
typedef IntTreeNode* IntTreeNodePtr;
STACK_DEFINE_FOR(IntTreeNodePtr);

typedef struct IntTree {
    IntTreeNode* root;
} IntTree;

typedef struct OptionalInt {
    bool present;
    int value;
} OptionalInt;

void int_tree_node_init(IntTreeNode* node, int key) {
    node->key = key;
    node->left = NULL;
    node->right = NULL;
}

IntTreeNode* int_tree_node_new(int key) {
    IntTreeNode* ptr = (IntTreeNode*)malloc(sizeof(IntTreeNode));
    int_tree_node_init(ptr, key);
    return ptr;
}

void int_tree_node_print(IntTreeNode* node) {
    printf("node %d\n", node->key);
}

void _int_tree_free_including_children(IntTreeNode* node) {
    if (node == NULL) return;
    _int_tree_free_including_children(node->left);
    _int_tree_free_including_children(node->right);
    free(node);
}

void int_tree_free(IntTree* tree) {
    _int_tree_free_including_children(tree->root);
    tree->root = NULL;
}

void int_tree_iterative_insert(IntTree* tree, int key) {
    if (tree->root == NULL) {
        tree->root = int_tree_node_new(key);
        return;
    }

    IntTreeNode* current = tree->root;
    while (current != NULL) {
        if (key < current->key) {
            if (current->left == NULL) {
                current->left = int_tree_node_new(key);
                current = NULL;
            }
            else {
                current = current->left;
            }
        }
        else {
            if (current->right == NULL) {
                current->right = int_tree_node_new(key);
                current = NULL;
            }
            else {
                current = current->right;
            }
        }
    }
}

// we need pointer to a pointer to node
// because we want to change pointer in tree, not just value
void int_tree_node_recursive_insert(IntTreeNode** node_ptr, int key) {
    if (*node_ptr == NULL) {
        *node_ptr = int_tree_node_new(key);
        return;
    }

    if (key < (*node_ptr)->key) {
        int_tree_node_recursive_insert(&((*node_ptr)->left), key);
    }
    else {
        int_tree_node_recursive_insert(&((*node_ptr)->right), key);
    }
}

void int_tree_recursive_insert(IntTree* tree, int key) {
    int_tree_node_recursive_insert(&(tree->root), key);
}

void int_tree_recursive_in_order_walk(IntTreeNode* node) {
    if (node == NULL) return;
    int_tree_recursive_in_order_walk(node->left);
    printf("node %d\n", node->key);
    int_tree_recursive_in_order_walk(node->right);
}

void int_tree_recursive_pre_order_walk(IntTreeNode* node) {
    if (node == NULL) return;
    printf("node %d\n", node->key);
    int_tree_recursive_in_order_walk(node->left);
    int_tree_recursive_in_order_walk(node->right);
}

void int_tree_recursive_post_order_walk(IntTreeNode* node) {
    if (node == NULL) return;
    int_tree_recursive_in_order_walk(node->left);
    int_tree_recursive_in_order_walk(node->right);
    printf("node %d\n", node->key);
}

/*
* My own old, require strategy to make it work
*
 while (stack.head != NULL) {
        if (stack.head->value->left != NULL) {
            STACK_PUSH(IntTreeNodePtr, stack, stack.head->value);
        }
        else {
            IntTreeNodePtr tree_node;
            STACK_POP(IntTreeNodePtr, &stack, &tree_node);

            printf("node %d\n", tree_node->key);

            if (tree_node->right != NULL) {
                STACK_PUSH(IntTreeNodePtr, stack, tree_node->right);
            }
        }
    }
*/

void int_tree_iterative_in_order_walk(IntTree* tree) {
    if (tree->root == NULL) return;

    STACK(IntTreeNodePtr) stack = STACK_NEW(IntTreeNodePtr);
    IntTreeNodePtr current = tree->root;

    while (true) {
        while (current != NULL) {
            STACK_PUSH(IntTreeNodePtr, stack, current);
            current = current->left;
        }

        if (STACK_IS_EMPTY(stack)) return;

        STACK_POP(IntTreeNodePtr, &stack, &current);
        printf("node %d\n", current->key);

        current = current->right;
    }
}

OptionalInt int_tree_minimum(IntTreeNode* node);
OptionalInt int_tree_minimum(IntTreeNode* node) {
    if (node == NULL) {
        return (OptionalInt) { false };
    }

    if (node->left == NULL) {
        return (OptionalInt) { true, node->key };
    }

    return int_tree_minimum(node->left);
}

OptionalInt int_tree_maximum_value(IntTreeNode* node);
OptionalInt int_tree_maximum_value(IntTreeNode* node) {
    if (node == NULL) {
        return (OptionalInt) { false };
    }

    if (node->right == NULL) {
        return (OptionalInt) { true, node->key };
    }

    return int_tree_maximum_value(node->right);
}

IntTreeNode* int_tree_maximum_node(IntTreeNode* node) {
    if (node == NULL) return NULL;
    if (node->right == NULL) return node;
    return int_tree_maximum_node(node->right);
}

// Implementation differs because I don't store parent in node
IntTreeNode* int_tree_predecessor(IntTree tree, int key) {
    IntTreeNode* predecessor = NULL;
    IntTreeNode* current = tree.root;

    while (current != NULL) {
        if (current->key < key) {
            predecessor = current;
            current = current->right;
        }
        else if (current->key > key) {
            current = current->left;
        }
        else {
            if (current->left != NULL) {
                predecessor = int_tree_maximum_node(current->left);
            }
            break;
        }
    }

    return predecessor;
}

void int_tree_example() {
    IntTree tree = { NULL };

    int_tree_iterative_insert(&tree, 10);
    int_tree_iterative_insert(&tree, 16);
    int_tree_recursive_insert(&tree, 17);
    int_tree_iterative_insert(&tree, 5);
    int_tree_iterative_insert(&tree, 4);
    int_tree_iterative_insert(&tree, 21);
    int_tree_recursive_insert(&tree, 1);

    printf("Pre order walk:\n");
    int_tree_recursive_pre_order_walk(tree.root);
    printf("Post order walk:\n");
    int_tree_recursive_post_order_walk(tree.root);

    printf("Recursive Center order walk:\n");
    int_tree_recursive_in_order_walk(tree.root);

    printf("Iterative Center order walk:\n");
    int_tree_iterative_in_order_walk(&tree);

    OptionalInt minimum = int_tree_minimum(tree.root);
    if (minimum.present) {
        printf("Tree minimum value: %d\n", minimum.value);
    }
    else {
        printf("Tree is empty\n");
    }

    OptionalInt maximum = int_tree_maximum_value(tree.root);
    if (maximum.present) {
        printf("Tree maximum value: %d\n", maximum.value);
    }
    else {
        printf("Tree is empty\n");
    }

    int key = 16;
    IntTreeNode* node = int_tree_predecessor(tree, key);
    if (node == NULL) {
        printf("No predecessor to %d\n", key);
    }
    else {
        printf("Predecessor to %d is %d\n", key, node->key);
    }

    int_tree_free(&tree);
}

#endif
#include <stdio.h>
#include <stdlib.h>

struct Node {
    char value;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(char value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void preorder_prefix(struct Node* node) {
    if (node == NULL) {
        return;
    }

    printf("%c ", node->value);
    preorder_prefix(node->left);
    preorder_prefix(node->right);
}

int main() {
    struct Node* root = createNode('+');
    root->left = createNode('*');
    root->left->left = createNode('5');
    root->left->right = createNode('4');
    root->right = createNode('-');
    root->right->left = createNode('2');
    root->right->right = createNode('3');

    printf("Prefix notation: ");
    preorder_prefix(root);

    return 0;
}


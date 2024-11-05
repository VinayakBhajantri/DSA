#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the garbage-collected memory
struct GCNode {
    int data;
    struct GCNode* left;
    struct GCNode* right;
    int mark; // Flag to mark reachable nodes
};

// Function to create a new node
struct GCNode* createNode(int data) {
    struct GCNode* newNode = (struct GCNode*)malloc(sizeof(struct GCNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->mark = 0; // Initialize mark as not reachable
    return newNode;
}

// Function to mark reachable nodes using postorder traversal
void markReachableNodes(struct GCNode* root) {
    if (root == NULL)
        return;

    markReachableNodes(root->left);
    markReachableNodes(root->right);

    // Mark the current node as reachable
    root->mark = 1;
}

// Function to perform garbage collection
void performGarbageCollection(struct GCNode** root) {
    if (*root == NULL)
        return;

    // Mark reachable nodes
    markReachableNodes(*root);

    // Delete unreachable nodes
    struct GCNode* current = *root;
    struct GCNode* parent = NULL;

    while (current != NULL) {
        if (current->mark == 0) {
            // Node is unreachable, delete it
            if (parent == NULL) {
                // Current node is the root
                *root = current->right;
                free(current);
                current = *root;
            } else {
                if (parent->left == current) {
                    parent->left = current->right;
                } else {
                    parent->right = current->right;
                }

                struct GCNode* temp = current;
                current = current->right;
                free(temp);
            }
        } else {
            // Node is reachable, move to the next node
            parent = current;
            current = current->right;
        }
    }
}

// Function to print the data of nodes in the garbage-collected memory
void printNodes(struct GCNode* root) {
    if (root == NULL)
        return;

    printNodes(root->left);
    printf("%d ", root->data);
    printNodes(root->right);
}

int main() {
    // Create nodes in the garbage-collected memory
    struct GCNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("Nodes before garbage collection: ");
    printNodes(root);
    printf("\n");

    // Perform garbage collection
    performGarbageCollection(&root);

    printf("Nodes after garbage collection: ");
    printNodes(root);
    printf("\n");

    return 0;
}

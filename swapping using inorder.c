#include <stdio.h>
#include <stdlib.h>

// Structure for a BST node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node in BST
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);

    return root;
}

// Function to swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Helper function to detect swapped elements in BST using inorder traversal
void detectSwappedElementsUtil(struct Node* root, struct Node** prev, struct Node** first, struct Node** middle, struct Node** last) {
    if (root == NULL)
        return;

    detectSwappedElementsUtil(root->left, prev, first, middle, last);

    if (*prev != NULL && root->data < (*prev)->data) {
        if (*first == NULL) {
            *first = *prev;
            *middle = root;
        } else {
            *last = root;
        }
    }

    *prev = root;

    detectSwappedElementsUtil(root->right, prev, first, middle, last);
}

// Function to detect swapped elements in BST
void detectSwappedElements(struct Node* root) {
    struct Node* prev = NULL;
    struct Node* first = NULL;
    struct Node* middle = NULL;
    struct Node* last = NULL;

    detectSwappedElementsUtil(root, &prev, &first, &middle, &last);

    if (first != NULL && last != NULL) {
        swap(&(first->data), &(last->data));
    } else if (first != NULL && middle != NULL) {
        swap(&(first->data), &(middle->data));
    }

    printf("Swapped elements in BST: ");
    if (first != NULL)
        printf("%d ", first->data);
    if (last != NULL)
        printf("%d", last->data);
    printf("\n");
}

// Function to print the inorder traversal of BST
void inorderTraversal(struct Node* root) {
    if (root == NULL)
        return;

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

int main() {
    struct Node* root = NULL;

    // Insert nodes into the BST
    root = insertNode(root, 6);
    root = insertNode(root, 10);
    root = insertNode(root, 3);
    root = insertNode(root, 4);
    root = insertNode(root, 2);
    root = insertNode(root, 8);
    root = insertNode(root, 7);

    printf("Inorder traversal before swapping: ");
    inorderTraversal(root);
    printf("\n");

    // Swap two elements in the BST
    swap(&(root->left->data), &(root->right->data));

    printf("Inorder traversal after swapping: ");
    inorderTraversal(root);
    printf("\n");

    // Detect and fix swapped elements in the BST
    detectSwappedElements(root);

    printf("Inorder traversal after fixing: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}


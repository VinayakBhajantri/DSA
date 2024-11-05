#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Node
{
	int key;
	struct Node *left;
	struct Node *right;
	int height;
};
struct Node* insert(struct Node* node, int key);
void preorder(FILE*fp,struct Node *root);
void inorder(FILE*fp,struct Node *root);
void postorder(FILE*fp,struct Node *root);
//void pre(struct Node*root);
struct Node* deleteNode(struct Node* root, int key);
void displayTree(struct Node* root, int space);
void random(int l, int h, int n);

int main()
{
    int l=2,h=80,n=200,i,t,r;
    int ch;
    clock_t start,stop;

    float time_r;
    FILE*fp4=fopen("logavlbst.txt","w");
    start=clock();

    random(l,h,n);
    FILE* fp=fopen("input.txt","r");
    FILE*fp1=fopen("preorder.txt","w");
    FILE*fp2=fopen("inorder.txt","w");
    FILE*fp3=fopen("postorder.txt","w");

    struct node*root=NULL;


    for(i=0;i<n;i++)
    {
        fscanf(fp,"%d",&r);
        root=insert(root,r);
    }


    displayTree(root,0);
    printf("\n");

    preorder(fp1,root);
    inorder(fp2,root);
        postorder(fp3,root);
        scanf("%d",&ch);
    switch(ch)
    {
        case 1: printf("Enter data to delete\n");
        scanf("%d",&t);
        root=deleteNode(root,t);
        displayTree(root,0);
        fprintf(fp1,"\nAfter deletion a tree\n");
        preorder(fp1,root);
        fprintf(fp2,"\nAfter deletion a tree\n");
        inorder(fp2,root);
        fprintf(fp3,"\nAfter deletion a tree\n");
        postorder(fp3,root);
        stop=clock();
    time_r = (float)(stop - start) / CLOCKS_PER_SEC;
    fprintf(fp4,"\nTime required for constructing a avl tree\n = %f\n",time_r);

        break;
        case 4:exit(0);

    }
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

}
int height(struct Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}
int max(int a, int b)
{
	return (a > b)? a : b;
}
struct Node* newNode(int key)
{
	struct Node* node = (struct Node*)
						malloc(sizeof(struct Node));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; // new node is initially added at leaf
	return(node);
}
struct Node *rightRotate(struct Node *y)
{
	struct Node *x = y->left;
	struct Node *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height(y->left),
					height(y->right)) + 1;
	x->height = max(height(x->left),
					height(x->right)) + 1;

	// Return new root
	return x;
}
struct Node *leftRotate(struct Node *x)
{
	struct Node *y = x->right;
	struct Node *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max(height(x->left),
					height(x->right)) + 1;
	y->height = max(height(y->left),
					height(y->right)) + 1;

	// Return new root
	return y;
}
int getBalance(struct Node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}
struct Node* insert(struct Node* node, int key)
{
	/* 1. Perform the normal BST insertion */
	if (node == NULL)
		return(newNode(key));

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else // Equal keys are not allowed in BST
		return node;

	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left),
						height(node->right));


	int balance = getBalance(node);


	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Right Right Case
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Left Right Case
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}
void preorder(FILE*fp,struct Node *root)
{
	if(root != NULL)
	{
       fprintf(fp,"%d ", root->key);
		preorder(fp,root->left);

		preorder(fp,root->right);

	}
}
void inorder(FILE*fp,struct Node *root)
{
	if(root != NULL)
	{

		inorder(fp,root->left);
		fprintf(fp,"%d ", root->key);

		inorder(fp,root->right);

	}
}
void postorder(FILE*fp,struct Node *root)
{
	if(root != NULL)
	{

		postorder(fp,root->left);

		postorder(fp,root->right);
		fprintf(fp,"%d ", root->key);

	}
}
void random(int l, int h, int n)
{
    int i, r;
    FILE *fp;
    fp = fopen("input.txt", "w");
    for (i = 0; i < n; i++)
    {
        r = rand() % (h - l) + l;
        fprintf(fp, "%d\t", r);
    }
    fclose(fp);
}
struct Node * minValueNode(struct Node* node)
{
	struct Node* current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}
struct Node* deleteNode(struct Node* root, int key)
{


	if (root == NULL)
		return root;


	if ( key < root->key )
		{
		    root->left = deleteNode(root->left, key);

		}


	else if( key > root->key )
		{
		    root->right = deleteNode(root->right, key);

		}


	else
	{


		if( (root->left == NULL) || (root->right == NULL) )
		{
			struct Node *temp = root->left ? root->left :
											root->right;

			// No child case
			if (temp == NULL)
			{
				temp = root;
				root = NULL;

			}
			else // One child case
			*root = *temp; // Copy the contents of
							// the non-empty child
			free(temp);
		}
		else
		{

			struct Node* temp = minValueNode(root->right);


			root->key = temp->key;


			root->right = deleteNode(root->right, temp->key);


		}

	}


	if (root == NULL)
	return root;


	root->height = 1 + max(height(root->left),
						height(root->right));


	int balance = getBalance(root);


	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);


	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}


	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);


	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}
void displayTree(struct Node* root, int space) {
    if (root == NULL)
        return;
    space += 10;

    displayTree(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);

    displayTree(root->left, space);
}

//BinaryTree.c
#include <stdio.h>
#include <stdlib.h>

struct node{

	int key;
	struct node *left;
	struct node *right;
	int height;
};

// Get height of the tree
int height(struct node *N){

	if(N == NULL)
		return 0;
	return N->height;
}

// Function to get max of two integers
int max(int a, int b){

	return (a > b)? a : b;
}

struct node* Insert(struct node *node, int key){

  // Could have created another function called newNode to make life easier but.... 
	if(node == NULL){
  // 1. Perform normal binary search tree inserstion 
		struct node* node = (struct node* )malloc(sizeof(struct node));
		node->key = key;
		node->left = NULL;
		node->right = NULL;
		node->height = 1;
		return node;
	}
  // right inserstion
	if(key > (node->key))
		node->right = Insert(node->right, key);
  // left
	else
		node->left = Insert(node->left, key);
  // 2. Update the height of node
	node->height = max(height(node->left), height(node->right)) + 1;

	return node;
}

struct node* Delete(struct node *node, int key){

	struct node *temp;
	if(node == NULL)
		printf("Element not found");
	else if(key < node->key)
		node->left = Delete(node->left, key);
	else if(key > node->key)
		node->right = Delete(node->right, key);
	else{
    // delete the node and replace with min element in right subtree or max element in the left subtree
		if(node->right && node->left){

			node->right = Delete(node->right, node->key);
		}
		else{
      // remove only one or zero children, then directly remove it from the tree and connect parent to its child
			temp = node;
			if(node->left == NULL)
				node = node->right;
			else if(node->right == NULL)
				node = node->right;
			free(temp); // Cya!
		}
	}
	return node;
}

void preOrder(struct node *root){

	if(root != NULL){
		printf("%d/%d ", root->key, root->height);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrder(struct node *root){

	if(root != NULL){
		inOrder(root->left);
		printf("%d/%d ", root->key, root->height);
		inOrder(root->right);
	}
}

void postOrder(struct node *root){

	if(root != NULL){
		postOrder(root->left);
		postOrder(root->right);
		printf("%d/%d ", root->key, root->height);
	}
}

int main()
{
	struct node *root = NULL;
	root = Insert(root, 1);
	root = Insert(root, 20);
	root = Insert(root, 5);
	root = Insert(root, 18);
	root = Insert(root, 66);
	root = Insert(root, 26);
	printf("PreOrder traversal is as follows\n");
	preOrder(root);
	printf("\n");

	printf("Node's deleted, PreOrder traversal is as follows\n");
	root = Delete(root, 5);
	root = Delete(root, 18);
	preOrder(root);
	printf("\n");

	printf("InOrder traversal is as follows\n");
	inOrder(root);
	printf("\n");

	printf("PosOrder traversal is as follows\n");
	postOrder(root);
	printf("\n");

	return 0;
}

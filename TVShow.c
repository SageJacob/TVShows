#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 1. Enter a list of shows into a binary search tree alphabetically
// 2. Ask the user which show they want to search for
// 3. Reach the desired node in O(logn) time
typedef struct node
{
	struct node *left, *right;
	char *show;
} node;
node *createNode(char *string)
{
	node *newNode = calloc(1, sizeof(node));
	newNode->show = malloc(sizeof(char) * (strlen(string) + 1));
	strcpy(newNode->show, string);
	newNode->show[strlen(string)] = '\0';
	return newNode;
}
// Traverses through the BST to insert alphabetically
node *treeTraversalHelper(node *root, node *nodeyNode)
{
	if (root == NULL || nodeyNode == NULL)
		return NULL;
	if (strcmp(nodeyNode->show, root->show) < 0)
	{
		if (root->left == NULL)
		{
			root->left = nodeyNode;
			return root;
		}
		treeTraversalHelper(root->left, nodeyNode);
	}
	if (strcmp(nodeyNode->show, root->show) > 0)
	{
		if (root->right == NULL)
		{
			root->right = nodeyNode;
			return root;
		}
		treeTraversalHelper(root->right, nodeyNode);
	}
	if (strcmp(nodeyNode->show, root->show) == 0)
		return root;
	return root;
}

node *treeTraversal(node *root, char *string)
{
	if (root == NULL)
		return createNode(string);
	return treeTraversalHelper(root, createNode(string));
}

node *Search(node *root, char *string)
{
	char *str = string;
	if (root == NULL)
		return NULL;
	if (strcmp(string, root->show) == 0)
	{
		printf("Finally, we have reached our destination!\n");
		printf("Show: %s\n", root->show);
		return root;
	}
	if (strcmp(string, root->show) < 0)
	{
		printf("Search in progress! Currently at: %s\n", root->show);
		Search(root->left, string);
	}
	if (strcmp(string, root->show) > 0)
	{
		printf("Search in progress! Currently at: %s\n", root->show);
		Search(root->right, string);
	}
	return root;
}

int main(void)
{
	int i = 0;
	node *root = NULL;
	char string[30], buffer[30], c;
	FILE *ifp = fopen("inputFile.txt", "r");
	if (ifp == NULL)
		return 0;
	while (fscanf(ifp, "%c", &c) != EOF)
	{
		if (c == '\n')
		{
			string[i] = '\0';
			root = treeTraversal(root, string);
			i = 0;
			continue;
		}
		string[i++] = c;
	}
	i = 0;
	printf("Please enter the show you'd like to find (case sensitive, max characters 30): ");
	fgets(buffer, 30, stdin);
	strcpy(string, buffer);
	while (string[i] != '\n')
		i++;
	string[i] = '\0';
	Search(root, string);
	return 0;
}

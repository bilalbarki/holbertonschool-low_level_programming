#include <stdlib.h>
#include "tree.h"
#include <string.h>

/**
 * btree_insert - creates a node in a binary tree
 * @tree: pointer to tree
 * @data: points to a string array
 */
int btree_insert(BTree **tree, char *data)
{
	if (*tree == NULL)
	{
		*tree = (BTree *) malloc(sizeof(BTree));
		if (tree == NULL)
		{
			return (1);
		}
		(*tree)->str = strdup(data);
		if (((*tree)->str) == NULL)
			return (1);
		/* initialize the children to null */
		(*tree)->left = NULL;
		(*tree)->right = NULL;
		return (0);
	}
	else if (strcmp(data, (*tree)->str) < 0)
	{
		btree_insert(&(*tree)->left, data);
	}
	else if (strcmp(data, (*tree)->str) >= 0)
	{
		btree_insert(&(*tree)->right, data);
	}
	return (0);
}

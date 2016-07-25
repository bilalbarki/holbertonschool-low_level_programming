#include <stdlib.h>
#include "tree.h"
#include <string.h>
int btree_insert(BTree **tree, char *data);

/**
 * Array_to_btree - converts an array of stings into a binary tree
 * @array: array passed as parameter
 */
BTree *array_to_btree(char **array)
{
	int i;
	BTree *tree = NULL;
	/*loop through the array*/
	for (i = 0; array[i]; i++)
		if( btree_insert(&tree, array[i]) )
			return NULL;
	return tree;
}

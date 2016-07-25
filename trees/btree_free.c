#include <stdlib.h>
#include "tree.h"

/**
 * btree_free - Frees memory for a binary tree
 * @tree: points to binary tree
 */
void btree_free(BTree *tree)
{
	if( tree != NULL )
	{
		btree_free( tree->left );
		btree_free( tree->right );
		free( tree -> str );
		free( tree );
	}
}

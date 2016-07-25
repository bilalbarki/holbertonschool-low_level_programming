#include <stdlib.h>
#include "tree.h"

/*frees a binary tree*/
void btree_free(BTree *tree)
{
	if( tree != NULL )
	{
		/*recursive calls*/
		btree_free( tree->left );
		btree_free( tree->right );
		/*freeing*/
		free( tree -> str );
		free( tree );
	}
}

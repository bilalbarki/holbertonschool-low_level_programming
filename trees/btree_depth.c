#include <stdlib.h>
#include "tree.h"

/**
 * btree_depth - calculates the depth of a binary tree
 * @tree: points to binary tree
 */
int btree_depth(BTree *tree) 
{
	if (tree==NULL) 
		return -1;
	else
	{
		int left_depth;
		int right_depth;
		left_depth = btree_depth(tree->left);
		right_depth = btree_depth(tree->right);
		if (left_depth > right_depth) 
			return(left_depth+1);
		else return(right_depth+1);
	}
}

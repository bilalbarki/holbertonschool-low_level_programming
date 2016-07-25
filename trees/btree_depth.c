#include <stdlib.h>
#include "tree.h"
/*calculates binary tree depth*/
int btree_depth(BTree *tree) 
{
	if (tree==NULL) 
		return -1;
	else
	{
		int left_depth;
		int right_depth;
		/* compute the depth of each subtree */
		left_depth = btree_depth(tree->left);
		right_depth = btree_depth(tree->right);
 
		/* use the larger one */
		if (left_depth > right_depth) 
			return(left_depth+1);
		else return(right_depth+1);
	}
}

#include "tree.h"
#include <string.h>

/**                                                                                         
 * btree_find - searches through the binary tree to find the given node element             
 * @tree: points to a binary tree                                                           
 * @str: string of array to find                                                            
 */
BTree *btree_find(BTree *tree, char *str)
{
	if (tree != NULL)
	{
		if (strcmp(tree->str, str) == 0)
		{
			return (tree);
		}
		else if (strcmp(str, tree->str) > 0)
		{
			return (btree_find(tree->left, str));
		}
		else
		{
			return (btree_find(tree->right, str));
		}
	}
	else
		return (NULL);
}


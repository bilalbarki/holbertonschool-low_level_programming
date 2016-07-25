#include "tree.h"
#include <string.h>

/**
 * btree_find - searches through the binary tree to find the given node element
 * @tree: points to a binary tree
 * @str: string of array to find
 */
BTree *btree_find(BTree *leaf, char *str)
{
  if( leaf != NULL )
  {
      if(strcmp(leaf->str, str) == 0)
      {
          return leaf;
      }
      else if(strcmp(str, leaf->str) > 0)
      {
	return btree_find(leaf->left, str);
      }
      else
      {
	return btree_find(leaf->right, str);
      }
  }
  else return NULL;
}

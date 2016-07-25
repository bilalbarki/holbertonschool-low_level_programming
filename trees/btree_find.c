#include "tree.h"
#include <string.h>

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

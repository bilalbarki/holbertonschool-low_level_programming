#include <stdlib.h>
#include "tree.h"

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

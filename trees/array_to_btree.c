#include <stdlib.h>
#include "tree.h"
#include <string.h>

int btree_insert(BTree **tree, char *data)
{
    if( *tree == NULL )
    {
        *tree = ( BTree* ) malloc( sizeof( BTree ) );
	if ( tree == NULL )
	{
	  return 1;
	}
        (*tree)->str = strdup(data);
        /* initialize the children to null */
        (*tree)->left = NULL;    
        (*tree)->right = NULL;
	return 0;
    }
    else if (strcmp(data, (*tree)->str) > 0 )
    {
      btree_insert( &(*tree)->left, data );
    }
    else if(strcmp(data, (*tree)->str) <= 0 )
    {
      btree_insert( &(*tree)->right, data );
    }
    return 0;
}


BTree *array_to_btree(char **array)
{
	int i;
	BTree *tree = NULL;
	for (i = 0; array[i]; i++)
		if( btree_insert(&tree, array[i]) )
			return NULL;
	return tree;
}

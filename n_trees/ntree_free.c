#include <stdlib.h>
#include "tree.h"
void ntree_free(NTree *);

/**
 * free_children - Frees ntree children
 * @list: Pointer to a list
 * Description: Frees the list of an ntree
 */
void free_children(List *list)
{
	List *next;
	next = list;
	while (next)
	{
		next = list->next;
		ntree_free(list->node);
		free(list);
		list = next;
	}
}


/**
 * ntree_free - Frees an ntree
 * @tree: first Pointer to an ntree
 * Description: Frees an ntree
 */
void ntree_free(NTree *tree)
{
	if (tree!=NULL)
	{
		free(tree->str);
		if (tree->children != NULL)
		{
			free_children(tree->children);
		}
		free(tree);
	}
}

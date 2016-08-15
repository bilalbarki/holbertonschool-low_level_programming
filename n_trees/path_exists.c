#include <stdlib.h>
#include <string.h>
#include "tree.h"

/**
 * path_exists - Checks if path exists
 * @root: Pointer to root of an ntree
 * @parents: Defines ancestors for the node
 * Description: Searches for a node and returns 1 if found, otherwise 0
 */
int path_exists(NTree *root, char **parents)
{
	int i;
	List *traverse;
	if(root==NULL || parents == NULL || parents[0]==NULL)
	{
		return 0;
	}
	if (strcmp(parents[0],root->str) == 0 && parents[1] == NULL) return 1;
	else if (parents[1] == NULL) { 
		return 0;
	}
	traverse = root->children;
	for (i=1; parents[i]!=NULL; i++)
	{
		while(traverse!=NULL)
		{
			if ( strcmp(parents[i], traverse->node->str) == 0)
			{
				if (parents[i+1] == NULL)
				{
					return 1;
				}
				else
				{
					traverse = traverse->node->children;
					break;
				}
			}
			else
			{
				traverse = traverse->next;
			}
		}
	}
	return 0;
}

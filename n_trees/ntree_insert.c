#include <stdlib.h>
#include <string.h>
#include "tree.h"

/**
 * traverse_nodes - Traverses the tree to find a node
 * @root: Pointer to root of an ntree
 * @parents: An array of strings, shows path to new node
 * Description: Follows parents path and searches for node
 */
List* traverse_nodes(NTree *root, char **parents)
{
	int i;
	List *traverse;
	if(root==NULL || parents == NULL || parents[0]==NULL)
	{
		return NULL;
	}
	if (parents[1] == NULL)
	{
		return NULL;
	}
	traverse = root->children;
	for (i=1; parents[i]!=NULL; i++)
	{
		while(traverse!=NULL)
		{
			if ( strcmp(parents[i], traverse->node->str) == 0 )
			{
				if (parents[i+1] == NULL)
				{
					return traverse;
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
	return NULL;
}

/**
 * create_tree_node - Adds a new child node for NTree
 * @str: String to be stored
 * Description: Adds a new node ntree node
 */
NTree *create_tree_node(char *str)
{
	NTree *node;
	node = malloc(sizeof(NTree));
	if (node == NULL)
	{
		return NULL;
	}
	node->str = strdup(str);
	if (node->str == NULL)
	{
		return NULL;
	}
	node->children = NULL;
	return node;
}

/**
 * create_new_list - created a new list
 * @head: pointer to head of a list
 * @str: string to be added
 * @root: root of Ntree
 * Description: Creates a new list node
 */
List* create_new_list(List *head, char *str, NTree *root)
{
	List *list;
	list = malloc(sizeof(List));
	if (list == NULL)
	{
		return NULL;
	}
	list->next = NULL;
	list->node = create_tree_node(str);
	if (head == NULL)
	{
		list->next = root->children;
		root->children = list;
		return list;
	}
	list->next = head->node->children;
	head->node->children = list;
	return list;
}

/**
 * ntree_insert - Following the parent path, adds new node
 * @tree: Points to root of NTree node
 * @parents: An array of strings, shows path to new node
 * @data: New string to be stored
 * Description: The func adds a new node to ntree
 */
int ntree_insert(NTree **tree, char **parents, char *data)
{
	List *list_node;
	if (*tree == NULL)
	{
		*tree = create_tree_node(data);
		return 0;
	}
	list_node = traverse_nodes(*tree, parents);
	if ( create_new_list(list_node, data, *tree) == NULL )
	{
		return 1;
	}
	return 0;
}

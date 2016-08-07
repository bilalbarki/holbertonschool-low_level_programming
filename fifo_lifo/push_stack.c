#include <stdlib.h>
#include <string.h>
#include "stack.h"

/**
 * push_stack - pushes string to a stack
 * @list: points to a stack
 * @str: string to be saved in the stack
 */
int push_stack(Stack **list, char *str)
{
	Stack *node;
	node = malloc(sizeof(Stack));
	if (node == NULL)
	{ 
		return (1);
	}
	node->str = strdup(str);
	if (node->str == NULL)
	{
		free(node);
		return (1);
	}
	node->next = (*list);
	*list = node;
	return (0);
}

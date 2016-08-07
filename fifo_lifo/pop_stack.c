#include <stdlib.h>
#include "stack.h"

/**
 * pop_stack - pops string from a stack
 * @list: points to a stack
 */
char *pop_stack(Stack **list)
{
	char *str;
	Stack *node;
	node = (*list);
	if (node == NULL)
	{
		return (NULL);
	}
	str = node->str;
	(*list) = node->next;
	free(node);
	return (str);  
}

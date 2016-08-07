#include <stdlib.h>
#include "queue.h"

/**
 * pop_queue - pops a string from a queue
 * @list: Queue linked list passed as an argument
 */
char *pop_queue(Queue **list)
{
	char *str;
	Queue *node;
	node = *list;
	if (node == NULL) 
	{
		return NULL;
	}
	str = node->str;
	(*list) = node->next;
	free(node);
	return str;
}

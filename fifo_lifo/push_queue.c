#include <stdlib.h>
#include <string.h>
#include "queue.h"

/**
 * push_queue - pushes a string to a queue
 * @list: points to a stack
 * @str: string to be saved in the queue
 */
int push_queue(Queue **list, char *str)
{
	Queue *node, *i;
	node = malloc( sizeof(Queue) );
	if (node == NULL)
	{
		return 1;
	}
	node->str = strdup(str);
	if (node->str == NULL)
	{
		free(node);
		return 1;
	}
	node->next=NULL;
	if ( (*list) == NULL)
	{
		(*list) = node;
	}
	else
	{
		for(i=*list ; i->next ; i=i->next);
		i->next=node;
	}
	return 0;
}

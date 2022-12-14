#include <stdlib.h>

#include "main.h"

/**
 * add_node_end - append a new node to a list
 * @head: pointer to the first node of the list
 * @str: string to set
 *
 * Return: address of new node
 * NULL if fails
*/
path_t *add_node_end(path_t **head, const char *str)
{
	path_t *newNode, *temp;

	if (head == NULL)
		return (NULL);
	newNode = malloc(sizeof(*newNode));
	if (newNode == NULL)
		return (NULL); /* insuffisient memory */
	newNode->dir = _strdup(str);
	if (newNode->dir == NULL)
		return (NULL);
	newNode->next = NULL;

	if (*head == NULL) /* first node */
	{
		*head = newNode;
		return (newNode);
	}

	/* finding last node */
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = newNode;

	return (newNode);
}

/**
 * free_list - free a path_t list
 * @head: start of list
*/
void free_list(path_t **head)
{
	path_t *temp, *hold;

	if (*head == NULL)
		return;

	hold = *head;
	while (TRUE)
	{
		if (hold == NULL)
			break;
		temp = hold;
		hold = hold->next;
		if (temp->dir)
			free(temp->dir);
		free(temp);
	}
}

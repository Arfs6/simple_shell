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
list_t *add_node_end(list_t **head, const char *str)
{
	list_t *newNode, *temp;

	if (head == NULL)
		return (NULL);
	newNode = malloc(sizeof(newNode));
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
 * free_list - free a list_t list
 * @head: start of list
*/
void free_list(list_t *head)
{
	list_t *temp;

	if (head == NULL)
		return;

	while (head->next != NULL)
	{
		temp = head->next;
		if (head->dir)
			free(head->dir);
		free(head);
		head = temp;
	}
	free(head->dir);
	free(head);
}

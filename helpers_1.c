#include "shell.h"

/**
 * addNodeToFront - Adds a node to the beginning of the list.
 * @head: Pointer to the head node.
 * @data: Data field of the node.
 * @index: Node index used for history.
 *
 * Return: Pointer to the new head node.
 */
list_t *addNodeToFront(list_t **head, const char *data, int index)
{
	list_t *newHead;

	if (!head)
		return (NULL);

	newHead = malloc(sizeof(list_t));
	if (!newHead)
		return (NULL);

	_memset((void *)newHead, 0, sizeof(list_t));
	newHead->num = index;

	if (data)
	{
		newHead->str = _strdup(data);
		if (!newHead->str)
		{
			free(newHead);
			return (NULL);
		}
	}

	newHead->next = *head;
	*head = newHead;
	return (newHead);
}

/**
 * addNodeToEnd - Adds a node to the end of the list.
 * @head: Pointer to the head node.
 * @data: Data field of the node.
 * @index: Node index used for history.
 *
 * Return: Pointer to the new node.
 */
list_t *addNodeToEnd(list_t **head, const char *data, int index)
{
	list_t *newNode, *node;

	if (!head)
		return (NULL);

	node = *head;
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);

	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = index;

	if (data)
	{
		newNode->str = _strdup(data);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;

		node->next = newNode;
	}
	else
		*head = newNode;

	return (newNode);
}

/**
 * printListData - Prints only the data element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Number of nodes in the list.
 */
size_t printListData(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * deleteNodeAtIndex - Deletes a node at the given index.
 * @head: Pointer to the head node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int deleteNodeAtIndex(list_t **head, unsigned int index)
{
	list_t *node, *prevNode;
	unsigned int currentIndex = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *head;
	while (node)
	{
		if (currentIndex == index)
		{
			prevNode->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}

		currentIndex++;
		prevNode = node;
		node = node->next;
	}

	return (0);
}

/**
 * freeList - Frees all nodes of a list.
 * @headPtr: Pointer to the head node.
 *
 * Return: void.
 */
void freeList(list_t **headPtr)
{
	list_t *node, *nextNode, *head;

	if (!headPtr || !*headPtr)
		return;

	head = *headPtr;
	node = head;
	while (node)
	{
		nextNode = node->next;
		free(node->str);
		free(node);
		node = nextNode;
	}

	*headPtr = NULL;
}
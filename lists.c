#include "shell.h"


/**
 * add_node - Adds a new node to a start of the linked list.
 * @head: Address of the pointer to the head node in the list.
 * @str: The string field of the node in the list.
 * @num: The node index used by hist.
 *
 *
 * Return: A pointer to the new head node.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - Adds a new node to the end of the linked list.
 * @head: Address of the ptr to the linked list head node.
 * @str: The string field of the linked list node.
 * @num: The node index used by history.
 *
 *
 * Return: A pointer to the new node.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_nod, *nod;

	if (!head)
		return (NULL);

	nod = *head;
	new_nod = malloc(sizeof(list_t));
	if (!new_nod)
		return (NULL);
	_memset((void *)new_nod, 0, sizeof(list_t));
	new_nod->num = num;
	if (str)
	{
		new_nod->str = _strdup(str);
		if (!new_nod->str)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->next)
			nod = nod->next;
		nod->next = new_nod;
	}
	else
		*head = new_nod;
	return (new_nod);
}

/**
 * print_list_str - Print only the string element of a list_t linked list.
 * @h: Pointer to the first nod.
 *
 * Return: The size of the list.
 */
size_t print_list_str(const list_t *h)
{
	size_t q = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		q++;
	}
	return (q);
}

/**
 * delete_node_at_index - Deletes node at a given index in the list.
 * @head: Address of the pointer to the first node in the list.
 * @index: Index of the node to delete.
 *
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int q = 0;

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
		if (q == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		q++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - Frees all nodes on linked list.
 * @head_ptr: Address of the pointer to the linked list head node.
 *
 *
 * Return: void.
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

/*
Copyright (c) 2017 Aramis Hornung Moraes

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "ahm_list.h"
#include <stdlib.h> // free()
#include <stdio.h> // printf()
#include <string.h> // Huffman strings manipulation.

// Returns a poiter of a empty list. DO NOT FORGET TO FREE THE MEMORY ALLOCATED BY CALLING "ahm_free_list(ahm_list *list_ptr)" BEFORE ENDING YOUR PROGRAM. 
ahm_list_node *ahm_allocate_list_node(void *data)
{
	ahm_list_node *new_node;
	new_node = (struct ahm_list_node*)malloc(sizeof(struct ahm_list_node));

	new_node->data = data;
	new_node->next = NULL;
	//new_node->previous = NULL;
	return new_node;
}
// Returns a poiter of a empty list.
ahm_list *ahm_allocate_list()
{
	ahm_list* new_list;
	new_list = (struct ahm_list*)malloc(sizeof(struct ahm_list));
	new_list->first = new_list->last = NULL;
	new_list->list_size = 0;
	return new_list;
}
// Returns 1 if list is empty. Returns 0 if list is not empty.
int ahm_is_list_empty(ahm_list *list)
{
	if (list->first == list->last && list->last == NULL)
		return 1;
	else return 0;
}
void ahm_free_list(ahm_list *list_ptr)
{
	ahm_list_node *node_ptr;
	ahm_list_node *freeable_node;

	/* free the nodes first */
	if (!ahm_is_list_empty(list_ptr))
	{
		node_ptr = list_ptr->first;
		while (node_ptr)
		{
			freeable_node = node_ptr;
			node_ptr = node_ptr->next;
			free(freeable_node);
		}
	}
	/* finally free the list structure */
	free(list_ptr);
}
void ahm_insert_firts_list(ahm_list *list_ptr, void *data)
{
	ahm_list_node *node_ptr = ahm_allocate_list_node(data);
	if (!ahm_is_list_empty(list_ptr))
	{
		node_ptr->next = list_ptr->first;
		list_ptr->first = node_ptr;
	}
	else
	{
		node_ptr->next = NULL;
		list_ptr->first = list_ptr->last = node_ptr;
	}
	++list_ptr->list_size;
}
void ahm_insert_after_list(ahm_list *list_ptr, ahm_list_node *node_ptr, void *data)
{
	ahm_list_node *insertion_node_ptr = ahm_allocate_list_node(data);
	insertion_node_ptr->next = node_ptr->next;
	node_ptr->next = insertion_node_ptr;

	// if next is null, then we can confirm this is the last element on the list
	if (insertion_node_ptr->next == NULL) 
		list_ptr->last = insertion_node_ptr;
	++list_ptr->list_size;
}
void ahm_insert_last_list(ahm_list *list_ptr, void *data)
{
	ahm_list_node *node_ptr = ahm_allocate_list_node(data);
	if (!ahm_is_list_empty(list_ptr))
	{
		list_ptr->last->next = node_ptr;
		list_ptr->last = node_ptr;
	}
	else
		list_ptr->first = list_ptr->last = node_ptr;
	++list_ptr->list_size;
}
void ahm_insert_indexed_list(ahm_list *list_ptr, unsigned int index, void *data)
{
	ahm_list_node *aux;
	if (ahm_is_list_empty(list_ptr))
	{
		ahm_insert_firts_list(list_ptr, data);
	}
	else if (index >= list_ptr->list_size)
	{
		ahm_insert_last_list(list_ptr, data);
	}
	else
	{
		unsigned int aux_i = 0;
		aux = list_ptr->first;
		while (aux_i < index && aux->next != NULL)
		{
			aux = aux->next;
			++aux_i;
		}
			
		aux->data = data;
	}
}

void* ahm_remove_first_list(ahm_list *list)
{
	void *data = NULL; // This is the value we will return.
	ahm_list_node *removed_node; // This pointer will be used to free the memory when we finish removing its value form the list.

	if (!ahm_is_list_empty(list))
	{
		removed_node = list->first;
		data = removed_node->data;
		if (!removed_node->next) // The fisrt node has a next node? if not, it was the only node in the list, now list will be empty.
			list->first = list->last = NULL;
		else // Else, the fisrt node of the list will be the ex-fisrt node's next.
			list->first = list->first->next;
		free(removed_node); // Prevent memory leaks.
		--list->list_size;
	}
	return data;
}
void* ahm_remove_after_list(ahm_list *list, ahm_list_node *node)
{
	void *data = NULL;
	ahm_list_node *removed_node;

	if (node->next)
	{
		removed_node = node->next;
		data = removed_node->data;

		if (removed_node->next)
			node->next = node->next->next;
		else
		{
			node->next = NULL;
			list->last = node;
		}
		free(removed_node);
		--list->list_size;
	}
	return data;
}
void* ahm_remove_last_list(ahm_list *list_ptr)
{
	void *data = NULL;
	ahm_list_node *removed_node;

	if (!ahm_is_list_empty(list_ptr))
	{
		removed_node = list_ptr->first; // Calm down, keep reading the code. We will navegate from the beginning of the list until we reach the end, then we will remove the last node.
		if (removed_node = list_ptr->last)
			list_ptr->first = list_ptr->last = NULL;
		else
		{
			while (removed_node->next->next) // we will navigate until we reach the antepenult node of the list, then we can remove_after that node we stoped by.
				removed_node = removed_node->next;

			data = ahm_remove_after_list(list_ptr, removed_node); // This function will also free the allocated memory of the node we want to remove.
			--list_ptr->list_size;
		}
	}
	return data;
}
void* ahm_remove_indexed_list(ahm_list *list_ptr, unsigned int index) // Not Tested
{
	ahm_list_node *aux;
	void *data = NULL;
	if (ahm_is_list_empty(list_ptr))
	{
		return NULL;
	}
	else if (index >= list_ptr->list_size)
	{
		return ahm_remove_last_list(list_ptr);
	}
	else
	{
		unsigned int aux_i = 0;
		aux = list_ptr->first;
		
		if (index == 0)
			return ahm_remove_first_list(list_ptr);
		else
		{
			while (aux_i < index-1 && aux->next != NULL)
			{
				aux = aux->next;
				++aux_i;
			}
			return ahm_remove_after_list(list_ptr, aux);
		}
	}
}
void ahm_print_int_list(ahm_list *list_ptr)
{
	ahm_list_node *aux;

	if (!ahm_is_list_empty(list_ptr))
	{
		aux = list_ptr->first;
		while (aux)
		{
			if (aux == list_ptr->last)
				printf("%d", (int)aux->data);
			else
				printf("%d, ", (int)aux->data);
			aux = aux->next;
		}
	}
}
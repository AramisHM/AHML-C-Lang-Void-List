#ifndef AHM_LIST_H
#define AHM_LIST_H

/* ---------------------------------------------------- VOID* LIST --------------------------------------------------- */

/* ---------------------------------------------------- definitions ---------------------------------------------------- */
// This is a node structure used for any type list (*void), its the most generic structure as for a list in the ahm library.
typedef struct ahm_list_node
{
	void *data;								// a pointer to anything your heat desire
	struct ahm_list_node *next;			// next node
	//struct ahm_list_node *previous;		// previous node - TODO
}ahm_list_node;

// This is a list type of void* nodes.
typedef struct ahm_list
{
	struct ahm_list_node *first;
	struct ahm_list_node *last;
	unsigned int list_size;
}ahm_list;

/* ---------------------------------------------------- functions ---------------------------------------------------- */

// Returns a poiter of a empty list. DO NOT FORGET TO FREE THE MEMORY ALLOCATED BY CALLING "ahm_free_list(ahm_list *list_ptr)" BEFORE ENDING YOUR PROGRAM. 
ahm_list_node *ahm_allocate_list_node(void *data);

// Returns a poiter of a empty list.
ahm_list *ahm_allocate_list();
void ahm_free_list(ahm_list *list_ptr);

// Returns 1 if list is empty. Returns 0 if list is not empty.
int ahm_is_list_empty(ahm_list *list);


void ahm_insert_firts_list(ahm_list *list_ptr, void *data);
void ahm_insert_after_list(ahm_list *list_ptr, ahm_list_node *node_ptr, void *data);
void ahm_insert_last_list(ahm_list *list_ptr, void *data);
void ahm_insert_indexed_list(ahm_list *list_ptr, unsigned int index, void *data);

void* ahm_remove_first_list(ahm_list *list);
void* ahm_remove_after_list(ahm_list *list,  ahm_list_node *node);
void* ahm_remove_last_list(ahm_list *list_ptr);
void* ahm_remove_indexed_list(ahm_list *list_ptr, unsigned int index);

void ahm_print_int_list(ahm_list *list_ptr);

#endif

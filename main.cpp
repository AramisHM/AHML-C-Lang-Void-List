/* 
AHML generic List Utilities
void list example

Copyright (c) 2017 Aramis Hornung Moraes
For usage and permissions, please read amh_list.*'s files
*/

#include "ahm_list.h"
#include <stdlib.h>
#include <stdio.h> // printf
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

int main()
{
	int i;
	ahm_list *list = ahm_allocate_list();

	for(i = 0; i < 3; i++)
		ahm_insert_last_list(list, (void*)i);

	ahm_insert_firts_list(list, (void*)-2);
	ahm_insert_firts_list(list, (void*)-1);
	ahm_insert_last_list(list, (void*)-2);
	ahm_insert_last_list(list, (void*)-1);

	ahm_insert_indexed_list(list, 6, (void*)-111);
	printf("\nI've removed %d\n", (int)ahm_remove_indexed_list(list, 1));
	ahm_print_int_list(list);

	ahm_free_list(list);

	//_CrtDumpMemoryLeaks();
	fflush(stdin);
	getchar();
	return 0;
}
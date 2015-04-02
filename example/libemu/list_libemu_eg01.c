#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emu/emu_list.h"

void emut_show_lroot(struct emu_list_root *elr)
{
    printf("lroot    : %p\n",elr);
    printf("head.next: %p\n",elr->head.next);
	printf("head.prev: %p\n",elr->head.prev);
	printf("tail.next: %p\n",elr->tail.next);
	printf("tail.prev: %p\n",elr->tail.prev);
}

void emut_show_item(struct emu_list_item *litem)
{
    printf("litem         : %p\n",litem);	
    printf("item.data     : %d\n",litem->uint32);
    printf("item.link.next: %p\n",litem->link.next);
	printf("item.link.prev: %p\n",litem->link.prev);
}


/*
emu_shellcode_test


*/
int main()
{
	struct emu_list_root *elr=NULL;
    struct emu_list_item *eli=NULL;	
	
	elr = emu_list_create();
	eli = emu_list_item_create();

	emut_show_lroot(elr);
	
	eli->uint32 = 123;
	emu_list_insert_last(elr, eli);

	printf("insert last: %p\n",eli);
	emut_show_lroot(elr);
	emut_show_item(eli);

	emu_list_destroy(elr);
    return 0;
}

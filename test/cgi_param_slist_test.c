#include <stdio.h>

#include "utils/cgi_slist.h"
#include "utils/cgi_param_slist.h"

static void print(pslist_t *head)
{
	pslist_t *tmp = NULL;
	CGI_SLIST_FOREACH(tmp,head,linker)
	{
		printf("key:\t%s\t\tvalue:\t%s\n",tmp->key,tmp->value);
	}
}

int main()
{
	pslist_t *head = pslist_create("Hello","Hi");
	print(head);
	printf("\n");

	pslist_insert_head(&head,pslist_create("A","B"));
	print(head);
	printf("\n");

	pslist_insert_head(&head,pslist_create("C","D"));
	print(head);
	printf("\n");

	pslist_insert_head(&head,pslist_create("E","F"));
	print(head);
	printf("\n");

	pslist_insert_head(&head,pslist_create("G","H"));
	print(head);
	printf("\n");

	while(!pslist_is_empty(head))
	{
		pslist_remove_head(&head);
		print(head);
		putchar('\n');
	}

	pslist_destroy(&head);
	return 0;
}

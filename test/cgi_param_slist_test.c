#include <stdio.h>

#include "utils/cgi_param_slist.h"

int main()
{
	pslist_t *head = pslist_create("Hello","Hi");
	pslist_t *tmp = NULL;
	CGI_SLIST_FOREACH(tmp,head,linker)
	{
		printf("key:\t%s\nvalue:\t%s\n",tmp->key,tmp->value);
	}
	pslist_destroy(&head);
	return 0;
}

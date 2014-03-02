#include <stdlib.h>

#include "cgi.h"
#include "factory/cgi_factory.h"
#include "utils/cgi_slist.h"
#include "utils/cgi_param_slist.h"

pslist_t* pslist_create(char *key,char *value)
{
	pslist_t *param = factory_create(PARAM_SLIST);

	param->key = key;
	param->value = value;
	CGI_SLIST_INIT(param,linker);

	return param;
}

void pslist_insert_head(pslist_t **head_ptr,pslist_t *elem)
{
	if(*head_ptr != elem)
	{
		CGI_SLIST_INSERT_HEAD(*head_ptr,elem,linker);
	}
}

void pslist_remove_head(pslist_t **head_ptr)
{
	if(!CGI_SLIST_IS_EMPTY(*head_ptr))
	{
		pslist_t *head = *head_ptr;
		CGI_SLIST_REMOVE_HEAD(*head_ptr,linker);
		pslist_delete(head);
	}
}

void pslist_delete(pslist_t *elem)
{
	factory_destroy(elem,PARAM_SLIST);
}

void pslist_destroy(pslist_t **head_ptr)
{
	if(CGI_SLIST_IS_EMPTY(*head_ptr))
	{
		pslist_t *head = *head_ptr;
		pslist_destroy(&CGI_SLIST_NEXT(head,linker));
		pslist_delete(head);
	}
}

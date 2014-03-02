#include <stdlib.h>

#include "cgi.h"
#include "factory/cgi_factory.h"

void* factory_create(CGI_OBJECT item)
{
	void *object = NULL;

	switch(item)
	{
	case PARAM_SLIST:
		object = (pslist_t*)malloc(sizeof(pslist_t));
		break;
	default:
		break;
	}

	return object;
}

void factory_destroy(void *object,CGI_OBJECT item)
{
	free(object);
}

#include <stdlib.h>

#include "cgi.h"
#include "factory/cgi_factory.h"

void* cgi_factory_create(CGI_OBJECT item)
{
	void *object = NULL;

	switch(item)
	{
	case PARAM_SLIST:
		object = (cgi_pslist_t*)malloc(sizeof(cgi_pslist_t));
		break;
	default:
		break;
	}

	return object;
}

void cgi_factory_destroy(void *object,CGI_OBJECT item)
{
	free(object);
}

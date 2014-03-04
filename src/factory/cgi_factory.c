#include <stdlib.h>

#include "cgi.h"
#include "factory/cgi_factory.h"

void* cgi_factory_create(CGI_OBJECT item)
{
	void *object = NULL;
	cgi_http_connection_t *connection = NULL;

	switch(item)
	{
	case PARAM_SLIST:
		object = (cgi_pslist_t*)malloc(sizeof(cgi_pslist_t));
		break;

	case HTTP_CONNECTION:
		connection = (cgi_http_connection_t*)malloc(sizeof(cgi_http_connection_t));
		connection->rbuffer = (char*)malloc(sizeof(char) * 
			CGI_HTTP_CONNECTION_READ_BUFFER_SIZE);
		connection->wbuffer = (char*)malloc(sizeof(char) * 
			CGI_HTTP_CONNECTION_WRITE_BUFFER_SIZE);
		connection->rsize = CGI_HTTP_CONNECTION_READ_BUFFER_SIZE;
		connection->wsize = CGI_HTTP_CONNECTION_WRITE_BUFFER_SIZE;
		object = connection;
		break;

	default:
		break;
	}

	return object;
}

void cgi_factory_destroy(void *object,CGI_OBJECT item)
{
	if(item == HTTP_CONNECTION)
	{
		cgi_http_connection_t *connection = (cgi_http_connection_t*)object;
		free(connection->rbuffer);
		free(connection->wbuffer);
	}
	free(object);
}

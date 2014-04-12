#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "cgi.h"
#include "factory/cgi_factory.h"
#include "http/cgi_http_parser.h"
#include "dispatcher/cgi_event_dispatcher.h"

static HTTP_STATUS cgi_http_parse_method(cgi_http_connection_t *connection);
static HTTP_STATUS cgi_http_parse_version(cgi_http_connection_t *connection);

cgi_http_connection_t* cgi_http_connection_create()
{
	cgi_http_connection_t *connection = (cgi_http_connection_t*)
		cgi_factory_create(HTTP_CONNECTION);
	cgi_http_connection_init(connection);
	return connection;
}

void cgi_http_connection_init(cgi_http_connection_t *connection)
{
	if(connection->rsize == 0)
	{
		connection->rbuffer = NULL;
	}
	if(connection->wsize == 0)
	{
		connection->wbuffer = NULL;
	}
	connection->version = NULL;
	connection->url = NULL;
	connection->cookie = NULL;
	connection->content = NULL;
	connection->head = NULL;
	connection->read_idx = 0;
	connection->write_idx = 0;
	connection->checked_idx = 0;
	connection->start_line_idx = 0;
	connection->content_length = 0;
	connection->linger = 0;
	connection->cstatus = CHECK_REQUEST_LINE;
}

void cgi_http_connection_init4(cgi_http_connection_t *connection,int sockfd,
	struct sockaddr *clientaddr,socklen_t clientlen)
{
	cgi_http_connection_init(connection);
	connection->sockfd = sockfd;
	connection->clientlen = clientlen;
	memcpy(&connection->clientaddr,clientaddr,clientlen);
}

void cgi_http_connection_read(cgi_http_connection_t *connection)
{
	int rd = 0;
	while((rd = read(connection->sockfd,connection->rbuffer,connection->rsize - connection->read_idx)) > 0)
	{
		connection->read_idx += rd;
	}
}

void cgi_http_connection_write(cgi_http_connection_t *connection,
	cgi_event_dispatcher_t *dispatcher)
{
	write(connection->sockfd,connection->rbuffer,connection->read_idx);
	if(connection->linger)
	{
		cgi_http_connection_init(connection);
		cgi_event_dispatcher_modfd(dispatcher,connection->sockfd,EPOLLIN);
	}
	else
	{
		close(connection->sockfd);
	}
}

LINE_STATUS cgi_http_parse_line(cgi_http_connection_t *connection)
{
	uint32_t checked_idx = connection->start_line_idx;
	char *rbuffer = connection->rbuffer;
	LINE_STATUS lstatus;

	for( ; checked_idx < connection->read_idx; ++checked_idx)
	{
		if(rbuffer[checked_idx] == '\r')
		{
			if(rbuffer[checked_idx + 1] == '\n')
			{
				rbuffer[checked_idx++] = '\0';
				rbuffer[checked_idx++] = '\0';
				lstatus = LINE_OK;
			}
			else if(checked_idx + 1 == connection->read_idx)
			{
				lstatus = LINE_OPEN;
			}
			else
			{
				lstatus = LINE_BAD;
			}
			break;
		}
		else if(rbuffer[checked_idx] == '\n')
		{
			lstatus = LINE_BAD;
			break;
		}
	}

	connection->checked_idx = checked_idx;
	return lstatus;
}

HTTP_STATUS cgi_http_parse_request_line(cgi_http_connection_t *connection)
{
	char *rbuffer = connection->rbuffer;
	uint32_t checked_idx = connection->checked_idx;
	connection->start_line_idx = checked_idx;

	char *url = strpbrk(rbuffer," \t");
	if(url == NULL)
	{
		return BAD_REQUEST;
	}
	*url++ = '\0';

	if(cgi_http_parse_method(connection) == BAD_REQUEST)
	{
		return BAD_REQUEST;
	}

	url += strspn(url," \t");
	if(*url != '/')
	{
		return BAD_REQUEST;
	}
	connection->url = url;

	char *version = strpbrk(url," \t");
	if(version == NULL)
	{
		return BAD_REQUEST;
	}
	*version++ = '\0';
	version += strspn(version," \t");
	connection->version = version;
	connection->cstatus = CHECK_HEADER;
	return cgi_http_parse_version(connection);
}

HTTP_STATUS cgi_http_parse_method(cgi_http_connection_t *connection)
{
	char *rbuffer = connection->rbuffer;
	if(strncasecmp(rbuffer,"GET",3) == 0)
	{
		connection->method = GET;
		return CHECKING;
	}
	if(strncasecmp(rbuffer,"POST",4) == 0)
	{
		connection->method = POST;
		return CHECKING;
	}
	if(strncasecmp(rbuffer,"HEAD",4) == 0)
	{
		connection->method = HEAD;
		return CHECKING;
	}
	if(strncasecmp(rbuffer,"PUT",3) == 0)
	{
		connection->method = PUT;
		return CHECKING;
	}
	if(strncasecmp(rbuffer,"DELETE",6) == 0)
	{
		connection->method = DELETE;
		return CHECKING;
	}
	if(strncasecmp(rbuffer,"TRACE",5) == 0)
	{
		connection->method = TRACE;
		return CHECKING;
	}
	if(strncasecmp(rbuffer,"OPTIONS",7) == 0)
	{
		connection->method = OPTIONS;
		return CHECKING;
	}
	if(strncasecmp(rbuffer,"CONNECT",7) == 0)
	{
		connection->method = CONNECT;
		return CHECKING;
	}
	if(strncasecmp(rbuffer,"PATCH",5) == 0)
	{
		connection->method = PATCH;
		return CHECKING;
	}
	return BAD_REQUEST;
}

HTTP_STATUS cgi_http_parse_version(cgi_http_connection_t *connection)
{
	HTTP_STATUS hstatus;
	if(strcmp(connection->version,"HTTP/1.1") == 0)
	{
		hstatus = CHECKING;
	}
	else if(strcmp(connection->version,"HTTP/1.0") == 0)
	{
		hstatus = HTTP_VERSION_NOT_SUPPORTED;
	}
	else
	{
		hstatus = BAD_REQUEST;
	}
	return hstatus;
}

HTTP_STATUS cgi_http_parse_header(cgi_http_connection_t *connection)
{
	char *current = connection->rbuffer + connection->start_line_idx;
	connection->start_line_idx = connection->checked_idx;

	if(*current == '\0')
	{
		connection->cstatus = CHECK_CONTENT;
	}
	else if(strncasecmp(current,"Connection:",11) == 0)
	{
		current += 11;
		current += strspn(current," \t");
		if(strncasecmp(current,"keep-live",9) == 0)
		{
			connection->linger = 1;
		}
	}
	else if(strncasecmp(current,"Content-Length:",15) == 0)
	{
		current += 15;
		current += strspn(current," \t");
		connection->content_length = atol(current);
	}
	else if(strncasecmp(current,"Cookie:",7) ==0)
	{
		current += 7;
		current += strspn(current," \t");
		connection->cookie = current;
	}
	else
	{
		printf("%s\n",current);
	}
	return CHECKING;
}

HTTP_STATUS cgi_http_parse_content(cgi_http_connection_t *connection)
{
	connection->content = connection->rbuffer + connection->start_line_idx;
	if(connection->read_idx >= connection->content_length + connection->start_line_idx)
	{
		connection->content[connection->content_length] = '\0';
		return OK;
	}
	return CHECKING;
}

HTTP_STATUS cgi_http_process_read(cgi_http_connection_t *connection)
{
	LINE_STATUS lstatus;
	HTTP_STATUS hstatus = CHECKING;
	while(hstatus == CHECKING)
	{
		if(connection->cstatus != CHECK_CONTENT)
		{
			lstatus = cgi_http_parse_line(connection);
		}
		if(lstatus == LINE_BAD)
		{
			hstatus = BAD_REQUEST;
			break;
		}
		else if(lstatus == LINE_OPEN)
		{
			break;
		}

		switch(connection->cstatus)
		{
		case CHECK_REQUEST_LINE:
			hstatus = cgi_http_parse_request_line(connection);
			break;

		case CHECK_HEADER:
			hstatus = cgi_http_parse_header(connection);
			break;

		case CHECK_CONTENT:
			if(connection->content_length == 0)
			{
				hstatus = OK;
				break;
			}
			hstatus = cgi_http_parse_content(connection);
			break;

		default:
			break;
		}
	}
	return hstatus;
}

HTTP_STATUS cgi_http_process_write(cgi_http_connection_t *connection)
{
}

void cgi_http_write_request_line(cgi_http_connection_t *connection,HTTP_STATUS hstatus)
{
	char *status = NULL;
	switch(hstatus)
	{
	case OK:
		status = "200 OK";
		break;

	case FOUND:
		status = "302 Found";
		break;

	case NOT_MODIFIED:
		status = "304 Modified";
		break;

	case BAD_REQUEST:
		status = "400 Bad Request";
		break;

	case FORBIDDEN:
		status = "403 Forbidden";
		break;

	case NOT_FOUND:
		status = "404 Not Found";
		break;

	case INTERNAL_SERVER_ERROR:
		status = "500 Internal Server Error";
		break;

	case HTTP_VERSION_NOT_SUPPORTED:
		status = "505 HTTP Version Not Supported";
		break;

	default:
		break;
	}
	connection->write_idx += snprintf(connection->wbuffer,connection->wsize,
		"%s %s\r\n",connection->version,status);
}

void cgi_http_parse_param(cgi_http_connection_t *connection)
{
	char *src = NULL;
	if(connection->method == GET)
	{
		src = strpbrk(connection->url,"?");
		if(src != NULL)
		{
			*src++ = '\0';
		}
	}
	else
	{
		src = connection->content;
	}
	if(src != NULL)
	{
		char *key = NULL;
		char *value = NULL;
		while(1)
		{
			key = src;
			src = strpbrk(src,"=");
			*src++ = '\0';

			value = src;
			cgi_pslist_insert_head(&connection->head,
				cgi_pslist_create(key,value));
			if((src = strpbrk(src,"&")) != NULL)
			{
				*src++ = '\0';
			}
			else
			{
				break;
			}
		}
	}
}

void cgi_http_connection_destroy(cgi_http_connection_t *connection)
{
	cgi_factory_destroy(connection,HTTP_CONNECTION);
}

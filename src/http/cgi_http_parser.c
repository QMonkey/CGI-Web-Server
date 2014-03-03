#include <stdint.h>
#include <string.h>

#include "cgi.h"
#include "http/cgi_http_parser.h"

static HTTP_STATUS cgi_http_parse_method(cgi_http_connection_t *connection);
static HTTP_STATUS cgi_http_parse_version(cgi_http_connection_t *connection);

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

LINE_STATUS cgi_http_parse_line(cgi_http_connection_t *connection)
{
	uint32_t checked_idx = connection->start_line_idx;
	char *rbuffer = connection->rbuffer;
	LINE_STATUS lstatus;

	for( ; checked_idx < read_idx; ++checked_idx)
	{
		if(rbuffer[checked_idx] == '\r')
		{
			if(rbuffer[checked_idx + 1] == '\n')
			{
				rbuffer[checked_idx++] = '\0';
				rbuffer[checked_idx++] = '\0';
				lstatus = LINE_OK;
			}
			else if(checked_idx + 1 == read_idx)
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

	connection->checked_idx = chekced_idx;
	return lstatus;
}

HTTP_STATUS cgi_http_parse_request_line(cgi_http_connection_t *connection)
{
	char *rbuffer = connection->rbuffer;
	uint32_t checked_idx = connection->checked_idx;
	char *line_end = rbuffer + checked_idx;
	connection->start_line_idx = checked_idx;
	char *path = strpbrk(rbuffer," \t");

	if(path == NULL || path >= line_end)
	{
		return BAD_REQUEST;
	}
	*path++ = '\0';
}

HTTP_STATUS cgi_http_parse_method(cgi_http_connection_t *connection)
{
}

HTTP_STATUS cgi_http_parse_version(cgi_http_connection_t *connection)
{
}

HTTP_STATUS cgi_http_parse_header(cgi_http_connection_t *connection)
{
}

HTTP_STATUS cgi_http_parse_content(cgi_http_connection_t *connection)
{
}

HTTP_STATUS cgi_http_process_read(cgi_http_connection_t *connection)
{
}

HTTP_STATUS cgi_http_process_write(cgi_http_connection_t *connection)
{
}

void cgi_http_write_request_line(cgi_http_connection_t *connection,HTTP_STATUS hstatus)
{
}

void cgi_http_parse_param(cgi_http_connection_t *connection)
{
}

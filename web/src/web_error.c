#include "cgi.h"
#include "http/cgi_http_parser.h"

#include "web.h"

void do_response(cgi_http_connection_t *connection)
{
	cgi_http_write_request_line(connection, NOT_FOUND);
	cgi_http_write_file(connection, "public/html/error.html");
}

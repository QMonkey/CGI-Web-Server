#include "cgi.h"
#include "http/cgi_http_parser.h"

#include "web_favicon.h"

void do_response(cgi_http_connection_t *connection)
{
	cgi_http_write_request_line(connection, OK);
	cgi_http_write_file(connection, "public/yxh_thinking.ico");
}

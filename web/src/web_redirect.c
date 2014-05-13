#include "cgi.h"
#include "http/cgi_http_parser.h"
#include "utils/cgi_url_dltrie.h"

#include "web_redirect.h"

void do_response(cgi_http_connection_t *connection)
{
	cgi_url_dltrie_t *url_dltrie = cgi_url_dltrie_default_root();
	cgi_url_dltrie_find(url_dltrie, "/")(connection);
}

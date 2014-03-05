#include <stdio.h>

#include "cgi.h"
#include "utils/cgi_url_dltrie.h"

static void function_handler(cgi_http_connection_t *connection)
{
	printf("callback\n");
}

int main()
{
	char *url = "/public/hello/hi/how/are/you/index.html";
	cgi_url_dltrie_t *url_trie = cgi_url_dltrie_create();
	cgi_url_dltrie_insert(&url_trie,url,function_handler);
	cgi_handler_t handler = cgi_url_dltrie_find(url_trie,url);
	handler(NULL);

	return 0;
}

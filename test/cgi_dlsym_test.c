#include <stdio.h>
#include <assert.h>

#include "cgi.h"
#include "utils/cgi_dlsym.h"

int main()
{
	void *dlhandle = cgi_dlsym_open("web_error");
	assert(dlhandle != NULL);
	cgi_handler_t handler = cgi_dlsym_get_handler(dlhandle, "do_response");
	handler(NULL);
	cgi_dlsym_close(dlhandle);

	dlhandle = cgi_dlsym_open("web_index");
	assert(dlhandle != NULL);
	handler = cgi_dlsym_get_handler(dlhandle, "do_response");
	handler(NULL);
	cgi_dlsym_close(dlhandle);

	return 0;
}

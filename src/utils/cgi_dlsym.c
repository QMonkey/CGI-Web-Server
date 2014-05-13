#include <stdio.h>
#include <dlfcn.h>

#include "cgi.h"

void* cgi_dlsym_open(char *dlname)
{
	char fpath[CGI_NAME_BUFFER_SIZE];
	snprintf(fpath, CGI_NAME_BUFFER_SIZE - 1, "%slib%s.so", CGI_WEB_DLPATH, dlname); 
	void *dlhandle = dlopen(fpath, RTLD_LAZY);
	if(dlhandle == NULL)
	{
		fprintf(stderr, "%s\n", dlerror());
	}
	return dlhandle;
}

cgi_handler_t cgi_dlsym_get_handler(char *dlhandle,char *hdname)
{
	cgi_handler_t handler = NULL;
	char *errmsg = NULL;
	handler = (cgi_handler_t)dlsym(dlhandle, hdname);
	if((errmsg = dlerror()) != NULL)
	{
		handler = NULL;
		fprintf(stderr, "%s\n", errmsg);
	}

	return handler;
}

void cgi_dlsym_close(char *dlhandle)
{
	if(dlclose(dlhandle))
	{
		fprintf(stderr, "%s\n", dlerror());
	}
}

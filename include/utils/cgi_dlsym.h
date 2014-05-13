#ifndef CGI_DLSYM_H
#define CGI_DLSYM_H

#include "cgi.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern void* cgi_dlsym_open(char *dlname);
extern cgi_handler_t cgi_dlsym_get_handler(void *dlhandle, char *hdname);
extern void cgi_dlsym_close(char *dlhanlde);

#ifdef __cplusplus
}
#endif

#endif

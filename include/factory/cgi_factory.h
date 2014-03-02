#ifndef CGI_FACTORY_H
#define CGI_FACTORY_H

#include "cgi.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern void* cgi_factory_create(CGI_OBJECT item);
extern void cgi_factory_destroy(void *object,CGI_OBJECT item);

#ifdef __cplusplus
}
#endif

#endif

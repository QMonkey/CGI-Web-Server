#ifndef CGI_FACTORY_H
#define CGI_FACTORY_H

#include "cgi.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern void* factory_create(CGI_OBJECT item);
extern void factory_destroy(void *object,CGI_OBJECT item);

#ifdef __cplusplus
}
#endif

#endif

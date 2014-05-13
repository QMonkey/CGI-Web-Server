#ifndef WEB_REDIRECT_H
#define WEB_REDIRECT_H

#include "cgi.h"

#ifdef __cplusplus
extern "C"
{
#endif

void do_response(cgi_http_connection_t *connection);

#ifdef __cplusplus
}
#endif

#endif

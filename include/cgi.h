#ifndef CGI_H
#define CGI_H

#include "utils/cgi_slist.h"

typedef struct param_slist pslist_t;

typedef enum CGI_OBJECT
{
	PARAM_SLIST
} CGI_OBJECT;

struct param_slist
{
	char *key;
	char *value;
	CGI_SLIST_ENTRY(pslist_t) linker;
};

#endif

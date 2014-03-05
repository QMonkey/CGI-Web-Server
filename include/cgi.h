#ifndef CGI_H
#define CGI_H

#include <stdint.h>

#include "utils/cgi_slist.h"
#include "utils/cgi_dltrie.h"

#define CGI_HTTP_CONNECTION_READ_BUFFER_SIZE 1024
#define CGI_HTTP_CONNECTION_WRITE_BUFFER_SIZE 1024
#define CGI_URL_DLTRIE_KEY_SIZE 32

typedef enum CGI_OBJECT CGI_OBJECT;
typedef enum LINE_STATUS LINE_STATUS;
typedef enum CHECK_STATUS CHECK_STATUS;
typedef enum HTTP_STATUS HTTP_STATUS;
typedef enum HTTP_METHOD HTTP_METHOD;

typedef struct cgi_http_connection cgi_http_connection_t;
typedef struct cgi_param_slist cgi_pslist_t;
typedef struct cgi_url_dltrie cgi_url_dltrie_t;

typedef void (*cgi_handler_t)(cgi_http_connection_t*);

enum CGI_OBJECT
{
	HTTP_CONNECTION,
	PARAM_SLIST,
	URL_DLTRIE
};

enum LINE_STATUS
{
	LINE_OPEN,
	LINE_OK,
	LINE_BAD
};

enum CHECK_STATUS
{
	CHECK_REQUEST_LINE,
	CHECK_HEADER,
	CHECK_CONTENT
};

enum HTTP_STATUS
{
	CHECKING,
	OK,
	FOUND,
	NOT_MODIFIED,
	BAD_REQUEST,
	FORBIDDEN,
	NOT_FOUND,
	INTERNAL_SERVER_ERROR,
	HTTP_VERSION_NOT_SUPPORTED
};

enum HTTP_METHOD
{
	GET,
	POST,
	HEAD,
	PUT,
	DELETE,
	TRACE,
	OPTIONS,
	CONNECT,
	PATCH
};

struct cgi_http_connection
{
	char *rbuffer;
	char *wbuffer;
	char *version;
	char *url;
	char *cookie;
	char *content;
	cgi_pslist_t *head;
	uint32_t rsize;
	uint32_t wsize;	
	uint32_t read_idx;
	uint32_t write_idx;
	uint32_t checked_idx;
	uint32_t start_line_idx;
	uint32_t content_length;
	int linger;
	HTTP_METHOD method;
	CHECK_STATUS cstatus;
};

struct cgi_param_slist
{
	char *key;
	char *value;
	CGI_SLIST_ENTRY(cgi_pslist_t) linker;
};

struct cgi_url_dltrie
{
	char *key;
	cgi_handler_t handler;
	uint32_t ksize;
	CGI_DLTRIE_ENTRY(cgi_url_dltrie_t) linker;
};

#endif

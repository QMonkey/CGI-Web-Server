#ifndef CGI_PARAM_SLIST_H
#define CGI_PARAM_SLIST_H

#include "cgi.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern pslist_t* cgi_pslist_create(char *key,char *value);
extern int cgi_pslist_is_empty(pslist_t *head);
extern void cgi_pslist_insert_head(pslist_t **head_ptr,pslist_t *elem);
extern void cgi_pslist_remove_head(pslist_t **head_ptr);
extern char* cgi_pslist_find(pslist_t *head,char *key);
extern void cgi_pslist_delete(pslist_t *elem);
extern void cgi_pslist_destroy(pslist_t **head_ptr);

#ifdef __cplusplus
}
#endif

#endif

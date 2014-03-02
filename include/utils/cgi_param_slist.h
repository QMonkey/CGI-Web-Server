#ifndef CGI_PARAM_SLIST_H
#define CGI_PARAM_SLIST_H

#include "cgi.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern pslist_t* pslist_create(char *key,char *value);
extern int pslist_is_empty(pslist_t *head);
extern void pslist_insert_head(pslist_t **head_ptr,pslist_t *elem);
extern void pslist_remove_head(pslist_t **head_ptr);
extern char* pslist_find(pslist_t *head,char *key);
extern void pslist_delete(pslist_t *elem);
extern void pslist_destroy(pslist_t **head_ptr);

#ifdef __cplusplus
}
#endif

#endif

#ifndef CGI_PARAM_SLIST_H
#define CGI_PARAM_SLIST_H

typedef struct param_slist pslist_t;

#ifdef __cplusplus
extern "C"
{
#endif

extern pslist_t* pslist_create(char *key,char *value);
extern void pslist_insert_head(pslist_t **head_ptr,pslist_t *elem);
extern void pslist_remove_head(pslist_t **head_ptr);
extern void pslist_delete(pslist_t *elem);
extern void pslist_destroy(pslist_t **head_ptr);

#ifdef __cplusplus
}
#endif

#endif

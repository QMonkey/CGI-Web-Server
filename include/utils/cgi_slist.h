#ifndef CGI_SLIST_H
#define CGI_SLIST_H

#define CGI_SLIST_ENTRY(type)	struct						\
				{						\
					struct type *next;			\
				}

#define CGI_SLIST_FIRST(head)		(head)
#define CGI_SLIST_NEXT(elem,field)	(elem0>field.next)
#define CGI_SLIST_END(head)		NULL
#define CGI_SLIST_IS_EMPTY(head)	(CGI_SLIST_FIRST(head) == CGI_SLIST_END(head))

#define CGI_SLIST_INSERT_HEAD(head,elem,field)					\
	do									\
	{									\
		(elem)->field.next = (head);					\
		(head) = (elem);						\
	}									\
	while(0)

#define CGI_SLIST_INSERT_AFTER(elemo,elemt,field)				\
	do									\
	{									\
		(elemt)->field.next = (elemo)->field.next;			\
		(elemo)->field.next = (elemt);					\
	}									\
	while(0)

#define CGI_SLIST_REOMVE_HEAD(head,field)					\
	do									\
	{									\
		(head) = (head)->field.next;					\
	}									\
	while(0)

#define CGI_SLIST_REMOVE(type,head,elem,field)					\
	do									\
	{									\
		if(head == elem)						\
		{								\
			CGI_SLIST_REMOVE_HEAD(head,field);			\
		}								\
		else								\
		{								\
			struct type *ptr = (head);				\
			while(ptr->field.next != (elem))			\
			{							\
				ptr = ptr->field.next;				\
			}							\
			ptr->field.next = (elem)->field.next;			\
		}								\
	}									\
	while(0)

#endif

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "cgi.h"
#include "factory/cgi_factory.h"
#include "utils/cgi_url_dltrie.h"

static cgi_url_dltrie_t *url_trie = NULL;

static char* cgi_url_strpbrk(char *url);

cgi_url_dltrie_t* cgi_url_dltrie_create()
{
	cgi_url_dltrie_t *elem = cgi_factory_create(URL_DLTRIE);
	elem->handler = NULL;
	return elem;
}

char* cgi_url_strpbrk(char *url)
{
	char *scanner = url;
	while(*scanner != '/' && *scanner != '\0')
	{
		++scanner;
	}
	if(*scanner == '/')
	{
		++scanner;
	}
	return scanner;
}

void cgi_url_dltrie_insert(cgi_url_dltrie_t **head_ptr,char *url,
	cgi_handler_t handler)
{
	if(head_ptr == NULL || url == NULL || *url == '\0')
	{
		return;
	}

	char *scanner = NULL;
	cgi_url_dltrie_t *head = NULL;
	uint32_t diff;
	while(1)
	{
		scanner = cgi_url_strpbrk(url);
		head = *head_ptr;
		diff = scanner - url;
		if(head == NULL)
		{
			*head_ptr = cgi_url_dltrie_create();
			head = *head_ptr;
			snprintf(head->key,diff + 1,"%s",url);
		}
		else if(memcmp(head->key,url,diff))
		{
			head_ptr = &CGI_DLTRIE_SIBLING(head,linker);
			continue;
		}
		if(*scanner == '\0')
		{
			head->handler = handler;
			break;
		}
		head_ptr = &CGI_DLTRIE_CHILD(head,linker);
		url = scanner;
	}
}

cgi_handler_t cgi_url_dltrie_find(cgi_url_dltrie_t *head,char *url)
{
	char *scanner = NULL;
	uint32_t diff;
	cgi_handler_t handler = NULL;
	while(1)
	{
		scanner = cgi_url_strpbrk(url);
		diff = scanner - url;
		if(head == NULL || url == NULL || *url == '\0')
		{
			break;
		}
		if(memcmp(head->key,url,diff))
		{
			head = CGI_DLTRIE_SIBLING(head,linker);
			continue;
		}
		if(*scanner == '\0')
		{
			handler = head->handler;
			break;
		}
		head = CGI_DLTRIE_CHILD(head,linker);
		url = scanner;
	}
	return handler;
}

void cgi_url_dltrie_delete(cgi_url_dltrie_t *elem)
{
	cgi_factory_destroy(elem,URL_DLTRIE);
}

void cgi_url_dltrie_destroy(cgi_url_dltrie_t **head_ptr)
{
}

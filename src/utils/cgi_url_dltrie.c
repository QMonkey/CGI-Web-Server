#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "cgi.h"
#include "factory/cgi_factory.h"
#include "utils/cgi_dlsym.h"
#include "utils/cgi_url_dltrie.h"

static cgi_url_dltrie_t *url_trie = NULL;

static char* cgi_url_strpbrk(char *url);

cgi_url_dltrie_t* cgi_url_dltrie_create()
{
	cgi_url_dltrie_t *elem = cgi_factory_create(URL_DLTRIE);
	elem->handler = NULL;
	elem->dlhandle = NULL;
	return elem;
}

cgi_url_dltrie_t* cgi_url_dltrie_default_root()
{
	if(url_trie == NULL)
	{
		cgi_url_dltrie_init(&url_trie);
	}
	return url_trie;
}

void cgi_url_dltrie_init(cgi_url_dltrie_t **head_ptr)
{	
	void *dlhandle = NULL;

	dlhandle = cgi_dlsym_open("web_index");
	cgi_url_dltrie_insert(head_ptr, "/", 
		cgi_dlsym_get_handler(dlhandle, "do_response"), dlhandle);
	cgi_url_dltrie_insert(head_ptr, "/index.html", 
		cgi_dlsym_get_handler(dlhandle, "do_response"), dlhandle);

	dlhandle = cgi_dlsym_open("web_error");
	cgi_url_dltrie_insert(head_ptr, "/error.html", 
		cgi_dlsym_get_handler(dlhandle, "do_response"), dlhandle);

	dlhandle = cgi_dlsym_open("web_signin");
	cgi_url_dltrie_insert(head_ptr, "/signIn.html", 
		cgi_dlsym_get_handler(dlhandle, "do_response"), dlhandle);

	dlhandle = cgi_dlsym_open("web_signup");
	cgi_url_dltrie_insert(head_ptr, "/signUp.html", 
		cgi_dlsym_get_handler(dlhandle, "do_response"), dlhandle);

	dlhandle = cgi_dlsym_open("web_verify_signin");
	cgi_url_dltrie_insert(head_ptr, "/verifySignIn", 
		cgi_dlsym_get_handler(dlhandle, "do_response"), dlhandle);

	dlhandle = cgi_dlsym_open("web_verify_signup");
	cgi_url_dltrie_insert(head_ptr, "/verifySignUp", 
		cgi_dlsym_get_handler(dlhandle, "do_response"), dlhandle);

	dlhandle = cgi_dlsym_open("web_default");
	cgi_url_dltrie_insert(head_ptr, "/favicon.ico", 
		cgi_dlsym_get_handler(dlhandle, "do_response"), dlhandle);
	cgi_url_dltrie_insert(head_ptr, "/css/index.css", 
		cgi_dlsym_get_handler(dlhandle, "do_response"), dlhandle);
	cgi_url_dltrie_insert(head_ptr, "/css/reset.css", 
		cgi_dlsym_get_handler(dlhandle, "do_response"), dlhandle);
	cgi_url_dltrie_insert(head_ptr, "/js/signUp.js", 
		cgi_dlsym_get_handler(dlhandle, "do_response"), dlhandle);
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
	cgi_handler_t handler,void *dlhandle)
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
			head->dlhandle = dlhandle;
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

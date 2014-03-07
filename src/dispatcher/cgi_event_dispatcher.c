#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>

#include "cgi.h"
#include "factory/cgi_factory.h"
#include "http/cgi_http_parser.h"
#include "dispatcher/cgi_event_dispatcher.h"

cgi_event_dispatcher_t* cgi_event_dispatcher_create()
{
	cgi_event_dispatcher_t *dispatcher = cgi_factory_create(EVENT_DISPATCHER);
	dispatcher->timeout = -1;
	return dispatcher;
}

void cgi_event_dispatcher_init(cgi_event_dispatcher_t *dispatcher,int epfd,int listenfd,int timeout)
{
	dispatcher->epfd = epfd;
	dispatcher->listenfd = listenfd;
	dispatcher->timeout = timeout;
}

void cgi_event_dispatcher_addfd(cgi_event_dispatcher_t *dispatcher,int fd,int in,int oneshot)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLET | EPOLLRDHUP;
	if(in)
	{
		event.events |= EPOLLIN;
	}
	else
	{
		event.events |= EPOLLOUT;
	}
	if(oneshot)
	{
		event.events |= EPOLLONESHOT;
	}
	epoll_ctl(dispatcher->epfd,EPOLL_CTL_ADD,fd,&event);
	cgi_event_dispatcher_set_nonblocking(fd);
}

void cgi_event_dispatcher_rmfd(cgi_event_dispatcher_t *dispatcher,int fd)
{
	epoll_ctl(dispatcher->epfd,EPOLL_CTL_DEL,fd,NULL);
}

void cgi_event_dispatcher_modfd(cgi_event_dispatcher_t *dispatcher,int fd,int ev)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events = ev | EPOLLET | EPOLLRDHUP | EPOLLONESHOT;
	epoll_ctl(dispatcher->epfd,EPOLL_CTL_MOD,fd,&event);
}

void cgi_event_dispatcher_set_nonblocking(int fd)
{
	int fsflags = fcntl(fd,F_GETFL);
	fsflags |= O_NONBLOCK;
	fcntl(fd,F_SETFL,fsflags);
}

void cgi_event_dispatcher_loop(cgi_event_dispatcher_t *dispatcher)
{
	int stop = 0;
	int nfds;
	int i;
	int tmpfd;
	int cfd;
	struct epoll_event event;
	struct sockaddr clientaddr;
	socklen_t clientlen;
	cgi_http_connection_t *client_connection = NULL;
	while(!stop)
	{
		nfds = epoll_wait(dispatcher->epfd,dispatcher->events,
			dispatcher->evsize,dispatcher->timeout);
		for(i = 0; i < nfds; ++i)
		{
			event = dispatcher->events[i];
			tmpfd = event.data.fd;
			if(dispatcher->listenfd == tmpfd)
			{
				cfd = accept(tmpfd,&clientaddr,&clientlen);
				cgi_event_dispatcher_addfd(dispatcher,cfd,1,1);
				client_connection = dispatcher->connections + cfd;
				cgi_http_connection_init4(client_connection,cfd,&clientaddr,clientlen);
			}
			else if(event.events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
			{
				cgi_event_dispatcher_rmfd(dispatcher,tmpfd);
			}
			else if(event.events & EPOLLIN)
			{
			}
			else if(event.events & EPOLLOUT)
			{
			}
			else
			{
			}
		}
	}
}

void cgi_event_dispatcher_destroy(cgi_event_dispatcher_t *dispatcher)
{
	cgi_factory_destroy(dispatcher,EVENT_DISPATCHER);
}

#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "cgi.h"
#include "factory/cgi_factory.h"
#include "dispatcher/cgi_event_dispatcher.h"

cgi_event_dispatcher_t* cgi_event_dispatcher_create(int epfd,int listenfd,int timeout)
{
	cgi_event_dispatcher_t *dispatcher = cgi_factory_create(EVENT_DISPATCHER);
	dispatcher->epfd = epfd;
	dispatcher->listenfd = listenfd;
	dispatcher->timeout = timeout;
	return dispatcher;
}

void cgi_event_dispatcher_set_epfd(cgi_event_dispatcher_t *dispatcher,int epfd)
{
	dispatcher->epfd = epfd;
}

void cgi_event_dispatcher_set_listenfd(cgi_event_dispatcher_t *dispatcher,int listenfd)
{
	dispatcher->listenfd = listenfd;
}

void cgi_event_dispatcher_addfd(cgi_event_dispatcher_t *dispatcher,int fd,int in,int oneshot)
{
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLET | EPOLLRDHUP | EPOLLONESHOT;
	if(in)
	{
		event.events |= EPOLLIN;
	}
	else
	{
		event.events |= EPOLLOUT;
	}
	epoll_ctl(dispatcher->epfd,EPOLL_CTL_ADD,fd,&event);
	cgi_event_dispatcher_set_nonblocking(fd);
}

void cgi_event_dispatcher_rmfd(cgi_event_dispatcher_t *dispatcher,int fd)
{
	epoll_ctl(dispatcher->epfd,EPOLL_CTL_DEL,fd,NULL);
	close(fd);
}

void cgi_event_dispatcher_modfd(cgi_event_dispatcher_t *dispatcher,int fd,int ev)
{
	epoll_event event;
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
	int stop = false;
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
				client_connection = dispatcher->connections[cfd];
				cgi_http_connection_init(cfd,client_connection,&clientaddr,clientlen);
			}
			else if(event & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
			{
				cgi_event_dispatcher_rmfd(dispatcher,tmpfd);
			}
			else if(event & EPOLLIN)
			{
			}
			else if(event & EPOLLOUT)
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

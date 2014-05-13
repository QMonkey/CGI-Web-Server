EXECPATH = bin
OBJPATH = obj
DLPATH = web/lib
CC = gcc

EXEC = $(EXECPATH)/cgi_slist_test $(EXECPATH)/cgi_param_slist_test $(EXECPATH)/cgi_http_parser_test $(EXECPATH)/cgi_url_dltrie_test $(EXECPATH)/cgi_event_dispatcher_test $(EXECPATH)/cgi_thread_pool_test $(EXECPATH)/cgi_task_queue_test $(EXECPATH)/cgi_server_test $(EXECPATH)/cgi_dlsym_test

OBJS = $(OBJPATH)/cgi_factory.o $(OBJPATH)/cgi_http_parser.o $(OBJPATH)/cgi_param_slist.o $(OBJPATH)/cgi_url_dltrie.o $(OBJPATH)/cgi_event_dispatcher.o $(OBJPATH)/cgi_task_queue.o $(OBJPATH)/cgi_thread_pool.o $(OBJPATH)/cgi_dlsym.o

TESTOBJS = $(OBJPATH)/cgi_slist_test.o $(OBJPATH)/cgi_param_slist_test.o $(OBJPATH)/cgi_http_parser_test.o $(OBJPATH)/cgi_url_dltrie_test.o $(OBJPATH)/cgi_event_dispatcher_test.o $(OBJPATH)/cgi_thread_pool_test.o $(OBJPATH)/cgi_task_queue_test.o $(OBJPATH)/cgi_dlsym_test.o

DLLS = $(DLPATH)/libweb_error.so $(DLPATH)/libweb_index.so $(DLPATH)/libweb_default.so $(DLPATH)/libweb_signin.so $(DLPATH)/libweb_signup.so


all: $(OBJS) $(TESTOBJS) $(EXEC) $(DLLS)


$(EXECPATH)/cgi_slist_test: $(OBJPATH)/cgi_slist_test.o
	$(CC) -g $< -o $@

$(EXECPATH)/cgi_param_slist_test: $(OBJPATH)/cgi_param_slist_test.o $(OBJPATH)/cgi_param_slist.o
	$(CC) -g $< -o $@ $(OBJPATH)/cgi_param_slist.o $(OBJPATH)/cgi_factory.o

$(EXECPATH)/cgi_http_parser_test: $(OBJPATH)/cgi_http_parser_test.o
	$(CC) -g $< -o $@ $(OBJPATH)/cgi_factory.o $(OBJPATH)/cgi_http_parser.o $(OBJPATH)/cgi_param_slist.o $(OBJPATH)/cgi_event_dispatcher.o $(OBJPATH)/cgi_thread_pool.o $(OBJPATH)/cgi_task_queue.o $(OBJPATH)/cgi_url_dltrie.o $(OBJPATH)/cgi_dlsym.o -lpthread -ldl

$(EXECPATH)/cgi_url_dltrie_test: $(OBJPATH)/cgi_url_dltrie_test.o
	$(CC) -g $< -o $@ $(OBJPATH)/cgi_url_dltrie.o $(OBJPATH)/cgi_factory.o $(OBJPATH)/cgi_dlsym.o -ldl

$(EXECPATH)/cgi_event_dispatcher_test: $(OBJPATH)/cgi_event_dispatcher_test.o
	$(CC) -g $< -o $@ $(OBJPATH)/cgi_factory.o $(OBJPATH)/cgi_event_dispatcher.o $(OBJPATH)/cgi_http_parser.o $(OBJPATH)/cgi_param_slist.o $(OBJPATH)/cgi_thread_pool.o $(OBJPATH)/cgi_task_queue.o $(OBJPATH)/cgi_url_dltrie.o $(OBJPATH)/cgi_dlsym.o -lpthread -ldl

$(EXECPATH)/cgi_server_test: $(OBJPATH)/cgi_server_test.o
	$(CC) -g $< -o $@ $(OBJPATH)/cgi_factory.o $(OBJPATH)/cgi_event_dispatcher.o $(OBJPATH)/cgi_http_parser.o $(OBJPATH)/cgi_param_slist.o $(OBJPATH)/cgi_thread_pool.o $(OBJPATH)/cgi_task_queue.o $(OBJPATH)/cgi_url_dltrie.o $(OBJPATH)/cgi_dlsym.o -lpthread -ldl

$(EXECPATH)/cgi_thread_pool_test: $(OBJPATH)/cgi_thread_pool_test.o
	$(CC) -g $< -o $@ $(OBJPATH)/cgi_thread_pool.o $(OBJPATH)/cgi_factory.o $(OBJPATH)/cgi_task_queue.o -lpthread

$(EXECPATH)/cgi_task_queue_test: $(OBJPATH)/cgi_task_queue_test.o
	$(CC) -g $< -o $@ $(OBJPATH)/cgi_task_queue.o $(OBJPATH)/cgi_factory.o -lpthread

$(EXECPATH)/cgi_dlsym_test: $(OBJPATH)/cgi_dlsym_test.o
	$(CC) -g $< -o $@ $(OBJPATH)/cgi_dlsym.o -ldl


$(OBJPATH)/cgi_http_parser.o: src/http/cgi_http_parser.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_url_dltrie.o: src/utils/cgi_url_dltrie.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_param_slist.o: src/utils/cgi_param_slist.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_factory.o: src/factory/cgi_factory.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_event_dispatcher.o: src/dispatcher/cgi_event_dispatcher.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_task_queue.o: src/utils/cgi_task_queue.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_thread_pool.o: src/pool/cgi_thread_pool.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_slist_test.o: test/cgi_slist_test.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_param_slist_test.o: test/cgi_param_slist_test.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_http_parser_test.o: test/cgi_http_parser_test.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_url_dltrie_test.o: test/cgi_url_dltrie_test.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_event_dispatcher_test.o: test/cgi_event_dispatcher_test.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_server_test.o: test/cgi_server_test.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_dlsym_test.o: test/cgi_dlsym_test.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_thread_pool_test.o: test/cgi_thread_pool_test.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_task_queue_test.o: test/cgi_task_queue_test.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_dlsym.o: src/utils/cgi_dlsym.c
	$(CC) -g -c $< -I include -o $@

$(DLPATH)/libweb_default.so: web/src/web_default.c
	$(CC) -fPIC -shared -nostartfiles $< src/factory/cgi_factory.c src/utils/cgi_dlsym.c src/utils/cgi_url_dltrie.c src/http/cgi_http_parser.c -I include -I web/include -o $@

$(DLPATH)/libweb_error.so: web/src/web_error.c
	$(CC) -fPIC -shared -nostartfiles $< src/http/cgi_http_parser.c -I include -I web/include -o $@

$(DLPATH)/libweb_index.so: web/src/web_index.c
	$(CC) -fPIC -shared -nostartfiles $< src/http/cgi_http_parser.c -I include -I web/include -o $@

$(DLPATH)/libweb_signin.so: web/src/web_signin.c
	$(CC) -fPIC -shared -nostartfiles $< src/http/cgi_http_parser.c -I include -I web/include -o $@

$(DLPATH)/libweb_signup.so: web/src/web_signup.c
	$(CC) -fPIC -shared -nostartfiles $< src/http/cgi_http_parser.c -I include -I web/include -o $@

clean:
	-rm -rf $(EXEC) $(OBJS) $(TESTOBJS) $(DLLS)

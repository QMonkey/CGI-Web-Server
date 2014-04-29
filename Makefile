EXECPATH = bin
OBJPATH = obj
CC = gcc

EXEC = $(EXECPATH)/cgi_slist_test $(EXECPATH)/cgi_param_slist_test $(EXECPATH)/cgi_http_parser_test $(EXECPATH)/cgi_url_dltrie_test $(EXECPATH)/cgi_event_dispatcher_test $(EXECPATH)/cgi_thread_pool_test $(EXECPATH)/cgi_task_queue_test

OBJS = $(OBJPATH)/cgi_factory.o $(OBJPATH)/cgi_http_parser.o $(OBJPATH)/cgi_object_pool.o $(OBJPATH)/cgi_param_slist.o $(OBJPATH)/cgi_url_dltrie.o $(OBJPATH)/cgi_event_dispatcher.o $(OBJPATH)/cgi_task_queue.o $(OBJPATH)/cgi_thread_pool.o

TESTOBJS = $(OBJPATH)/cgi_slist_test.o $(OBJPATH)/cgi_param_slist_test.o $(OBJPATH)/cgi_http_parser_test.o $(OBJPATH)/cgi_url_dltrie_test.o $(OBJPATH)/cgi_event_dispatcher_test.o $(OBJPATH)/cgi_thread_pool_test.o $(OBJPATH)/cgi_task_queue_test.o


all: $(OBJS) $(TESTOBJS) $(EXEC)


$(EXECPATH)/cgi_slist_test: $(OBJPATH)/cgi_slist_test.o
	$(CC) -g $< -o $@

$(EXECPATH)/cgi_param_slist_test: $(OBJPATH)/cgi_param_slist_test.o $(OBJPATH)/cgi_param_slist.o
	$(CC) -g $< -o $@ $(OBJPATH)/cgi_param_slist.o $(OBJPATH)/cgi_factory.o

$(EXECPATH)/cgi_http_parser_test: $(OBJPATH)/cgi_http_parser_test.o
	$(CC) -g $< -o $@ $(OBJPATH)/cgi_factory.o $(OBJPATH)/cgi_http_parser.o $(OBJPATH)/cgi_param_slist.o $(OBJPATH)/cgi_event_dispatcher.o

$(EXECPATH)/cgi_url_dltrie_test: $(OBJPATH)/cgi_url_dltrie_test.o
	$(CC) -g $< -o $@ $(OBJPATH)/cgi_url_dltrie.o $(OBJPATH)/cgi_factory.o

$(EXECPATH)/cgi_event_dispatcher_test: $(OBJPATH)/cgi_event_dispatcher_test.o
	$(CC) -g $< -o $@ $(OBJPATH)/cgi_factory.o $(OBJPATH)/cgi_event_dispatcher.o $(OBJPATH)/cgi_http_parser.o $(OBJPATH)/cgi_param_slist.o

$(EXECPATH)/cgi_thread_pool_test: $(OBJPATH)/cgi_thread_pool_test.o
	$(CC) -g $< -o $@ $(OBJPATH)/cgi_thread_pool.o $(OBJPATH)/cgi_factory.o $(OBJPATH)/cgi_task_queue.o -lpthread

$(EXECPATH)/cgi_task_queue_test: $(OBJPATH)/cgi_task_queue_test.o
	$(CC) -g $< -o $@ $(OBJPATH)/cgi_task_queue.o $(OBJPATH)/cgi_factory.o -lpthread


$(OBJPATH)/cgi_http_parser.o: src/http/cgi_http_parser.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_url_dltrie.o: src/utils/cgi_url_dltrie.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_object_pool.o: src/object/cgi_object_pool.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_param_slist.o: src/utils/cgi_param_slist.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_factory.o: src/factory/cgi_factory.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_event_dispatcher.o: src/dispatcher/cgi_event_dispatcher.c
	$(CC) -g -c $< -I include -o $@ -lpthread

$(OBJPATH)/cgi_task_queue.o: src/utils/cgi_task_queue.c
	$(CC) -g -c $< -I include -o $@ -lpthread

$(OBJPATH)/cgi_thread_pool.o: src/pool/cgi_thread_pool.c
	$(CC) -g -c $< -I include -o $@ -lpthread

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

$(OBJPATH)/cgi_thread_pool_test.o: test/cgi_thread_pool_test.c
	$(CC) -g -c $< -I include -o $@ -lpthread

$(OBJPATH)/cgi_task_queue_test.o: test/cgi_task_queue_test.c
	$(CC) -g -c $< -I include -o $@ -lpthread

clean:
	-rm -rf $(EXEC) $(OBJS) $(TESTOBJS)

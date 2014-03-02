EXECPATH = bin
OBJPATH = obj
EXEC = $(EXECPATH)/cgi_slist_test $(EXECPATH)/cgi_param_slist_test
OBJS = $(OBJPATH)/cgi_factory.o $(OBJPATH)/cgi_http_parser.o $(OBJPATH)/cgi_object_pool.o $(OBJPATH)/cgi_param_slist.o
TESTOBJS = $(OBJPATH)/cgi_slist_test.o $(OBJPATH)/cgi_param_slist_test.o
CC = gcc

all: $(OBJS) $(TESTOBJS) $(EXEC)

$(EXECPATH)/cgi_slist_test: $(OBJPATH)/cgi_slist_test.o
	$(CC) -g $< -o $@

$(EXECPATH)/cgi_param_slist_test: $(OBJPATH)/cgi_param_slist_test.o $(OBJPATH)/cgi_param_slist.o
	$(CC) -g $< -o $@ $(OBJPATH)/cgi_param_slist.o $(OBJPATH)/cgi_factory.o

$(OBJPATH)/cgi_http_parser.o: src/http/cgi_http_parser.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_object_pool.o: src/object/cgi_object_pool.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_param_slist.o: src/utils/cgi_param_slist.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_factory.o: src/factory/cgi_factory.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_slist_test.o: test/cgi_slist_test.c
	$(CC) -g -c $< -I include -o $@

$(OBJPATH)/cgi_param_slist_test.o: test/cgi_param_slist_test.c
	$(CC) -g -c $< -I include -o $@

clean:
	-rm -rf $(PROG) $(OBJS) $(TESTOBJS)

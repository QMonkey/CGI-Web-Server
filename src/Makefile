OBJECTS = cgi_factory.o cgi_http_parser.o cgi_object_pool.o cgi_param_slist.o
CC = gcc

all: $(OBJECTS)

cgi_http_parser.o: http/cgi_http_parser.c
	$(CC) -g -c $< -I ../include

cgi_object_pool.o: object/cgi_object_pool.c
	$(CC) -g -c $< -I ../include

cgi_param_slist.o: utils/cgi_param_slist.c
	$(CC) -g -c $< -I ../include

cgi_factory.o: factory/cgi_factory.c
	$(CC) -g -c $< -I ../include

clean:
	-rm -rf $(OBJECTS)

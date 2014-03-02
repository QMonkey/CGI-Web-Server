OBJECTS = cgi_http_parser.o
CC = gcc

all: $(OBJECTS)

$(OBJECTS): %.o: %.c
	$(CC) -g -c $< -I ../../include

clean:
	-rm -rf $(OBJECTS)

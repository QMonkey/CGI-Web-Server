OBJECTS = cgi_object_pool.o
CC = gcc

all: $(OBJECTS)

$(OBJECTS): %.o: %.c
	$(CC) -g -c $< -I ../../include

clean:
	-rm -rf $(OBJECTS)

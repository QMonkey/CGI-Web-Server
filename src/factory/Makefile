OBJECTS = cgi_factory.o
CC = gcc

all: $(OBJECTS)

$(OBJECTS): %.o: %.c
	$(CC) -g -c $< -I ../../include

clean:
	-rm -rf $(OBJECTS)

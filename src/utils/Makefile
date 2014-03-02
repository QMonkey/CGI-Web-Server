OBJECTS = cgi_param_slist.o
CC = gcc

all: $(OBJECTS)

$(OBJECTS): %.o: %.c
	$(CC) -g -c $< -I ../../include

clean:
	-rm -rf $(OBJECTS)

PROG = cgi_slist_test
OBJECTS = cgi_slist_test.o
CC = gcc

all: $(PROG)

cgi_slist_test: cgi_slist_test.o
	$(CC) -g -o $@ $<

%.o: %.c
	$(CC) -g -c $< -I ../include

clean:
	-rm -rf $(OBJECTS) $(PROG)

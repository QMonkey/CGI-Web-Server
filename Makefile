PROG = CGI_Web_Server

All: $(PROG)

$(PROG):
	make -C src
	make -C test

clean:
	make clean -C src
	make clean -C test

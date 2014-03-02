OBJECTS = objects.o

all: $(OBJECTS)

$(OBJECTS):
	make -C factory http utils

clean:
	make clean -C factory http utils

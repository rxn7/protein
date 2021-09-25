HDRS = -I include -I src
SRCS = -c src/*.c -c src/core/*.c
OBJS = pn.o pn_core_variables.o 
LIBS = -lGLEW -lglfw
all: compile output clean

compile:
	gcc -fpic $(HDRS) $(SRCS) -std=gnu11

output:
	gcc -o bin/linux/libprotein.so $(LIBS) $(OBJS) -shared -Wl,-soname,libprotein

clean:
	rm *.o
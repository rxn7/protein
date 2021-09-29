HDRS = -I include -I src

SRCS = -c src/*.c

OBJS =  pn.o \
		pn_window.o \
		pn_vars.o \
		pn_log.o \
		pn_input.o \
		pn_init.o \
		pn_camera.o \
		pn_callbacks.o \
		pn_math.o

LIBS = -lGLEW -lglfw

all: compile output clean

compile:
	gcc -fpic $(HDRS) $(SRCS) -std=gnu11

output:
	gcc -o bin/linux/libprotein.so $(LIBS) $(OBJS) -shared -Wl,-soname,libprotein

clean:
	rm *.o
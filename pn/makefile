ifeq ($(OS),Windows_NT) 
    PN_OS := Windows
else
    PN_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

CFLAGS = -std=c11 -Wall -Wextra
HDRS = -I include -I src
SRCS = -c src/*.c
OBJS =  pn.o \
		pn_window.o \
		pn_vars.o \
		pn_log.o \
		pn_input.o \
		pn_init.o \
		pn_callbacks.o \
		pn_math.o \
		pn_util.o \
		pn_render.o \
		pn_shader.o  \
		pn_camera.o \
		pn_transform.o \
		pn_texture.o \
		pn_sys.o

ifeq ($(PN_OS), Windows)
	TARGET = bin/windows/protein.dll
endif

ifeq ($(PN_OS), Linux)
	TARGET = bin/linux/libprotein.so
endif

all: compile output clean

compile:
	gcc -fpic $(HDRS) $(SRCS) $(CFLAGS)

output:
	ar rvs bin/linux/libprotein.a $(OBJS)

clean:
	rm *.o

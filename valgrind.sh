#!/usr/bin/sh

# WARNING: Remeber to disable -O3 and enable -g in pn/makefile!

# Usage: ./valgrind.sh <exec>
# E.g.:  ./valgrind.sh ./examples/sandbox/sandbox

valgrind --tool=memcheck \
		 --leak-check=full \
		 --log-file=valgrind-out.txt \
		 ./$1
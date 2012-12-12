# makefile for the Simple Graphics Utility

P=sgutest
OBJECTS=sgu.c sgutest.c
CFLAGS=-DSGUTEST -std=c11 -g -Werror -Wall -O0
CFLAGS+=`pkg-config --cflags glib-2.0`
LDLIBS=`pkg-config --libs glib-2.0`
CC=clang

$(P): $(OBJECTS)

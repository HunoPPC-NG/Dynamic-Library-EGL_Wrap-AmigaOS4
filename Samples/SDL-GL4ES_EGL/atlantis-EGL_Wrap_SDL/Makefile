#!smake
#
# Copyright (c) Mark J. Kilgard, 1996, 1997.
#

TOP = ../../..
include 
include 

CPP = g++
CC = gcc
LN = 
MV = 
RM = -rm -rf

TARGETS = atlantis-SDL-EGL_wrap

LDFLAGS = -lSDLegl_wrap -use-dynld -legl_wrap -lauto
LLDLIBS = -lSDLegl_wrap -use-dynld -legl_wrap -lauto

SRCS =	swim.c atlantis.c whale.c dolphin.c shark.c
HDRS =	atlantis.h
OBJS =	$(SRCS:.c=.o)

LCOPTS = -I$(TOP)/include -fullwarn
LWOFF = ,813,852,827,826
LDIRT = *~ mjkimage.c *.bak *.pure

default : $(TARGETS)

atlantis-SDL-EGL_wrap : main.o atlantis.o whale.o dolphin.o shark.o swim.o 
	$(RM) $@
	$(CPP) -o $@ main.o atlantis.o whale.o dolphin.o shark.o swim.o $(LDFLAGS)

./atlantis.h : atlantis.h

include $(COMMONRULES)

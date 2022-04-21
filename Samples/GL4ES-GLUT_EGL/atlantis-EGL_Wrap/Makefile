#!smake
#
# Copyright (c) Mark J. Kilgard, 1996, 1997.
#

TOP = ../../..
include 
include 

CPP = g++
CC = gcc -O3
LN = 
MV = 
RM = -rm -rf

TARGETS = atlantis-EGL_wrap

LDFLAGS = -use-dynld -legl_wrap -lauto
LLDLIBS = -use-dynld -legl_wrap -lauto

SRCS =	swim.c atlantis.c whale.c dolphin.c shark.c
HDRS =	atlantis.h
OBJS =	$(SRCS:.c=.o)

LCOPTS = -I$(TOP)/include -fullwarn
LWOFF = ,813,852,827,826
LDIRT = *~ mjkimage.c *.bak *.pure

default : $(TARGETS)

atlantis-EGL_wrap : atlantis.o whale.o dolphin.o shark.o swim.o 
	$(RM) $@
	$(CPP) -o $@ atlantis.o whale.o dolphin.o shark.o swim.o $(LDFLAGS)

./atlantis.h : atlantis.h

include $(COMMONRULES)

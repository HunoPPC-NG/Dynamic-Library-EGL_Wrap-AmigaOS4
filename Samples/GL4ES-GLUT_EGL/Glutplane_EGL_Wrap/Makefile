CC = g++
CP = copy
RM = delete
CFLAGS =  -Iinclude -L/..
LIBS =  -use-dynld -legl_wrap -lauto 
OBJS = glutplane.o 
TARGET = glutplane_test
VERSION = 1

all: $(TARGET) glutplane_test

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)
	protect $@ +e

revision:
	bumprev $(VERSION) $(TARGET)

clean:
	$(RM) $(OBJS)
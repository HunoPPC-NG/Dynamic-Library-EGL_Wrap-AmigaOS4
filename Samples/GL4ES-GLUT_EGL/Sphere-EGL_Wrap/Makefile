CC = g++
CP = copy
RM = delete
CFLAGS =  -Iinclude -L/..
LIBS = -use-dynld -legl_wrap -lauto
OBJS = glut2.o 
TARGET = Glut2_test
VERSION = 1

all: $(TARGET) Glut2_test

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)
	protect $@ +e

revision:
	bumprev $(VERSION) $(TARGET)

clean:
	$(RM) $(OBJS)
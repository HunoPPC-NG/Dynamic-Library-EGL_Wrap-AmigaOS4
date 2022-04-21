CC = g++ -O2
CP = copy
RM = delete
CFLAGS =  -Iinclude -L/..
LIBS = -use-dynld -legl_wrap -lauto 
OBJS = scube.o 
TARGET = scube-EGL-GL4es
VERSION = 1

all: $(TARGET) scube-EGL-GL4es

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)
	protect $@ +e

revision:
	bumprev $(VERSION) $(TARGET)

clean:
	$(RM) $(OBJS)
CC			= gcc -O3

CPP			= g++ -O3

TARGET		= lesson05

$(TARGET):	lesson05.o 
	$(CPP) -o $(TARGET) lesson05.o -lSDLegl_wrap -use-dynld -legl_wrap -lauto

lesson05.o:		lesson05.c
	$(CC) -c lesson05.c

clean:
	rm -f $(TARGET) lesson05.o
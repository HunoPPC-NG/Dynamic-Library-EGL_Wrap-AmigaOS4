CC			= gcc -O3

CPP			= g++ -O3

TARGET		= lesson11

$(TARGET):	lesson11.o 
	$(CPP) -o $(TARGET) lesson11.o -lSDLegl_wrap -use-dynld -legl_wrap -lauto

lesson11.o:		lesson11.c
	$(CC) -c lesson11.c

clean:
	rm -f $(TARGET) lesson11.o
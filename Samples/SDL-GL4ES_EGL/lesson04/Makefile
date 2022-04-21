CC			= gcc -O3

CPP			= g++ -O3

TARGET		= lesson04

$(TARGET):	lesson04.o 
	$(CPP) -o $(TARGET) lesson04.o -lSDLegl_wrap -use-dynld -legl_wrap -lauto

lesson04.o:		lesson04.c
	$(CC) -c lesson04.c

clean:
	rm -f $(TARGET) lesson04.o
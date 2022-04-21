CC			= gcc -O3

CPP			= g++ -O3

TARGET		= lesson09

$(TARGET):	lesson09.o 
	$(CPP) -o $(TARGET) lesson09.o -lSDLegl_wrap -use-dynld -legl_wrap -lauto

lesson09.o:		lesson09.c
	$(CC) -c lesson09.c

clean:
	rm -f $(TARGET) lesson09.o
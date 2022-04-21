CC			= gcc -O3

CPP			= g++ -O3

TARGET		= lesson17

$(TARGET):	lesson17.o 
	$(CPP) -o $(TARGET) lesson17.o -lSDLegl_wrap -use-dynld -legl_wrap -lauto

lesson17.o:		lesson17.c
	$(CC) -c lesson17.c

clean:
	rm -f $(TARGET) lesson17.o
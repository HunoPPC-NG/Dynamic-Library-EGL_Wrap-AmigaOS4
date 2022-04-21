CC			= gcc -O3

CPP			= g++ -O3

TARGET		= lesson07

$(TARGET):	lesson07.o 
	$(CPP) -o $(TARGET) lesson07.o -lSDLegl_wrap -use-dynld -legl_wrap -lauto

lesson07.o:		lesson07.c
	$(CC) -c lesson07.c

clean:
	rm -f $(TARGET) lesson07.o
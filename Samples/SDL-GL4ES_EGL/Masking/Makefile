CC			= g++

TARGET		= Masking 

$(TARGET):	Main.o Init.o
	$(CC) -o $(TARGET) Main.o Init.o  -lSDLegl_wrap -use-dynld -legl_wrap -lauto

Main.o:		Main.cpp main.h
	$(CC) -c Main.cpp

Init.o:		Init.cpp main.h
	$(CC) -c   Init.cpp

clean:
	rm -f $(TARGET) Main.o Init.o core

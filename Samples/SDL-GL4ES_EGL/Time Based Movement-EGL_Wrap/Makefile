CC			= g++

TARGET		= TimeBasedMovement-EGL-GL4es

$(TARGET):	Main.o Init.o Camera.o
	$(CC) -o $(TARGET) Main.o Init.o Camera.o -lSDLegl_wrap -use-dynld -legl_wrap -lauto 

Main.o:		Main.cpp main.h
	$(CC) -c Main.cpp

Init.o:		Init.cpp main.h
	$(CC) -c Init.cpp

Camera.o:	Camera.cpp main.h
	${CC} -c Camera.cpp

clean:
	rm -f $(TARGET) Main.o Init.o core Camera.o

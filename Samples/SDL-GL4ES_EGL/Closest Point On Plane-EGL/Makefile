CC			= g++

TARGET		= ClosestPointOnPlane

$(TARGET):	Main.o Init.o 3DMath.o
	$(CC) -o $(TARGET) Main.o Init.o 3DMath.o -lSDLegl_wrap -use-dynld -legl_wrap -lauto

Main.o:		Main.cpp main.h
	$(CC) -c Main.cpp 
Init.o:		Init.cpp main.h
	$(CC) -c Init.cpp 

3DMath.o:	3DMath.cpp main.h 3DMath.h
	${CC} -c 3DMath.cpp 

clean:
	rm -f $(TARGET) Main.o Init.o 3DMath.o core

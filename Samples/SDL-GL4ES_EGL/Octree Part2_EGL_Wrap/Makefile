CC			= g++ 

TARGET		= octree2

$(TARGET):	Main.o Init.o Camera.o Octree.o Frustum.o
	$(CC) -o $(TARGET) Main.o Init.o Camera.o Octree.o Frustum.o  -lSDLegl_wrap -use-dynld -legl_wrap -lauto

Main.o:		Main.cpp main.h Camera.h;	$(CC) -c  Main.cpp

Init.o:		Init.cpp main.h
	$(CC) -c Init.cpp

Camera.o :  Camera.cpp main.h Camera.h
	$(CC) -c Camera.cpp

Octree.o :  Octree.cpp Octree.h main.h
	$(CC) -c Octree.cpp

Frustum.o :  Frustum.cpp Frustum.h 
	$(CC) -c Frustum.cpp

clean:
	rm -f $(TARGET) Main.o Init.o Camera.o Octree.o Frustum.o core

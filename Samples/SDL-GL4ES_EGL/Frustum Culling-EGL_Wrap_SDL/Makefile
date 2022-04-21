CC			= g++ -O3

TARGET		= FrustumCulling

$(TARGET):	Main.o Init.o Frustum.o Camera.o
	$(CC) -o $(TARGET) Main.o Init.o Frustum.o Camera.o -lSDLegl_wrap -use-dynld -legl_wrap -lauto

Main.o:		Main.cpp main.h
	$(CC) -c Main.cpp

Frustum.o:  Frustum.cpp main.h
	$(CC) -c Frustum.cpp

Camera.o:   Camera.cpp Camera.h
	$(CC) -c Camera.cpp

Init.o:		Init.cpp main.h
	$(CC) -c Init.cpp

clean:
	rm -f $(TARGET) Main.o Init.o Frustum.o Camera.o core

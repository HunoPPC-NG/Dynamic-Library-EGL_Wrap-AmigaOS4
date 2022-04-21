CC			= g++

TARGET		= OBJLoader

$(TARGET):	Main.o Init.o Obj.o
	$(CC) -o $(TARGET) Main.o Init.o Obj.o -lSDLegl_wrap -lSDL_image -ltiff -ljpeg -lpng12 -lwebp -lpthread -lz -use-dynld -legl_wrap -lauto

Main.o:		Main.cpp main.h
	$(CC) -c Main.cpp 

Obj.o:	    Obj.cpp Obj.h
	$(CC) -c Obj.cpp 

Init.o:		Init.cpp main.h
	$(CC) -c Init.cpp 

clean:
	rm -f $(TARGET) Main.o Init.o Obj.o core

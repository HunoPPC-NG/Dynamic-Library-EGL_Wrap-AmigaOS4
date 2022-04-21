CC			= gcc -O3

CPP			= g++ -O3

TARGET		= Cube-Blending-EGL-GL4es

$(TARGET):	blending.o 
	$(CPP) -o $(TARGET) blending.o -lSDLegl_wrap -use-dynld -legl_wrap -lauto -lSDL_image -ltiff -ljpeg -lpng12 -lwebp -lz -lpthread 

blending.o:		blending.c
	$(CC) -c blending.c

clean:
	rm -f $(TARGET) blending.o
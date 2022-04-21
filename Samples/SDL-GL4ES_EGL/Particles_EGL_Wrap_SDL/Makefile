CC			= g++

TARGET		= Particle 

$(TARGET):	OGL.o particle.o main.o
	$(CC) -o $(TARGET) OGL.o particle.o main.o -lSDLegl_wrap -use-dynld -legl_wrap -lauto

OGL.o:		OGL.cpp OGL.h
	$(CC) -c OGL.cpp

particle.o:		particle.cpp particle.h
	$(CC) -c particle.cpp

main.o:	main.cpp
	$(CC) -c main.cpp

clean:
	rm -f $(TARGET) OGL.o particle.o main.o 

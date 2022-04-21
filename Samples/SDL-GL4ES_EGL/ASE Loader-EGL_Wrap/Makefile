CC			= g++

TARGET		= ASELoader

$(TARGET):	Main.o Init.o Ase.o
	$(CC) -o $(TARGET) Main.o Init.o Ase.o -lSDLegl_wrap -use-dynld -legl_wrap -lauto

Main.o:		Main.cpp main.h
	$(CC) -c Main.cpp

Ase.o:            Ase.cpp Ase.h
	$(CC) -c Ase.cpp

Init.o:		Init.cpp main.h
	$(CC) -c Init.cpp

clean:
	rm -f $(TARGET) Main.o Init.o Ase.o core

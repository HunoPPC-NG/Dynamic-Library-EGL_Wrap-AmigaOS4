CC=g++
CFLAGS=-W -g -Wall -ansi -pedantic
LDFLAGS=-lSDL2egl_wrap -use-dynld -legl_wrap -lauto
EXEC=glcube
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: GlCube.h

%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)

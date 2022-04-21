
CPP  = g++
CC   = gcc 
WINDRES =
RES  = 
OBJ      = boing_ball.o texture.o test.o
LINKOBJ  = boing_ball.o texture.o test.o
LIBS =  -use-dynld -legl_wrap -lauto 
INCS = 
CXXINCS = 
BIN  = BoingTest-EGL-ES-VBO
CXXFLAGS = $(CXXINCS) -O3 -DUSEVBO
CFLAGS = $(INCS) -O3 -DUSEVBO
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before BoingTest-EGL-ES-VBO all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(LINKOBJ)
	g++ -o $(BIN) -use-dynld -legl_wrap -lauto $(LINKOBJ) -o $(BIN) 

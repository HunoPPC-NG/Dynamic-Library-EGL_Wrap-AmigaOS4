CC = g++
LD = g++
OBJ = \
	 triangles.o

BIN = openGLES-Hello_TriangleRotation

INCPATH = -I.

CFLAGS = $(INCPATH) -Wall  -Wwrite-strings

LDFLAGS =-use-dynld -legl_wrap -lauto

LIBS = 
#	add any extra linker libraries you want here

.PHONY: all all-before all-after clean clean-custom realclean

all: all-before $(BIN) all-after

all-before:
#	You can add rules here to execute before the project is built

all-after:
#	You can add rules here to execute after the project is built

clean: clean-custom
	rm -v $(OBJ)

realclean:
	rm -v $(OBJ) $(BIN)

$(BIN): $(OBJ) $(LIBS)
#	You may need to move the LDFLAGS variable in this rule depending on its contents
	@echo "Linking $(BIN)"
	@$(LD) -o $(BIN) $(OBJ) $(LDFLAGS) $(LIBS)

###################################################################
##
##  Standard rules
##
###################################################################

# A default rule to make all the objects listed below
# because we are hiding compiler commands from the output

.c.o:
	@echo "Compiling $<"
	@$(CC) -c $< -o $*.o $(CFLAGS)
triangles.o: triangles.cpp





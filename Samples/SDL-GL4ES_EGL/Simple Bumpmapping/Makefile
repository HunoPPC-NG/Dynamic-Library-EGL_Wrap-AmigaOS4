CC = g++
LD = g++
OBJ = \
	 main.o TORUS.o Maths/VECTOR4D.o Maths/VECTOR3D.o Maths/VECTOR2D.o Maths/COLOR.o Maths/MATRIX4X4.o Maths/PLANE.o NormalisationCubeMap.o Image/IMAGE_CalculateStride.o Image/IMAGE_ExpandPalette.o Image/IMAGE_Load.o Image/IMAGE_Load24BitBMP.o  Image/IMAGE_Load8BitBMP.o Image/IMAGE_LoadAlpha.o Image/IMAGE_LoadBMP.o Image/IMAGE_LoadCompressedTrueColorTGA.o Image/IMAGE_LoadTGA.o Image/IMAGE_LoadUncompressed8BitTGA.o Image/IMAGE_LoadUncompressedTrueColorTGA.o Extensions/ARB_multitexture_extension.o Extensions/ARB_texture_cube_map_extension.o Extensions/ARB_texture_env_combine_extension.o Extensions/ARB_texture_env_dot3_extension.o

BIN = openGLES-GLUES-Bumpmapping

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
TORUS.o: TORUS.cpp
Maths/VECTOR4D.o: Maths/VECTOR4D.cpp
Maths/VECTOR3D.o: Maths/VECTOR3D.cpp
Maths/VECTOR2D.o: Maths/VECTOR2D.cpp
Maths/COLOR.o: Maths/COLOR.cpp
Maths/MATRIX4X4.o: Maths/MATRIX4X4.cpp
Maths/PLANE.o: Maths/PLANE.cpp
NormalisationCubeMap.o: NormalisationCubeMap.cpp
Image/IMAGE_CalculateStride.o: Image/IMAGE_CalculateStride.cpp
Image/IMAGE_ExpandPalette.o: Image/IMAGE_ExpandPalette.cpp
Image/IMAGE_Load.o: Image/IMAGE_Load.cpp
Image/IMAGE_Load24BitBMP.o: Image/IMAGE_Load24BitBMP.cpp
Image/IMAGE_Load8BitBMP.o: Image/IMAGE_Load8BitBMP.cpp
Image/IMAGE_LoadAlpha.o: Image/IMAGE_LoadAlpha.cpp
Image/IMAGE_LoadBMP.o: Image/IMAGE_LoadBMP.cpp
Image/IMAGE_LoadCompressedTrueColorTGA.o: Image/IMAGE_LoadCompressedTrueColorTGA.cpp
Image/IMAGE_LoadTGA.o: Image/IMAGE_LoadTGA.cpp
Image/IMAGE_LoadUncompressed8BitTGA.o: Image/IMAGE_LoadUncompressed8BitTGA.cpp
Image/IMAGE_LoadUncompressedTrueColorTGA.o: Image/IMAGE_LoadUncompressedTrueColorTGA.cpp
Extensions/ARB_multitexture_extension.o: Extensions/ARB_multitexture_extension.cpp
Extensions/ARB_texture_cube_map_extension.o: Extensions/ARB_texture_cube_map_extension.cpp
Extensions/ARB_texture_env_combine_extension.o: Extensions/ARB_texture_env_combine_extension.cpp
Extensions/ARB_texture_env_dot3_extension.o: Extensions/ARB_texture_env_dot3_extension.cpp
main.o: main.cpp





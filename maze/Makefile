#OBJS specifies which files to compile as part of the project
OBJS = src/main.c src/distances.c src/readfromfile.c src/globals.c src/loadTexture.c src/camera_movement.c src/collision.c src/draw.c src/draw_map.c src/game.c

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -Wall -Werror -Wextra -pedantic

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = `sdl2-config --cflags --libs` -lm -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = a.out

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm -f $(OBJ_NAME)

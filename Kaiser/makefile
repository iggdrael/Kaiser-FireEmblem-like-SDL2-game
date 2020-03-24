CC=gcc
FLAGS=-Wall -g

SDL_DIR=${HOME}/SDL
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include

LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}
PROG=Kaiser

all:	sdl_text

sdl_text:	main.c fonctions.c
	${CC} -o ${PROG} main.c fonctions.c `sdl2-config --cflags --libs` ${LIBS}
clean:
	rm -f ${PROG}
	rm -f *.o



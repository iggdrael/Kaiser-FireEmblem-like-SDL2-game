CC=gcc
FLAGS=-Wall -g

SDL_DIR=${HOME}/SDL
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include

LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}
PROG=Kaiser

all:	sdl

sdl:	editeur.c fonctions.c jeu.c lib.c main.c menus.c selection_equipe.c
	${CC} -o ${PROG} editeur.c fonctions.c jeu.c lib.c main.c menus.c selection_equipe.c ${INCS} ${LIBS}

clean:
	rm -f ${PROG}
	rm -f *.o



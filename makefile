
CC=gcc

SDL_DIR=${HOME}/SDLBIS
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} 

PROG=sdl_test

all: sdl_text

sdl_text: src/main.c src/fonctions.c
	${CC} -o ${PROG} src/main.c src/fonctions.c ${LIBS} ${INCLUDES}

clean: 
	rm -f ${PROG}
	rm -f *.o



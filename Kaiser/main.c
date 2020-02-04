#include "fonctions.h"
//gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
//gcc src/kaiser/main.c .\src\kaiser\fonctions.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

int main(int argc, char** argv){
/**La fonction main constitue un menu permettant :
 * de lancer le jeu
 * de lancer l'editeur de map
 * d'acceder aux reglages
**/

/**------------------Declaration des variables principales-------------**/
	
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	TTF_Font *font;

/**------------------Initialisation SDL et librairies------------------**/

    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
        SDL_ExitWithError("Initialisation SDL", NULL, NULL, NULL);

	if(!TTF_WasInit() && TTF_Init()==-1) {
    	printf("TTF_Init: %s\n", TTF_GetError());
    	exit(EXIT_FAILURE);
	}

	window = SDL_CreateWindow("Kaiser",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if(window == NULL)
		SDL_ExitWithError("Erreur à la création de la fenetre\n", window, NULL, NULL);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL)
		SDL_ExitWithError("Erreur à la création du renderer\n", window, renderer, NULL);


/**------------------Declaration variables secondaires-------------------------**/

	//int ;
	//SDL_bool program_launched = SDL_TRUE;
	//SDL_Event event;

/**------------------Creation des textures-------------------------------------**/

	//SDL_Texture *texture;

/**------------------Debut du programme----------------------------------------**/

	menu(window, renderer);
    /*while (program_launched){
        while (SDL_PollEvent(&event)){
            switch(event.type){
				case SDL_QUIT: program_launched = SDL_FALSE;break;

                case SDL_MOUSEBUTTONDOWN:
					//case jouer:jouer()
					//case editeur:editeur()
					//case reglages:reglages()
                    break;
				
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE: program_launched = SDL_FALSE;break;
						case SDLK_a: editeur_map(window, renderer);break;
            		}
					break;
			}
        }
    }*/

/**------------------Liberation de la mémoire allouee-------------------------**/

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
    SDL_Quit();

/**-----------------Fin du programme------------------------------------------**/

    return EXIT_SUCCESS;
}


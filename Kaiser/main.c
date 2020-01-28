#include "fonctions.h"
//gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
//gcc src/kaiser/main.c .\src\kaiser\fonctions.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

int main(int argc, char** argv){
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	int *map = init_map();
	//aff_map(map);

    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
        SDL_ExitWithError("Initialisation SDL", NULL, NULL, NULL);

	window = SDL_CreateWindow("Kaiser",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if(window == NULL)
		SDL_ExitWithError("Erreur à la création de la fenetre\n", window, NULL, NULL);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL)
		SDL_ExitWithError("Erreur à la création du renderer\n", window, renderer, NULL);

	//creer_map_rendu(window, renderer);
	//editeur_map(window, renderer, map);
	SDL_Texture *texture_tiles = creerTexture(window, renderer, "texturesfull.png");
	load_matrice(map);
	load_map(map, renderer, texture_tiles);

/************************************************************************************************************************************************************************************/
	int x, y, i = 13, j = 5, texture_actuelle_x, texture_actuelle_y;
	float p;
	select_tile(renderer, texture_tiles, i, j, 44, 15);
	SDL_RenderPresent(renderer);

/***************************************************/
	SDL_bool program_launched = SDL_TRUE;

    while (program_launched){
        SDL_Event event;

        while (SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_MOUSEBUTTONDOWN:
					x = event.button.y / LARGEUR_EDIT;
					y = event.button.x / LARGEUR_EDIT;
					SDL_Log("%d-%d  --> map[%d][%d]\n", event.button.x, event.button.y, x, y);
                    break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							program_launched = SDL_FALSE;
							break;
						case SDLK_UP:
							p = (float)*(map + M*i + j) / (float)NOMBRE_BLOCS_LARGEUR;
							texture_actuelle_x = (int)p;
							p = (p - texture_actuelle_x) * 100;
							texture_actuelle_y = NOMBRE_BLOCS_LARGEUR * p / 100;
							select_tile(renderer, texture_tiles, i, j, texture_actuelle_x, texture_actuelle_y);

							i--;
							select_tile(renderer, texture_tiles, i, j, 44, 15);
							SDL_RenderPresent(renderer);
							break;
						case SDLK_DOWN:
							p = (float)*(map + M*i + j) / (float)NOMBRE_BLOCS_LARGEUR;
							texture_actuelle_x = (int)p;
							p = (p - texture_actuelle_x) * 100;
							texture_actuelle_y = NOMBRE_BLOCS_LARGEUR * p / 100;
							select_tile(renderer, texture_tiles, i, j, texture_actuelle_x, texture_actuelle_y);

							i++;
							select_tile(renderer, texture_tiles, i, j, 44, 15);
							SDL_RenderPresent(renderer);
							break;
						case SDLK_RIGHT:
							p = (float)*(map + M*i + j) / (float)NOMBRE_BLOCS_LARGEUR;
							texture_actuelle_x = (int)p;
							p = (p - texture_actuelle_x) * 100;
							texture_actuelle_y = NOMBRE_BLOCS_LARGEUR * p / 100;
							select_tile(renderer, texture_tiles, i, j, texture_actuelle_x, texture_actuelle_y);

							j++;
							select_tile(renderer, texture_tiles, i, j, 44, 15);
							SDL_RenderPresent(renderer);
							break;
						case SDLK_LEFT:
							p = (float)*(map + M*i + j) / (float)NOMBRE_BLOCS_LARGEUR;
							texture_actuelle_x = (int)p;
							p = (p - texture_actuelle_x) * 100;
							texture_actuelle_y = NOMBRE_BLOCS_LARGEUR * p / 100;
							select_tile(renderer, texture_tiles, i, j, texture_actuelle_x, texture_actuelle_y);
							
							j--;
							select_tile(renderer, texture_tiles, i, j, 44, 15);
							SDL_RenderPresent(renderer);
							break;
					}
					break;
                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;
                default: break;
            }
        }
    }
	SDL_DestroyTexture(texture_tiles);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();
	free(map);

    return EXIT_SUCCESS;
}


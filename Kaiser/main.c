#include "fonctions.h"
//gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

int main(int argc, char** argv)
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	int *map = init_map();
	//aff_map(map);

    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
        SDL_ExitWithError("Initialisation SDL", NULL, NULL, NULL);

	window = SDL_CreateWindow("Kaiser",0, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
	//window = SDL_CreateWindow("Textures",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 736, 672, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);


	if(window == NULL)
		SDL_ExitWithError("Erreur à la création de la fenetre\n", window, NULL, NULL);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL)
		SDL_ExitWithError("Erreur à la création du renderer\n", window, renderer, NULL);

	//creer_map_rendu(window, renderer);
	editeur_map(window, renderer, map);
	//SDL_Texture *texture_case = creerTexture(window, renderer, "src/Kaiser/img/textures.png");
	//aff_texture(window, renderer, texture_case, 0, 0, HUD, 0);

/************************************************************************************************************************************************************************************/

	SDL_bool program_launched = SDL_TRUE, tour = SDL_TRUE;
	coords graph, mat;

    while (program_launched){
        SDL_Event event;

        while (SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_MOUSEBUTTONDOWN:
					graph.x = event.button.x;
					graph.y = event.button.y;
					mat.x = event.button.y / (672 / 21);
					mat.y = event.button.x / (736 / 23);

					SDL_Log("%d-%d  --> grille[%d][%d]\n", graph.x, graph.y, mat.x, mat.y);
                    break;
				case SDL_KEYDOWN:

					break;
                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;
                default: break;
            }
        }
    }

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();
	free(map);

    return EXIT_SUCCESS;
}


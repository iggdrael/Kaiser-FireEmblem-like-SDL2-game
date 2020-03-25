#include "commun.h"
//gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
//gcc .\src\ProjetS4\Kaiser\main.c .\src\ProjetS4\Kaiser\fonctions.c .\src\ProjetS4\Kaiser\selection_equipe.c  .\src\ProjetS4\Kaiser\jeu.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf  

int main(int argc, char** argv){
/**La fonction main constitue un menu permettant :
 * de lancer le jeu
 * de lancer l'editeur de map
 * d'acceder aux reglages
**/

/**------------------Declaration des variables principales-------------**/

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	WIDTH=1366;
	HEIGHT=768;

/**------------------Initialisation SDL et librairies------------------**/

  if (SDL_Init(SDL_INIT_VIDEO) != 0 )
  	SDL_ExitWithError("Initialisation SDL", NULL, NULL, NULL);

	if(!TTF_WasInit() && TTF_Init() == -1)
		SDL_ExitWithError("TTF_Init", NULL, NULL, NULL);

	window = SDL_CreateWindow("Kaiser",10, 50, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
		SDL_ExitWithError("Erreur à la création de la fenetre\n", window, NULL, NULL);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		SDL_ExitWithError("Erreur à la création du renderer\n", window, renderer, NULL);

/**------------------Initialisation map---------------------------------------**/

	case_t *map = init_matrice();

/**------------------Chargement des textures----------------------------------**/

	SDL_Texture *pack_texture = creerTexture(window, renderer, "packtexture.png");

/**------------------Affichage du Menu----------------------------------------**/

	menu(window, renderer, map, pack_texture);

/**------------------Liberation de la mémoire allouee-------------------------**/

	SDL_DestroyTexture(pack_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

/**-----------------Fin du programme------------------------------------------**/

	return EXIT_SUCCESS;
}

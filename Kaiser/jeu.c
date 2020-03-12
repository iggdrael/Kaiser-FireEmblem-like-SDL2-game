#include "fonctions.h"
#include "jeu.h"

int randint(int min, int max){
	srand(time(NULL));
	return (rand()%(max - min + 1) + min);
}

void lancer_jeu(SDL_Window *window, SDL_Renderer *renderer){
/**Fonction Principale**/

/**------------------Creation des textures----------------------------------------------------**/

	SDL_Texture *pack_texture = creerTexture(window, renderer, "packtexture.png");

/**------------------Initialisation Jeu---------------------------------------------------**/

	case_t *map = init_matrice();

	int nb_persos = randint(MIN_PERSO, MAX_PERSO);
	//creationEquipes();

	int i_map = randint(1, NB_MAPS);
	char nom_map[10] = "mapX.txt";
	nom_map[3] = i_map;

	load_matrice(map)
	aff_map(map, renderer, pack_texture);
	//aff_tile(...,gui);
	SDL_RenderPresent(renderer);

/**------------------Autres variables-----------------------------------------------------**/

	SDL_bool jeu_launched = SDL_TRUE;
    SDL_Event event;

/**------------------Debut du programme de jeu------------------------------------------**/

    while (jeu_launched){
        SDL_WaitEvent(&event);

		switch(event.type){
			case SDL_QUIT: jeu_launched = SDL_FALSE;break;
		}
	}

/**------------------Liberation de la mémoire allouee----------------------------------------**/

	SDL_DestroyTexture(pack_texture);
	detruire_matrice(map);

/**------------------Fin du programme de l editeur-------------------------------------------**/
}

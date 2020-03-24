#include "fonctions.h"
#include "jeu.h"

int randint(int min, int max){
/**Fonction générant un entier aléatoire entre deux bornes en paramètres**/
	srand(time(NULL));
	return (rand()%(max - min + 1) + min);
}

void lancer_jeu(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *pack_texture, case_t *map){
/**Fonction Principale**/

	SDL_Window *window_gui = NULL;
	SDL_Renderer *renderer_gui = NULL;

/**------------------Initialisation de la fenetre et du renderer du gui----------------------**/

	window_gui = SDL_CreateWindow("Interface combat", WIDTH + 15, 50, (WIDTH / 3.5), HEIGHT, SDL_WINDOW_SHOWN);

	if(window_gui == NULL)
		SDL_ExitWithError("Erreur à la création de la fenetre\n", window_gui, NULL, NULL);

	renderer_gui = SDL_CreateRenderer(window_gui, -1, SDL_RENDERER_ACCELERATED);
	if(renderer_gui == NULL)
		SDL_ExitWithError("Erreur à la création du renderer\n", window_gui, renderer_gui, NULL);


/**------------------Variables correspondant a l id des fenetres------------------------------**/

	Uint32 id_main_window = SDL_GetWindowID(window);
	Uint32 id_window_gui = SDL_GetWindowID(window_gui);

/**------------------Creation des textures----------------------------------------------------**/

	SDL_Texture *interface = creerTexture(window_gui, renderer_gui, "gui.png");

/**------------------Initialisation Jeu---------------------------------------------------**/

	//int nb_persos = randint(MIN_PERSO, MAX_PERSO);
	//creationEquipes();

	//int i_map = randint(1, NB_MAPS);
	//char nom_map[10] = "mapX.txt";
	//nom_map[3] = i_map;

	//load_matrice(map);
	aff_map(map, renderer, pack_texture);
	aff_tile(renderer_gui, interface, 0, 0, -1);
	SDL_RenderPresent(renderer);
	SDL_RenderPresent(renderer_gui);

/**------------------Autres variables-----------------------------------------------------**/

	///Determine quel joueur commence à jouer
	//int tour_joueur = randint(0, 1);


	SDL_bool jeu_launched = SDL_TRUE;
    SDL_Event event;

/**------------------Debut du programme de jeu------------------------------------------**/

    while (jeu_launched){
        SDL_WaitEvent(&event);
		if (event.window.windowID == id_main_window){

			switch(event.type){
				case SDL_QUIT: jeu_launched = SDL_FALSE;break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							jeu_launched = SDL_FALSE;
							break;
					}
			}
		}
		else if (event.window.windowID == id_window_gui){
/**------------------Evenement sur fenetre interface------------------------------------------**/

			switch(event.type){
				case SDL_QUIT: jeu_launched = SDL_FALSE;break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							jeu_launched = SDL_FALSE;
							break;
					}
			}
		}
	}

/**------------------Liberation de la mémoire allouee----------------------------------------**/

	SDL_DestroyTexture(interface);
	SDL_DestroyRenderer(renderer_gui);
	SDL_DestroyWindow(window_gui);

/**------------------Fin du programme de jeu-------------------------------------------**/

	menu(window, renderer, map, pack_texture);
}

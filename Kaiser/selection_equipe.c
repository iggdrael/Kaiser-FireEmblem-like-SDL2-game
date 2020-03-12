#include "fonctions.h"

void create_team(perso_t * team, const int NB_PERS){

	team = malloc(NB_PERS * sizeof(perso_t));
	
	SDL_Event event;
	SDL_Bool selection_launched = SDL_TRUE;
	SDL_Texture *background = NULL;
	const int taille_police = 72;

	SDL_Surface *back_rect = NULL;
	TTF_Font *police = TTF_OpenFont("caviardreams.ttf", taille_police);

	if (!police)
		SDL_ExitWithError("Erreur du chargement de la police", window, renderer, background);

	back_rect = IMG_Load("background.png");
	if(back_rect == NULL){
    	SDL_ExitWithError("Erreur à la création de l'image\n", window, renderer, NULL);
		exit(EXIT_FAILURE);
	}

	background = SDL_CreateTextureFromSurface(renderer, back_rect);
	SDL_FreeSurface(back_rect);
	if(background == NULL){
    	SDL_ExitWithError("Erreur à la création de la texture\n", window, renderer, background);
		exit(EXIT_FAILURE);
	}
	aff_tile(renderer, background, 0, 0, -1);

	/// Affichage des rectangles sous les textes.

 	SDL_RenderPresent(renderer);

	while (selection_launched){
        SDL_WaitEvent(&event);

			switch(event.type){
				case SDL_QUIT: selection_launched = SDL_FALSE; break;

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT){
						
					}
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE: menu_launched = SDL_FALSE; break;

					}
			}
	}

	free(police);
	SDL_DestroyTexture(background);

	if (setting_asked)
		settings(window, renderer);
	
}

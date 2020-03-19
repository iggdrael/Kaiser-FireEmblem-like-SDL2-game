#include "fonctions.h"
#include "selection_equipe.h"

void create_team(SDL_Window *window, SDL_Renderer *renderer, case_t *map, SDL_Texture *pack_texture, perso_t * team, const int NB_PERS){

	team = malloc(NB_PERS * sizeof(perso_t));
	

	SDL_Rect rect_plus, rect_minus;
	const int taille_police = 72;

	rect_plus.w = rect_minus.w = rect_plus.h = rect_minus.h = taille_police + 10;
	rect_plus.x = WIDTH/2 - rect_plus.w;
	rect_minus.x = WIDTH/2 + rect_minus.w;
	rect_plus.y = rect_minus.y = HEIGHT-3*(HEIGHT/4);

	TTF_Font *police = TTF_OpenFont("caviardreams.ttf", taille_police);
	SDL_Texture *pack_textures_for_window = creerTexture(window, renderer, "packtexture.png");

	if (!police)
		SDL_ExitWithError("Erreur du chargement de la police", window, renderer, NULL);

	load_matrice(map);
	aff_map(map, renderer, pack_texture);

	SDL_SetRenderDrawColor(renderer, 46, 180, 100, 255);

	SDL_RenderFillRect(renderer, &rect_plus);
	SDL_RenderFillRect(renderer, &rect_minus);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderDrawRect(renderer, &rect_plus);
	SDL_RenderDrawRect(renderer, &rect_minus);

	creerTexte(renderer, police, "+", rect_plus.x + 23, rect_plus.y - 7);
	creerTexte(renderer, police, "-", rect_minus.x + 27, rect_minus.y - 7);
	aff_tile(renderer, pack_textures_for_window, rect_plus.x%LARGEUR_CASE, rect_plus.y%LARGEUR_CASE + 3, 484);

	SDL_RenderPresent(renderer);

	SDL_Event event;
	SDL_bool selection_launched = SDL_TRUE;
	SDL_bool menu_asked = SDL_FALSE;
	SDL_bool game_start = SDL_FALSE;

	while (selection_launched && menu_asked == SDL_FALSE && game_start == SDL_FALSE){
        SDL_WaitEvent(&event);

			switch(event.type){
				case SDL_QUIT: selection_launched = SDL_FALSE;break;

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT){
						if (clickSurCase(event, rect_plus)){
							printf("+\n");
						}
						else if (clickSurCase(event, rect_minus)){
							printf("-\n");
						}
					}
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE: menu_asked = SDL_TRUE;break;

					}
			}
	}

	free(police);

	if (menu_asked)
		menu(window, renderer, map, pack_texture);

	if (game_start);
		//lancer_jeu(window, renderer);
	
}

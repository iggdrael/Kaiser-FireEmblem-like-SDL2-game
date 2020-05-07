#include "libs/commun.h"

void settings(SDL_Window *window, SDL_Renderer *renderer, case_t *map, SDL_Texture *pack_texture){
/**Fonction affichant un menu permettant a l utilisateur de naviguer dans le programme**/
	SDL_Rect rect_taille_1, rect_taille_2, rect_taille_3, rect_taille_4, rect_quitter;
	const int taille_police = 40;
	const int taille_police_titre = 72;

	rect_taille_1.w = rect_taille_2.w = rect_taille_3.w = rect_taille_4.w = WIDTH/6;
	rect_taille_1.h = rect_taille_2.h = rect_taille_3.h = rect_taille_4.h = taille_police;
	rect_taille_1.y = rect_taille_2.y = rect_taille_3.y = rect_taille_4.y = HEIGHT-3*(HEIGHT/5)+5;

	rect_taille_1.x = (rect_taille_1.w)/6;
	rect_taille_2.x = (rect_taille_1.w)*1.7;
	rect_taille_3.x = (rect_taille_1.w)*3.2;
	rect_taille_4.x = (rect_taille_1.w)*4.8;

	rect_quitter.w = WIDTH-WIDTH*0.65;
	rect_quitter.h = taille_police_titre;
	rect_quitter.x = (WIDTH-(WIDTH-WIDTH*0.65))/2;
	rect_quitter.y = HEIGHT-1*(HEIGHT/4)+5;

	TTF_Font *police_titre = TTF_OpenFont(NOM_FONT, taille_police_titre);
	TTF_Font *police =TTF_OpenFont(NOM_FONT, taille_police);

	if (!police)
		SDL_ExitWithError("Erreur du chargement de la police", window, renderer, NULL);
	if (!police_titre)
		SDL_ExitWithError("Erreur du chargement de la police titre(Option)", window, renderer, NULL);

	load_matrice(map, 0);
	aff_map(map, renderer, pack_texture);

	SDL_SetRenderDrawColor(renderer, R_R,  R_G, R_B, 255);

	SDL_RenderFillRect(renderer, &rect_taille_1);
	SDL_RenderFillRect(renderer, &rect_taille_2);
	SDL_RenderFillRect(renderer, &rect_taille_3);
	SDL_RenderFillRect(renderer, &rect_taille_4);
	SDL_RenderFillRect(renderer, &rect_quitter);


	/// Affichage des rectangles sous les textes.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderDrawRect(renderer, &rect_taille_1);
	SDL_RenderDrawRect(renderer, &rect_taille_2);
	SDL_RenderDrawRect(renderer, &rect_taille_3);
	SDL_RenderDrawRect(renderer, &rect_taille_4);

	SDL_RenderDrawRect(renderer, &rect_quitter);

	creerTexte(renderer, police_titre, "Affichage", WIDTH/2 - 5 * 34, (HEIGHT-3*(HEIGHT/4)+5) - 5);
	creerTexte(renderer, police_titre, "Son", WIDTH/2 - 7 * 13, (HEIGHT-2*(HEIGHT/4)+5) - 5);
	creerTexte(renderer, police_titre, "Retour", WIDTH/2 - 6 * 20, rect_quitter.y - 5);

	creerTexte(renderer, police, "1280x720", rect_taille_1.w/6, rect_taille_1.y-5);
	creerTexte(renderer, police, "1366x768", rect_taille_1.w*1.7, rect_taille_1.y-5);
	creerTexte(renderer, police, "1600x900", rect_taille_1.w*3.2, rect_taille_1.y-5);
	creerTexte(renderer, police, "1920x1080", rect_taille_1.w*4.8, rect_taille_1.y-5);

 	SDL_RenderPresent(renderer);

	SDL_Event event;
	SDL_bool set_launched = SDL_TRUE;
	SDL_bool settings_asked = SDL_FALSE;
	while (set_launched){
		SDL_WaitEvent(&event);
			switch(event.type){
				case SDL_QUIT: set_launched = SDL_FALSE;break;

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT){
						if (clickSurCase(event, rect_taille_1)){
							WIDTH=1280;
							HEIGHT=720;
							SDL_SetWindowSize(window, WIDTH, HEIGHT);
							settings_asked=SDL_TRUE;
							set_launched = SDL_FALSE;
						}
						else if (clickSurCase(event, rect_taille_2)){
							WIDTH=1366;
							HEIGHT=768;
							SDL_SetWindowSize(window, WIDTH, HEIGHT);
							settings_asked=SDL_TRUE;
							set_launched = SDL_FALSE;
						}
						else if (clickSurCase(event, rect_taille_3)){
							WIDTH=1600;
							HEIGHT=900;
							SDL_SetWindowSize(window, WIDTH, HEIGHT);
							settings_asked=SDL_TRUE;
							set_launched = SDL_FALSE;
						}
						else if (clickSurCase(event, rect_taille_4)){
							WIDTH=1920;
							HEIGHT=1080;
							SDL_SetWindowSize(window, WIDTH, HEIGHT);
							settings_asked=SDL_TRUE;
							set_launched = SDL_FALSE;
						}
						else if (clickSurCase(event, rect_quitter))
							set_launched = SDL_FALSE;
					}
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE: set_launched = SDL_FALSE;break;

					}
			}
	}
	free(police);
	free(police_titre);

	if (settings_asked){
		SDL_RenderClear(renderer);
		settings(window, renderer, map, pack_texture);
	}
	else
		menu(window, renderer, map, pack_texture);
}

void menu(SDL_Window *window, SDL_Renderer *renderer, case_t *map, SDL_Texture *pack_texture){
/**Fonction affichant un menu permettant a l utilisateur de naviguer dans le programme**/
	SDL_Rect rect_jouer, rect_editeur, rect_quitter;
	const int taille_police = 72;

	rect_jouer.w = rect_editeur.w = rect_quitter.w = WIDTH-WIDTH*0.65;
	rect_jouer.h = rect_editeur.h = rect_quitter.h = taille_police + 10;
	rect_jouer.x = rect_editeur.x = rect_quitter.x = (WIDTH-rect_jouer.w)/2;
	rect_jouer.y = HEIGHT-3*(HEIGHT/4);
	rect_editeur.y = HEIGHT-2*(HEIGHT/4);
	rect_quitter.y = HEIGHT-1*(HEIGHT/4);

	TTF_Font *police = TTF_OpenFont(NOM_FONT, taille_police);

	if (!police)
		SDL_ExitWithError("Erreur du chargement de la police", window, renderer, NULL);

	load_matrice(map, 0);
	aff_map(map, renderer, pack_texture);

	SDL_SetRenderDrawColor(renderer, R_R,  R_G, R_B, 255);

	SDL_RenderFillRect(renderer, &rect_jouer);
	SDL_RenderFillRect(renderer, &rect_editeur);
	SDL_RenderFillRect(renderer, &rect_quitter);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderDrawRect(renderer, &rect_jouer);
	SDL_RenderDrawRect(renderer, &rect_editeur);
	SDL_RenderDrawRect(renderer, &rect_quitter);

	creerTexte(renderer, police, "JOUER", WIDTH/2 - 5 * 18, rect_jouer.y - 5);
	creerTexte(renderer, police, "EDITEUR", WIDTH/2 - 7 * 15, rect_editeur.y - 5);
	creerTexte(renderer, police, "OPTIONS", WIDTH/2 - 7 * 20, rect_quitter.y - 5);

 	SDL_RenderPresent(renderer);


	SDL_Event event;
	SDL_bool menu_launched = SDL_TRUE;
	SDL_bool jeu_asked = SDL_FALSE;
	SDL_bool editeur_asked = SDL_FALSE;
	SDL_bool setting_asked = SDL_FALSE;

	while (menu_launched){
        SDL_WaitEvent(&event);

			switch(event.type){
				case SDL_QUIT: menu_launched = SDL_FALSE;break;

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT){
						if (clickSurCase(event, rect_jouer)){
							jeu_asked = SDL_TRUE; 
							menu_launched = SDL_FALSE;
						}
						else if (clickSurCase(event, rect_editeur)){
							editeur_asked = SDL_TRUE;
							menu_launched = SDL_FALSE;
						}
						else if (clickSurCase(event, rect_quitter)){
							setting_asked = SDL_TRUE;
							menu_launched = SDL_FALSE;
						}
					}
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE: menu_launched = SDL_FALSE;break;
					}
			}
	}

	free(police);

	if (jeu_asked)
		lancer_jeu(window, renderer, pack_texture, map);
	else if (editeur_asked)
		editeur_map(window, renderer, map, pack_texture);
	else if (setting_asked)
		settings(window, renderer, map, pack_texture);
}

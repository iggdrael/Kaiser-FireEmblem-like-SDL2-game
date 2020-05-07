#include "libs/commun.h"

void editeur_map(SDL_Window *window, SDL_Renderer *renderer, case_t *map, SDL_Texture *pack_texture){
/**Fonction permettant d editer une map
 * Elle perment entre autre de :
 * Choisir des textures depuis une deuxieme fenetre
 * Remplir la carte avec cette texture avec la touche f
 * Charger une map depuis un fichier texte avec la touche c
 * Sauvegarder la map dans un fichier texte avec la touche s
**/

/**------------------Declaration de la fenetre et du renderer du pack de texture-------------**/

	SDL_Window *window_edit = NULL;
	SDL_Renderer *renderer_edit = NULL;

/**------------------Initialisation de la fenetre et du renderer du pack de texture----------**/

	window_edit = SDL_CreateWindow("Textures", WIDTH+15, 50, W_TEXTURES, H_TEXTURES, SDL_WINDOW_SHOWN);

	if(window_edit == NULL)
		SDL_ExitWithError("Erreur à la création de la fenetre\n", window_edit, NULL, NULL);

	renderer_edit = SDL_CreateRenderer(window_edit, -1, SDL_RENDERER_ACCELERATED);
	if(renderer_edit == NULL)
		SDL_ExitWithError("Erreur à la création du renderer\n", window_edit, renderer_edit, NULL);

/**------------------Declaration variables secondaires----------------------------------------**/

	SDL_bool editeur_launched = SDL_TRUE, clic_long_gauche = SDL_FALSE, clic_long_droit = SDL_FALSE;
    SDL_Event event;
	SDL_Rect rect_select;
	coords_t case_select;
	rect_select.w = rect_select.h = 24;
	int case_actuelle = 0;
	int n_map;

/**------------------Variables correspondant a l id des fenetres------------------------------**/

	Uint32 id_main_window = SDL_GetWindowID(window);
	Uint32 id_window_edit = SDL_GetWindowID(window_edit);

/**------------------Creation des textures----------------------------------------------------**/

	SDL_Texture *pack_textures_for_window = creerTexture(window_edit, renderer_edit, "imgs/packtexture.png");

/**------------------Affichage des textures dans la deuxieme fenetre--------------------------
 * ------------------Remplissage de la fenetre principale avec la tile case vide--------------**/

	SDL_RenderClear(renderer);
	SDL_SetRenderDrawBlendMode(renderer_edit, SDL_BLENDMODE_BLEND);
	aff_tile(renderer_edit, pack_textures_for_window, 0, 0, -1, 1);
	SDL_RenderPresent(renderer_edit);
	fill_map(map, VIDE);
	aff_map(map, renderer, pack_texture);
	SDL_RenderPresent(renderer);

/**------------------Debut du programme de l editeur------------------------------------------**/

    while (editeur_launched){
        SDL_WaitEvent(&event);

		if (event.window.windowID == id_main_window){
/**------------------Evenement sur fenetre principale-----------------------------------------**/

			switch(event.type){
				case SDL_QUIT: editeur_launched = SDL_FALSE;break;

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT){
						ajout_texture_case(map, event.button.y / LARGEUR_CASE, event.button.x / LARGEUR_CASE, case_actuelle);
						clic_long_gauche = SDL_TRUE;
					}
					else if (event.button.button == SDL_BUTTON_RIGHT){
						ajout_texture_case(map, event.button.y / LARGEUR_CASE, event.button.x / LARGEUR_CASE, VIDE);
						clic_long_droit = SDL_TRUE;
					}
					break;

				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT)
						clic_long_gauche = SDL_FALSE;
					else if (event.button.button == SDL_BUTTON_RIGHT)
						clic_long_droit = SDL_FALSE;
					break;

				case SDL_MOUSEMOTION:
				/**Si l utilisateur maintient le clic enfonce, on affiche les textures a l emplacement du curseur**/
					if (clic_long_gauche == SDL_TRUE)
						ajout_texture_case(map, event.button.y / LARGEUR_CASE, event.button.x / LARGEUR_CASE, case_actuelle);
					else if (clic_long_droit == SDL_TRUE){
						ajout_texture_case(map, event.button.y / LARGEUR_CASE, event.button.x / LARGEUR_CASE, VIDE);
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE: editeur_launched = SDL_FALSE;break;

						case SDLK_a: aff_matrice(map);break;
						case SDLK_f: fill_map(map, case_actuelle);break;

						case SDLK_s: save_map(map);break;

						case SDLK_c: 
							printf("Numero de la map a charger : ");
							scanf("%d", &n_map);
							load_matrice(map, n_map);
							break;
					}
					break;
				}
			}
			SDL_RenderClear(renderer);
			aff_map(map, renderer, pack_texture);
			SDL_RenderPresent(renderer);
		}
		else if (event.window.windowID == id_window_edit){
/**------------------Evenement sur fenetre textures------------------------------------------**/

			switch(event.type){
				case SDL_QUIT: editeur_launched = SDL_FALSE;break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							editeur_launched = SDL_FALSE;
							break;
					}
					break;

				case SDL_MOUSEBUTTONDOWN: 
					case_actuelle = (event.button.y / (H_TEXTURES / NOMBRE_BLOCS_HAUTEUR)) * NOMBRE_BLOCS_LARGEUR + (event.button.x / (W_TEXTURES / NOMBRE_BLOCS_LARGEUR));
					case_select = case_to_coords(case_actuelle);
					rect_select.x = case_select.y * 24;
					rect_select.y = case_select.x * 24;

					SDL_RenderClear(renderer_edit);
					aff_tile(renderer_edit, pack_textures_for_window, 0, 0, -1, 1);
					SDL_SetRenderDrawColor(renderer_edit, 255, 0, 0, 128);
					SDL_RenderFillRect(renderer_edit, &rect_select);
					SDL_SetRenderDrawColor(renderer_edit, 0, 0, 0, 255);
					SDL_RenderPresent(renderer_edit);
					break;
			}
		}
	}

/**------------------Liberation de la mémoire allouee----------------------------------------**/

	SDL_DestroyTexture(pack_textures_for_window);
	SDL_DestroyRenderer(renderer_edit);
	SDL_DestroyWindow(window_edit);

/**------------------Fin du programme de l editeur-------------------------------------------**/

	menu(window, renderer, map, pack_texture);
}
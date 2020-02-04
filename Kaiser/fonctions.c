#include "fonctions.h"

case_t *init_matrice(){
/**Fonction qui initialise et retourne la matrice representant la map**/
	int i, j, k;
	case_t *map = malloc(sizeof(case_t) * (N*M));

	if (map == NULL){
		fprintf(stderr, "Problème allocation mémoire\n");
		exit(EXIT_FAILURE);
	}

/**On alloue de la mémoire pour chaque case de la matrice**/
	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++){
			(map + i*M + j)->textures = malloc(sizeof(int) * MAX_TEXTURES);
			
			if ((map + i*M + j)->textures == NULL){
				fprintf(stderr, "Problème allocation mémoire\n"); 
				exit(EXIT_FAILURE);
			}
		}

	return map;
}

void detruire_matrice(case_t *map){
/**Fonction qui libere la memoire allouee a la matrice map**/
	int i, j;

	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			free((map + i*M + j)->textures);
	free(map);
}

void aff_matrice(case_t *A){
/**Fonction affichant le contenu de la matrice passee en parametre sur la sortie standard**/ 
    int i, j, k;

    for(i = 0 ; i < N; i++){
        for (j = 0 ; j < M ; j++){
			printf("[");
			for (k = 0; k < MAX_TEXTURES; k++)
            	printf("%d ", (A + M*i + j)->textures[k]);
			printf("]");
		}
        printf("\n");
    }
}

void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t){
/**Fonction de gestion d erreur qui affiche l erreur SDL rencontree et libere la memoire allouee avant de quitter le programme**/
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	if(t != NULL)
        SDL_DestroyTexture(t);
    if(r != NULL)
        SDL_DestroyRenderer(r);
    if(w != NULL)
        SDL_DestroyWindow(w);
    SDL_Quit();

    exit(EXIT_FAILURE);
}

SDL_Texture *creerTexture(SDL_Window *window, SDL_Renderer *renderer, char sourceIMG[30]){
/**Fonction qui cree et retourne une texture associee au renderer et a la source passes en parametres**/
	SDL_Surface *img_to_load = NULL;
	SDL_Texture *texture = NULL;
    
	img_to_load = IMG_Load(sourceIMG);
    if(img_to_load == NULL){
    	SDL_ExitWithError("Erreur à la création de l'image\n", window, renderer, NULL);
		exit(EXIT_FAILURE);
	}

	texture = SDL_CreateTextureFromSurface(renderer, img_to_load);
    SDL_FreeSurface(img_to_load);
    if(texture == NULL){
    	SDL_ExitWithError("Erreur à la création de la texture\n", window, renderer, texture);
		exit(EXIT_FAILURE);
	}

	return (texture);
}

void aff_tile(SDL_Renderer *renderer, SDL_Texture *texture, int i, int j, int case_actuelle){
/**Fonction affichant une portion de la texture sur le renderer (depuis sa case, -1 pour toute la texture)**/
	SDL_Rect Rect_dest;
    SDL_Rect Rect_source;

	if (case_actuelle == -1){
		if(SDL_RenderCopy(renderer, texture, NULL, NULL) != 0){
			SDL_ExitWithError("Erreur à l'affichage\n", 0, renderer, texture);
			exit(EXIT_FAILURE);
		}
	}
	else{
		coords_t coords = case_to_coords(case_actuelle);

		Rect_source.w = LARGEUR_TILE;
		Rect_dest.w   = LARGEUR_CASE;
		Rect_source.h = HAUTEUR_TILE;
		Rect_dest.h   = LARGEUR_CASE;

		Rect_dest.x = j * LARGEUR_CASE;
		Rect_dest.y = i * LARGEUR_CASE;
		Rect_source.x = coords.y * LARGEUR_TILE;
		Rect_source.y = coords.x * LARGEUR_TILE;

		if(SDL_RenderCopy(renderer, texture, &Rect_source, &Rect_dest) != 0){
			SDL_ExitWithError("Erreur à l'affichage\n", 0, renderer, texture);
			exit(EXIT_FAILURE);
		}
	}
}

void creerTexte(SDL_Renderer *renderer, TTF_Font *police, char *str, int x, int y){
/**Fonction affichant un texte "str" sur le renderer aux coordonees passees en parametres**/
	SDL_Surface *texte = NULL;
	SDL_Rect txtDestRect;
	SDL_Color NOIR = {0, 0, 0};

	texte = TTF_RenderUTF8_Blended(police, str, NOIR);
	if (!texte){
		fprintf (stderr, "Erreur a la creation du texte : %s\n", SDL_GetError ());
		exit (EXIT_FAILURE);
	}
	SDL_Texture * texte_tex = SDL_CreateTextureFromSurface(renderer, texte);
	if (!texte_tex){
		fprintf(stderr, "Erreur a la creation du rendu du texte : %s\n", SDL_GetError ());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(texte);
	txtDestRect.x = x;
    txtDestRect.y = y;
	SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
	SDL_RenderCopy(renderer, texte_tex, NULL, &txtDestRect);
	SDL_RenderPresent(renderer);
}

SDL_bool valides(int x, int y){
/**Fonction qui retourne TRUE si les coordonnees passees en parametres sont dans les limites de la matrice**/
	return ((x >= 0 && x < N) && (y >= 0 && y < M));
}

void save_map(case_t *map){
/**Fonction permettant de creer un fichier texte et d y sauvegarder une map**/ 
	/*FILE *fic = NULL;
	char fname[8] = "mapA.txt";

	while (access(fname, F_OK) != -1)
		fname[3]++;

	fic = fopen(fname, "w");

	if (fic == NULL){
        printf("Cannot open file\n");
        exit(EXIT_FAILURE);
    }

	int i, j;

	for(i = 0 ; i < N; i++){
        for (j = 0 ; j < M ; j++)
            fprintf(fic, "%d ", *(map + M*i + j));
		fprintf(fic, "\n");
    }
	fclose(fic);
	SDL_Log("Sauvegarde reussie !!\n");*/
}

void load_matrice(case_t *map){
/**Fonction permettant de charger la matrice "map" depuis un fichier texte**/
	/*FILE *fic = NULL;
	char fname[8] = "mapA.txt";

	//printf("Nom de la map a charger : ");
	//scanf("%s", fname);

	fic = fopen(fname, "r");
	if (fic == NULL) {
        printf("Cannot open file %s\n", fname);
        exit(EXIT_FAILURE);
    }

	int i, j, val_texture;

	for(i = 0; i < N; i++){
        for (j = 0 ; (j < M) && !feof(fic) ; j++){
			fscanf(fic, "%d ", &val_texture);
            *(map + M*i + j) = val_texture;
		}
    }
	fclose(fic);
	printf("La map a bien ete chargee.\n");*/
}

void aff_map(case_t *map, SDL_Renderer *renderer, SDL_Texture *pack_texture){
/**Fonction affichant les textures de la matrice "map" sur le renderer**/
	int i, j, k;

	for(i = 0 ; i < N; i++)
        for (j = 0; j < M; j++)
			for (k = 0; k < MAX_TEXTURES; k++){
				if ((map + M*i + j)->textures[k] != SUPR)
					aff_tile(renderer, pack_texture, i, j, (map + M*i + j)->textures[k]);
			}
	SDL_RenderPresent(renderer);
}

coords_t case_to_coords(int case_actuelle){
/**Fonction qui transforme la case passee en parametres en coordonnees 
 * de son emplacement dans le pack de texture et les retourne**/
	coords_t coords;

	coords.x = case_actuelle / NOMBRE_BLOCS_LARGEUR;
	coords.y = case_actuelle - (coords.x * NOMBRE_BLOCS_LARGEUR);

	return coords;
}

type_t type_texture(int case_actuelle){
/**Fonction qui retourne le type de la texture 
 * case vide, 
 * texture fond (ex : terre, eau), 
 * texture decor (ex : montagne, pont))
 * RP (ex : personnage, equipement)**/
	if (case_actuelle == 0)
		return VIDE;
	else if ((case_actuelle > 0 && case_actuelle < 332) || (case_actuelle >= 374 && case_actuelle < 412))
		return FOND;
	else if ((case_actuelle >= 332 && case_actuelle < 374) || (case_actuelle >= 412 && case_actuelle < 473))
		return DECOR;
	else
		return RP;
}

type_t type_case(int case_actuelle){
/**Fonction qui retourne le type de la case
 * Franchissable (ex : pierre)
 * Infranchissable (ex : lave)
 * RP (ex : personnage ou equipement)**/
	if (case_actuelle < 375)
		return LIBRE;
	else if (case_actuelle >= 375 && case_actuelle < 474)
		return NON_LIBRE;
	else if (case_actuelle >= 474)
		return RP;
}

void fill_map(case_t *map, int case_actuelle){
/**Fonction permettant de remplir la carte avec la tile selectionnee depuis ses coordonnees**/
	int i, j;

	for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
			ajout_texture_case(map, i, j, case_actuelle);
}

void ajout_texture_case(case_t *map,  int i, int j, int case_actuelle){
/**Fonction qui ecrase la case de la matrice par la "case actuelle" et qui remplace cette case a l ecran**/
	int type = type_texture(case_actuelle);

	if (type == VIDE){
		/**On reinitialise la case**/
		(map + i * M + j)->textures[0] = case_actuelle;
		(map + i * M + j)->textures[1] = SUPR;
		(map + i * M + j)->textures[2] = SUPR;
	}
	else if (type == FOND){
		/**On change le fond**/
		(map + i * M + j)->textures[0] = case_actuelle;
	}
	else if (type == DECOR){
		/**On change l element**/
		(map + i * M + j)->textures[1] = case_actuelle;
	}
	else if (type == RP){
		/**On change l element**/
		(map + i * M + j)->textures[2] = case_actuelle;
	}

	#ifdef DEBUG
		printf("type : %d, case_actuelle : %d, tex[0] : %d, text[1] : %d, tex[2] : %d\n\n", type, case_actuelle, (map + i * M + j)->textures[0], (map + i * M + j)->textures[1], (map + i * M + j)->textures[2]);
	#endif
}

void editeur_map(SDL_Window *window, SDL_Renderer *renderer){
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

	window_edit = SDL_CreateWindow("Textures", 1920-W_TEXTURES, 100, W_TEXTURES, H_TEXTURES, SDL_WINDOW_SHOWN);

	if(window_edit == NULL)
		SDL_ExitWithError("Erreur à la création de la fenetre\n", window_edit, NULL, NULL);

	renderer_edit = SDL_CreateRenderer(window_edit, -1, SDL_RENDERER_ACCELERATED);
	if(renderer_edit == NULL)
		SDL_ExitWithError("Erreur à la création du renderer\n", window_edit, renderer_edit, NULL);

/**------------------Declaration variables secondaires----------------------------------------**/
	
	case_t *map = init_matrice();
	SDL_bool editeur_launched = SDL_TRUE, clic_long_gauche = SDL_FALSE, clic_long_droit = SDL_FALSE;
    SDL_Event event;
	int case_actuelle = 0;

/**------------------Variables correspondant a l id des fenetres------------------------------**/

	Uint32 id_main_window = SDL_GetWindowID(window);
	Uint32 id_window_edit = SDL_GetWindowID(window_edit);

/**------------------Creation des textures----------------------------------------------------**/

	SDL_Texture *pack_textures_for_window = creerTexture(window_edit, renderer_edit, "packtexture.png");
	SDL_Texture *pack_texture = creerTexture(window, renderer, "packtexture.png");

/**------------------Affichage des textures dans la deuxieme fenetre--------------------------
 * ------------------Remplissage de la fenetre principale avec la tile case vide--------------**/

	aff_tile(renderer_edit, pack_textures_for_window, 0, 0, -1);
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
						ajout_texture_case(map, event.button.y / LARGEUR_CASE, event.button.x / LARGEUR_CASE, 0);
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
						ajout_texture_case(map, event.button.y / LARGEUR_CASE, event.button.x / LARGEUR_CASE, 0);
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE: editeur_launched = SDL_FALSE;break;

						case SDLK_a: aff_matrice(map);break;
						case SDLK_f: fill_map(map, case_actuelle);break;
						
						case SDLK_s: save_map(map);break;

						case SDLK_c:
							load_matrice(map);
							aff_map(map, renderer, pack_texture);
							break;
					}
					break;
				}
			}
			SDL_RenderClear(renderer);
			//SDL_FillRect(renderer, NULL, SDL_MapRGB(renderer->format, 255, 255, 255));
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

				case SDL_MOUSEBUTTONDOWN: case_actuelle = (event.button.y / (H_TEXTURES / NOMBRE_BLOCS_HAUTEUR)) * NOMBRE_BLOCS_LARGEUR + (event.button.x / (W_TEXTURES / NOMBRE_BLOCS_LARGEUR));
			}
		}
	}

/**------------------Liberation de la mémoire allouee----------------------------------------**/

	SDL_DestroyTexture(pack_textures_for_window);
	SDL_DestroyTexture(pack_texture);
	SDL_DestroyRenderer(renderer_edit);
	SDL_DestroyWindow(window_edit);
	detruire_matrice(map);

/**------------------Fin du programme de l editeur-------------------------------------------**/
}


void menu(SDL_Window *window, SDL_Renderer *renderer){
/**Fonction affichant un menu permettant a l utilisateur de naviguer dans le programme**/
	SDL_Event event;
	SDL_bool menu_launched = SDL_TRUE;
	SDL_Texture *background = NULL;
	TTF_Font *police = TTF_OpenFont("caviardreams.ttf", 72);

	if (!police)
		SDL_ExitWithError("Erreur du chargement de la police", window, renderer, background);

	background = creerTexture(window, renderer, "background.png");
	SDL_RenderCopy(renderer, background, NULL, NULL);
	creerTexte(renderer, police, "Jouer", WIDTH/2-72*2.5, HEIGHT-3*(HEIGHT/4));
	creerTexte(renderer, police, "Editeur", WIDTH/2-72*2.5, HEIGHT-2*(HEIGHT/4));
	creerTexte(renderer, police, "Quitter", WIDTH/2-72*2.5, HEIGHT-1*(HEIGHT/4));

 	SDL_RenderPresent(renderer);

	while (menu_launched){
        SDL_WaitEvent(&event);

			switch(event.type){
				case SDL_QUIT: menu_launched = SDL_FALSE;break;

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT){
						if (	event.button.y > HEIGHT-3*(HEIGHT/4)-72 
							&& 	event.button.y < HEIGHT-2*(HEIGHT/4)-72
							){
							printf("Jouer\n");
						}
						else if (event.button.y > HEIGHT-2*(HEIGHT/4)-72
							&&	event.button.y < HEIGHT-1*(HEIGHT/4)-72
							){
							SDL_RenderClear(renderer);
							editeur_map(window, renderer);
						}
						else if (event.button.y > HEIGHT-1*(HEIGHT/4)-72
							&&	event.button.y < HEIGHT-72
							){
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
	SDL_DestroyTexture(background);
}
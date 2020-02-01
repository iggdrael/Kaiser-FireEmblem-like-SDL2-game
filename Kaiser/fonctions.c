#include "fonctions.h"

int *init_matrice(){
/**Fonction qui initialise et retourne la matrice representant la map**/
	int i, j;
	int *map = malloc(sizeof(int) * (N*M));

	if (map == NULL){
		fprintf(stderr, "Problème allocation mémoire\n");
		free(map); 
		exit(EXIT_FAILURE);
	}

	return map;
}

void aff_matrice(int *A){
/**Fonction affichant le contenu de la matrice passee en parametre sur la sortie standard**/ 
    int i, j;
    for(i = 0 ; i < N; i++){
        for (j = 0 ; j < M ; j++)
            printf("%d ", *(A + M*i + j));
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

void save_map(int *map){
/**Fonction permettant de creer un fichier texte et d y sauvegarder une map**/ 
	FILE *fic = NULL;
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
	SDL_Log("Sauvegarde reussie !!\n");
}

void load_matrice(int *map){
/**Fonction permettant de charger la matrice "map" depuis un fichier texte**/
	FILE *fic = NULL;
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
	printf("La map a bien ete chargee.\n");
}

void aff_map(int *map, SDL_Renderer *renderer, SDL_Texture *pack_texture){
/**Fonction affichant les textures de la matrice "map" sur le renderer**/
	int i, j;

	for(i = 0 ; i < N; i++)
        for (j = 0; j < M; j++)
			aff_tile(renderer, pack_texture, i, j, *(map + M*i + j));
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

void fill_map(SDL_Renderer *renderer, SDL_Texture *pack_texture, int *map, int case_actuelle){
/**Fonction permettant de remplir la carte avec la tile selectionnee depuis ses coordonnees**/
	int i, j;

	for (i = 0; i < N; i++)
        for (j = 0; j < M; j++){
			aff_tile(renderer, pack_texture, i, j, case_actuelle);
			*(map + M*i + j) = case_actuelle; 
		}
    SDL_RenderPresent(renderer);
}

void ecraser_case_actuelle(SDL_Renderer *renderer, SDL_Texture *texture, int *map,  int i, int j, int case_actuelle){
/**Fonction qui ecrase la case de la matrice par la "acse actuelle" et qui remplace cette case a l ecran**/
	*(map + i * M + j) = case_actuelle;
	aff_tile(renderer, texture, i, j, case_actuelle);
	SDL_RenderPresent(renderer);
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
	
	int *map = init_matrice();
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
	fill_map(renderer, pack_texture, map, 0);

/**------------------Debut du programme de l editeur------------------------------------------**/

    while (editeur_launched){
        SDL_WaitEvent(&event);

		if (event.window.windowID == id_main_window){
/**------------------Evenement sur fenetre principale-----------------------------------------**/

			switch(event.type){
				case SDL_QUIT: editeur_launched = SDL_FALSE;break;

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT){
						ecraser_case_actuelle(renderer, pack_texture, map, event.button.y / LARGEUR_CASE, event.button.x / LARGEUR_CASE, case_actuelle);
						clic_long_gauche = SDL_TRUE;
					}  
					else if (event.button.button == SDL_BUTTON_RIGHT){
						ecraser_case_actuelle(renderer, pack_texture, map, event.button.y / LARGEUR_CASE, event.button.x / LARGEUR_CASE, 0);
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
						ecraser_case_actuelle(renderer, pack_texture, map, event.button.y / LARGEUR_CASE, event.button.x / LARGEUR_CASE, case_actuelle);
					else if (clic_long_droit == SDL_TRUE){
						ecraser_case_actuelle(renderer, pack_texture, map, event.button.y / LARGEUR_CASE, event.button.x / LARGEUR_CASE, 0);
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE: editeur_launched = SDL_FALSE;break;

						case SDLK_a: aff_matrice(map);break;
						case SDLK_f: fill_map(renderer, pack_texture, map, case_actuelle);break;
						
						case SDLK_s: save_map(map);break;

						case SDLK_c:
							load_matrice(map);
							aff_map(map, renderer, pack_texture);
							break;
					}
					break;
				}
			}
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
	free(map);

/**------------------Fin du programme de l editeur-------------------------------------------**/
}
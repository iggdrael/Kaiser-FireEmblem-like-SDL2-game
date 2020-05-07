#include "libs/commun.h"

case_t *init_matrice(){
/**Fonction qui initialise et retourne la matrice representant la map**/
	int i, j;

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
			(map + i*M + j)->perso = malloc(sizeof(perso_t));

			if ((map + i*M + j)->perso == NULL){
				fprintf(stderr, "Problème allocation mémoire\n");
				exit(EXIT_FAILURE);
			}
			(map + i*M + j)->is_perso = SDL_FALSE;
			clean_perso((map + i*M + j)->perso);
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

void aff_tile(SDL_Renderer *renderer, SDL_Texture *texture, int i, int j, int case_actuelle, float multi){
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
		Rect_dest.w   = (int)(LARGEUR_CASE * multi);
		Rect_source.h = HAUTEUR_TILE;
		Rect_dest.h   = (int)(LARGEUR_CASE * multi);

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
	SDL_Color NOIR = {P_R, P_G, P_B};

	texte = TTF_RenderUTF8_Blended(police, str, NOIR);
	if (!texte){
		fprintf (stderr, "Erreur a la creation du texte : %s\n", SDL_GetError ());
		exit(EXIT_FAILURE);
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
}

void save_map(case_t *map){
/**Fonction permettant de creer un fichier texte et d y sauvegarder une map**/
	FILE *fic = NULL;
	char fname[8] = "map1.txt";

	while (access(fname, F_OK) != -1)
		fname[3]++;

	fic = fopen(fname, "w");

	if (fic == NULL){
        printf("Cannot open file\n");
        exit(EXIT_FAILURE);
    }

	int i, j, k;

	for(i = 0 ; i < N; i++){
        for (j = 0 ; j < M ; j++){
			fprintf(fic, "[");
			for (k = 0; k < MAX_TEXTURES; k++)
            	fprintf(fic, "%d ", (map + M*i + j)->textures[k]);
			fprintf(fic, "]");
		}
        fprintf(fic, "\n");
    }

	fclose(fic);
	SDL_Log("Sauvegarde reussie !!\n");
}

void load_matrice(case_t *map, int n_map){
/**Fonction permettant de charger la matrice "map" depuis un fichier texte**/
	FILE *fic = NULL;
	char fname[13] = "maps/map0.txt";

	fname[8] = '0' + n_map;

	fic = fopen(fname, "r");
	if (fic == NULL) {
        printf("Cannot open file %s\n", fname);
        exit(EXIT_FAILURE);
    }

	int i, j, val1, val2, val3;

	for(i = 0; i < N; i++){
        for (j = 0 ; (j < M) && !feof(fic) ; j++){
			fscanf(fic, "[%d %d %d ]", &val1, &val2, &val3);
            (map + M*i + j)->textures[0] = val1;
            (map + M*i + j)->textures[1] = val2;
            (map + M*i + j)->textures[2] = val3;
		}
		fscanf(fic, "\n");
    }
	fclose(fic);
}

void aff_map(case_t *map, SDL_Renderer *renderer, SDL_Texture *pack_texture){
/**Fonction affichant les textures de la matrice "map" sur le renderer**/
	int i, j, k;
	SDL_Rect rect_select;
	rect_select.w = rect_select.h = LARGEUR_CASE;

	for(i = 0 ; i < N; i++)
        for (j = 0; j < M; j++)
			for (k = 0; k < MAX_TEXTURES; k++){
				if ((map + M*i + j)->textures[k] != RIEN){
					aff_tile(renderer, pack_texture, i, j, (map + M*i + j)->textures[k], 1);

					if ((map + M*i + j)->is_perso == SDL_TRUE){
						if ((map + M*i + j)->perso->is_dep == SDL_TRUE){
							rect_select.x = j * LARGEUR_CASE;
							rect_select.y = i * LARGEUR_CASE;
							SDL_SetRenderDrawColor(renderer, 0, 0, 0, 64);
							SDL_RenderFillRect(renderer, &rect_select);
						}
					}
				}
			}
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
	if ((case_actuelle >= 374 && case_actuelle < 474) || case_actuelle == 358)
		return NON_LIBRE;
	else if (case_actuelle < 374 && case_actuelle != RIEN)
		return LIBRE;
	else if (case_actuelle >= 474)
		return RP;
	return -1;
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

	if (valides(i, j)){
		int type = type_texture(case_actuelle);

		if (type == VIDE){
			/**On reinitialise la case**/
			(map + i * M + j)->textures[0] = case_actuelle;
			(map + i * M + j)->textures[1] = RIEN;
			(map + i * M + j)->textures[2] = RIEN;
		}
		else if (type == FOND){
			/**On change le fond**/
			(map + i * M + j)->textures[0] = case_actuelle;
		}
		else if (type == DECOR){
			/**On change le decor**/
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
}

SDL_bool clickSurCase(SDL_Event click, SDL_Rect caseRect){
/**Fonction testant si un click a lieu dans le rectangle en paramètres**/
	return (	click.button.y > caseRect.y
			&& 	click.button.y < caseRect.y + caseRect.h
			&& 	click.button.x > caseRect.x
			&&	click.button.x < caseRect.x + caseRect.w);
}
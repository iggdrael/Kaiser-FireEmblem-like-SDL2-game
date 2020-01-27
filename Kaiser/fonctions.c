#include "fonctions.h"

void creer_map_rendu(SDL_Window *window, SDL_Renderer *renderer){
	SDL_Texture *texture_hud = creerTexture(window, renderer, "src/Kaiser/img/gui.png");
	SDL_Texture *texture_case = creerTexture(window, renderer, "src/Kaiser/img/case.jpg");
	int x, y;

	aff_texture(window, renderer, texture_hud, 0, 0, HUD, 0);

    for(x = 100; x < (M*LARGEUR_CASE); x += LARGEUR_CASE)
        for (y = 100; y < (N*LARGEUR_CASE); y += LARGEUR_CASE)
			aff_texture(window, renderer, texture_case, x, y, CASE, LARGEUR_CASE);

	SDL_DestroyTexture(texture_hud);
	SDL_DestroyTexture(texture_case);
}

int *init_map(){
	int i, j;
	int *grille = malloc(sizeof(int) * (N*M));

	if (grille == NULL){
		fprintf(stderr, "Problème allocation mémoire\n");
		free(grille); 
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
			*(grille + M*i + j) = VIDE;

	return grille;
}

void aff_map(int *A)
{
    int i, j;
    for(i = 0 ; i < N; i++){
        for (j = 0 ; j < M ; j++)
            printf("%d ", *(A + M*i + j));
        printf("\n");
    }
}

void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t)
{
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

void aff_texture(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, int x_texture, int y_texture, int type_texture, int type_largeur){
	SDL_Rect DestR;
	int out_render;

	switch (type_texture){
		case HUD:
			out_render = SDL_RenderCopy(renderer, texture, NULL, NULL);
			break;
		case CASE:
			DestR.x = x_texture;
			DestR.y = y_texture;
			DestR.w = DestR.h = type_largeur;
			out_render = SDL_RenderCopy(renderer, texture, NULL, &DestR);
			break;
	}

	if(out_render != 0){
		SDL_ExitWithError("Erreur à l'affichage\n", window, renderer, texture);
		exit(EXIT_FAILURE);
	}
    SDL_RenderPresent(renderer);
}

void select_tile(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int i, int j){
	SDL_Rect Rect_dest;
    SDL_Rect Rect_source;
    Rect_source.w = LARGEUR_TILE;
    Rect_dest.w   = LARGEUR_EDIT;
    Rect_source.h = HAUTEUR_TILE;
    Rect_dest.h   = LARGEUR_EDIT;

	Rect_dest.x = y * LARGEUR_EDIT;
    Rect_dest.y = x * LARGEUR_EDIT;
    Rect_source.x = j * LARGEUR_TILE;
    Rect_source.y = i * LARGEUR_TILE;

	if(SDL_RenderCopy(renderer, texture, &Rect_source, &Rect_dest) != 0){
		SDL_ExitWithError("Erreur à l'affichage\n", 0, renderer, texture);
		exit(EXIT_FAILURE);
	}
    //SDL_RenderPresent(renderer);
}

void creerTexte(SDL_Renderer *renderer, TTF_Font *police, char str[], int x, int y){
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
	return ((x >= 0 && x < N) && (y >= 0 && y < M));
}

void save_map(int *map){
	FILE *fic = NULL;
	char fname[24] = "src/kaiser/maps/mapA.txt";

	while (access(fname, F_OK) != -1 )
		fname[19]++;

	fic = fopen(fname, "w");

	if (fic == NULL ) {
        printf( "Cannot open file\n");
        exit(EXIT_FAILURE);
    }

	int i, j;

	for(i = 0 ; i < N; i++){
        for (j = 0 ; j < M ; j++)
            fprintf(fic, "%d ", *(map + M*i + j));
		fprintf(fic, "\n");
    }
	fclose(fic);
}

void load_map(int *map, SDL_Renderer *renderer, SDL_Texture *texture_tiles){
	FILE *fic = NULL;
	char mapname[24];
	char fname[24] = "src/kaiser/maps/";

	printf("Nom de la map à charger : ");
	scanf("%s", mapname);
	strcat(fname, mapname);

	fic = fopen(fname, "r");
	if (fic == NULL) {
        printf("Cannot open file\n");
        exit(EXIT_FAILURE);
    }

	int i, j, texture_actuelle_x, texture_actuelle_y, val_texture;
	float p;

	for(i = 0 ; i < N; i++){
        for (j = 0 ; (j < M) && !feof(fic) ; j++){
			fscanf(fic, "%d ", &val_texture);
            *(map + M*i + j) = val_texture;
			
			p = (float)val_texture / (float)NOMBRE_BLOCS_LARGEUR;
			texture_actuelle_x = (int)p;
			p = (p - texture_actuelle_x) * 100;
			texture_actuelle_y = NOMBRE_BLOCS_LARGEUR * p / 100;
			select_tile(renderer, texture_tiles, i, j, texture_actuelle_x, texture_actuelle_y);
		}
    }
	fclose(fic);
	SDL_RenderPresent(renderer);
}

void editeur_map(SDL_Window *window, SDL_Renderer *renderer, int *map){
	/*************************************************************/
	SDL_Window *window_edit = NULL;
	SDL_Window *window_actuelle = NULL;
	SDL_Renderer *renderer_edit = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
        SDL_ExitWithError("Initialisation SDL", NULL, NULL, NULL);

	window_edit = SDL_CreateWindow("Textures", 1920-W_TEXTURES, 100, W_TEXTURES, H_TEXTURES, SDL_WINDOW_SHOWN);

	if(window_edit == NULL)
		SDL_ExitWithError("Erreur à la création de la fenetre\n", window_edit, NULL, NULL);

	renderer_edit = SDL_CreateRenderer(window_edit, -1, SDL_RENDERER_ACCELERATED);
	if(renderer_edit == NULL)
		SDL_ExitWithError("Erreur à la création du renderer\n", window_edit, renderer_edit, NULL);

	Uint32 id_window = SDL_GetWindowID(window), id_window_edit = SDL_GetWindowID(window_edit);

	/*************************************************************/
	SDL_Texture *texture_case_vide = creerTexture(window, renderer, "src/Kaiser/img/texture_hach.jpg");
	SDL_Texture *texture_textures = creerTexture(window_edit, renderer_edit, "src/Kaiser/img/texturesfull.png");
	SDL_Texture *texture_tiles = creerTexture(window, renderer, "src/Kaiser/img/texturesfull.png");


	SDL_bool editeur_launched = SDL_TRUE, clic_long_gauche = SDL_FALSE, clic_long_droit = SDL_FALSE;
    SDL_Event event;
	int case_actuelle = 0, x, y, texture_actuelle_x, texture_actuelle_y;

	aff_texture(window_edit, renderer_edit, texture_textures, 0, 0, HUD, 0);

	for (x = 0; x < (M*LARGEUR_EDIT)+LARGEUR_EDIT; x += LARGEUR_EDIT)
        for (y = 0; y < (N*LARGEUR_EDIT)+LARGEUR_EDIT; y += LARGEUR_EDIT)
			aff_texture(window, renderer, texture_case_vide, x, y, CASE, LARGEUR_EDIT);

    while (editeur_launched){
        SDL_WaitEvent(&event);
		if (event.window.windowID == id_window){
			switch(event.type){
				case SDL_QUIT:
					editeur_launched = SDL_FALSE;
					break;
				case SDL_MOUSEBUTTONDOWN:
					x = event.button.y / LARGEUR_EDIT;
					y = event.button.x / LARGEUR_EDIT;
					SDL_Log("%d-%d  --> map[%d][%d]\n", event.button.x, event.button.y, x, y);

					if (event.button.button == SDL_BUTTON_LEFT){
						*(map + x * M + y) = case_actuelle;
						select_tile(renderer, texture_tiles, x, y, texture_actuelle_x, texture_actuelle_y);
					    SDL_RenderPresent(renderer);
						clic_long_gauche = SDL_TRUE;
					}        
					else if (event.button.button == SDL_BUTTON_RIGHT){
						*(map + x * M + y) = VIDE;
						aff_texture(window, renderer, texture_case_vide, (y * LARGEUR_EDIT), (x * LARGEUR_EDIT), CASE, LARGEUR_EDIT);
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
					x = event.button.y / LARGEUR_EDIT;
					y = event.button.x / LARGEUR_EDIT;

					if (clic_long_gauche == SDL_TRUE){
						*(map + x * M + y) = case_actuelle;
						select_tile(renderer, texture_tiles, x, y, texture_actuelle_x, texture_actuelle_y);
					    SDL_RenderPresent(renderer);
					}
					else if (clic_long_droit == SDL_TRUE){
						*(map + x * M + y) = VIDE;
						aff_texture(window, renderer, texture_case_vide, (y * LARGEUR_EDIT), (x * LARGEUR_EDIT), CASE, LARGEUR_EDIT);
					}
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							editeur_launched = SDL_FALSE;
							break;
						case SDLK_a:
							aff_map(map);
							break;
						case SDLK_f:
							for (x = 0; x < N+1; x++)
        						for (y = 0; y < M+1; y++)
									select_tile(renderer, texture_tiles, x, y, texture_actuelle_x, texture_actuelle_y);
						    SDL_RenderPresent(renderer);
							break;
						case SDLK_s:
							save_map(map);
							break;
						case SDLK_c:
							load_map(map, renderer, texture_tiles);
							break;
					}
					break;
			}
		}
		else if (event.window.windowID == id_window_edit){
			switch(event.type){
				case SDL_QUIT:
					editeur_launched = SDL_FALSE;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							editeur_launched = SDL_FALSE;
							break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					texture_actuelle_x = event.button.y / (H_TEXTURES / NOMBRE_BLOCS_HAUTEUR);
					texture_actuelle_y = event.button.x / (W_TEXTURES / NOMBRE_BLOCS_LARGEUR);
					case_actuelle = texture_actuelle_x * NOMBRE_BLOCS_LARGEUR + texture_actuelle_y;

					SDL_Log("%d-%d  --> textures[%d][%d]\n", event.button.x, event.button.y, texture_actuelle_x, texture_actuelle_y);
				break;
			}
		}
	}
	SDL_DestroyTexture(texture_case_vide);
	SDL_DestroyTexture(texture_textures);
	SDL_DestroyTexture(texture_tiles);

	SDL_DestroyRenderer(renderer_edit);
	SDL_DestroyWindow(window_edit);
}
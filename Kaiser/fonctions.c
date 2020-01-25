#include "fonctions.h"

void creer_map_rendu(SDL_Window *window, SDL_Renderer *renderer){
	SDL_Texture *texture_hud = creerTexture(window, renderer, "src/Kaiser/img/hud.png");
	SDL_Texture *texture_case = creerTexture(window, renderer, "src/Kaiser/img/case.jpg");
	int x, y;

	aff_texture(window, renderer, texture_hud, 0, 0, HUD, 0);

    for(x = 0; x < (M*LARGEUR_CASE); x += LARGEUR_CASE)
        for (y = 0; y < (N*LARGEUR_CASE); y += LARGEUR_CASE)
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

void editeur_map(SDL_Window *window, SDL_Renderer *renderer, int *map){
	SDL_Texture *texture_case_vide = creerTexture(window, renderer, "src/Kaiser/img/case_vide.png");
	SDL_Texture *texture_case_presque_vide = creerTexture(window, renderer, "src/Kaiser/img/case_presque_vide.jpg");
	SDL_Texture *texture_ciel = creerTexture(window, renderer, "src/Kaiser/img/ciel.jpg");
	SDL_Texture *texture_eau = creerTexture(window, renderer, "src/Kaiser/img/eau.jpg");
	SDL_Texture *texture_terre = creerTexture(window, renderer, "src/Kaiser/img/terre.jpg");
	SDL_Texture *texture_herbe = creerTexture(window, renderer, "src/Kaiser/img/herbe.jpg");
	SDL_Texture *texture_actuelle = texture_eau;

	SDL_bool editeur_launched = SDL_TRUE;
    SDL_Event event;
	int case_actuelle = EAU, x, y;

	aff_texture(window, renderer, texture_ciel, 0, 0, HUD, 0);

	for (x = 0; x < (M*LARGEUR_EDIT); x += LARGEUR_EDIT)
        for (y = 0; y < (N*LARGEUR_EDIT); y += LARGEUR_EDIT)
			aff_texture(window, renderer, texture_case_vide, x, y, CASE, LARGEUR_EDIT);

    while (editeur_launched){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                editeur_launched = SDL_FALSE;
                break;
            case SDL_MOUSEBUTTONDOWN:
				x = event.button.y / LARGEUR_EDIT;
				y = event.button.x / LARGEUR_EDIT;
                if (event.button.button == SDL_BUTTON_LEFT){
					SDL_Log("%d-%d  --> map[%d][%d]\n", event.button.x, event.button.y, x, y);

                    *(map + x * M + y) = case_actuelle;
					aff_texture(window, renderer, texture_actuelle, (y * LARGEUR_EDIT), (x * LARGEUR_EDIT), CASE, LARGEUR_EDIT);
				}        
                else if (event.button.button == SDL_BUTTON_RIGHT){
                    *(map + x * M + y) = VIDE;
					aff_texture(window, renderer, texture_case_presque_vide, (y * LARGEUR_EDIT), (x * LARGEUR_EDIT), CASE, LARGEUR_EDIT);
				}
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        editeur_launched = SDL_FALSE;
                        break;
                    case SDLK_s:
                        //sauvegarderNiveau(carte);
                        break;
                    case SDLK_c:
                        //chargerNiveau(carte);
                        break;
                    case SDLK_KP_1:
						case_actuelle = EAU;
                        texture_actuelle = texture_eau;
                        break;
                    case SDLK_KP_2:
						case_actuelle = TERRE;
                        texture_actuelle = texture_terre;
                        break;
                    case SDLK_KP_3:
						case_actuelle = HERBE;
                        texture_actuelle = texture_herbe;
                        break;
                    case SDLK_KP_4:
						aff_map(map);
						printf("\n\n");
                        break;
                }
                break;
        }
	}
	SDL_DestroyTexture(texture_eau);
	SDL_DestroyTexture(texture_terre);
	SDL_DestroyTexture(texture_herbe);
	SDL_DestroyTexture(texture_case_vide);
	SDL_DestroyTexture(texture_case_presque_vide);
	SDL_DestroyTexture(texture_ciel);
	SDL_DestroyTexture(texture_actuelle);
}
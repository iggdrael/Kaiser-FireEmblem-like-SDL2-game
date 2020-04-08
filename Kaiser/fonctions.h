#ifndef _FONCTIONS_H_
#define _FONCTIONS_H_

typedef enum libre_s{LIBRE, NON_LIBRE}libre_t; /**Types de cases**/
typedef enum type_s{FOND, DECOR, RP}type_t; /**Types de cases**/
#define VIDE 0
#define RIEN -1 /**Texture inexistante**/


typedef struct case_s{
	int *textures;
	struct perso_s *perso;
	SDL_bool is_perso;
}case_t;

typedef struct coords_s{int x, y;}coords_t;
/**Structure de coordonees x, y**/
/**
* \fn case_t *init_matrice(void)
*/
case_t *init_matrice();

/**
* \fn void detruire_matrice(case_t *map)
* \param map Carte à détruire.
*/
void detruire_matrice(case_t *map);

/**
* \fn void aff_matrice(case_t *A)
* \param A Matrice à afficher.
*/
void aff_matrice(case_t *A);

/**
* \fn void load_matrice(case_t *map, int n_map)
* \param map Charge la matrice.
* \param n_map numero de la map a charger
*/
void load_matrice(case_t *map, int n_map);

/**
* \fn void save_map(case_t *map)
* \param map Carte a sauvegarder
*/
void save_map(case_t *map);

/**
* \fn void aff_map(case_t *map, SDL_Renderer *renderer, SDL_Texture *pack_texture)
* \param map,renderer,packtexture Afffiche les textures de la matrice sur l'écran
*/
void aff_map(case_t *map, SDL_Renderer *renderer, SDL_Texture *pack_texture);

/**
* \fn SDL_Texture *creerTexture(SDL_Window *window, SDL_Renderer *renderer, char sourceIMG[30])
* \param window,renderer,sourceIMG[30] Creer une texture associee au renderer et à la source passes en parametres
*/
SDL_Texture *creerTexture(SDL_Window *window, SDL_Renderer *renderer, char sourceIMG[30]);

/**
* \fn void aff_tile(SDL_Renderer *renderer, SDL_Texture *texture, int i, int j, int case_actuelle)
* \param renderer,texture,i,j,case_actuelle Affiche une portion de la texture sur le renderer
*/
void aff_tile(SDL_Renderer *renderer, SDL_Texture *texture, int i, int j, int case_actuelle,  float multi);

/**
* \fn coords_t case_to_coords(int case_actuelle)
* \param case_actuelle Transforme la case en coordonees de son emplacement dans le pack de texture
*/
coords_t case_to_coords(int case_actuelle);

/**
* \fn void fill_map(case_t *map, int case_actuelle)
* \param map,case_actuelle Fonction permettant de remplir la carte avec la touche selectionnee depuis ses coordonnees
*/
void fill_map(case_t *map, int case_actuelle);

/**
* \fn void ajout_texture_case(case_t *map,  int i, int j, int case_actuelle)
* \param map,i,j,case_actuelle  Ecrase la case de la matrice par case_actuelle et remplace cette case à l'écran
*/
void ajout_texture_case(case_t *map,  int i, int j, int case_actuelle);

/**
* \fn void editeur_map(SDL_Window *window, SDL_Renderer *renderer)
* \param window,renderer Edition d'une carte, choix texture,remplir,charger un carte deja creer,sauvegarder avec les touche f,c et s
*/
void editeur_map(SDL_Window *window, SDL_Renderer *renderer, case_t *map, SDL_Texture *pack_texture);

/**
* \fn SDL_bool valides(int x, int y)
* \param x,y coordonnees dans une matrice
*/
SDL_bool valides(int x, int y);

/**
* \fn void creerTexte(SDL_Renderer *renderer, TTF_Font *police, char *str, int x, int y)
* \param renderer,police,str,x,y Affiche un texte a l'écran au coordonees x y
*/
void creerTexte(SDL_Renderer *renderer, TTF_Font *police, char *str, int x, int y);

/**
* \fn void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t)
* \param massage,x,r,t  Gestion des erreurs et l'affiche
*/
void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);

/**
* \fn type_t type_case(int case_actuelle)
* \param case_actuelle Savoir le type de la case actuelle
*/
type_t type_case(int case_actuelle);

/**
* \fn type_t type_texture(int case_actuelle)
* \param case_actuelle Type de la texture
*/
type_t type_texture(int case_actuelle);

/**
* \fn void settings(SDL_Window *window, SDL_Renderer *renderer)
* \param window,renderer Affiche les paramètres du jeu
*/
void settings(SDL_Window *window, SDL_Renderer *renderer, case_t *map, SDL_Texture *pack_texture);

/**
* \fn void menu(SDL_Window *window, SDL_Renderer *renderer)
* \param window,renderer Affiche le menu
*/
void menu(SDL_Window *window, SDL_Renderer *renderer, case_t *map, SDL_Texture *pack_texture);

/**
* \fn SDL_bool clickSurCase(SDL_Event click, SDL_Rect caseRect);
* \param click, caseRect Test si un click est dans un rectangle
*/
SDL_bool clickSurCase(SDL_Event click, SDL_Rect caseRect);

#endif
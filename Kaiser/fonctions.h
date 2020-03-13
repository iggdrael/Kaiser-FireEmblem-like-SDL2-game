#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//#define DEBUG SDL_TRUE
int WIDTH;
int HEIGHT;
//#define WIDTH 1280 /**Largeur de la fenetre principale**/
//#define HEIGHT 720 /**Hauteur de la fenetre principale**/
#define W_TEXTURES 544 /**Largeur de la fenetre du pack de texture**/
#define H_TEXTURES 960 /**Hauteur de la fenetre du pack de texture**/
#define LARGEUR_TILE 32 /**Taille d un tile en pixels**/
#define HAUTEUR_TILE 32
#define NOMBRE_BLOCS_LARGEUR 17 /**Nombre de tiles sur le pack de texture**/
#define NOMBRE_BLOCS_HAUTEUR 30
#define MAX_TEXTURES 3 /**Nombre maximum de textures qu une case de la matrice peut avoir**/

#define M 39 /**Matrice de N * M cases, N est calculee automatiquement pour rester en 16/9**/
#define N (int)(M / (16.0/9.0) + 1)

#define LARGEUR_CASE (WIDTH / M) /**Largeur en pixels d une case en fonction de la taille de la fenetre**/

typedef enum type_s{VIDE, LIBRE, NON_LIBRE, RP, FOND, DECOR}type_t; /**Types de cases**/
#define SUPR -1 /**Texture inexistante**/

typedef struct case_s{
	int *textures;
}case_t;

typedef struct coords_s{int x, y;}coords_t;
/**Structure de coordonees x, y**/

/**Debut trucs jeu**/

typedef struct perso_s{
	int classe;
	int race;
	int pv;
	int atk;
	int def;
	int esq;
}perso_t;

enum{GUERRIER, MAGE, VOLEUR, ARCHER, PRETRE};
enum{HUMAIN, GOBELIN, ELFE, NAIN};


/**Fin jeu**/

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
* \fn void load_matrice(case_t *map)
* \param map Charge la matrice.
*/
void load_matrice(case_t *map);

/**
* \fn void save_map(case_t *map)
* \param map Carte à sauvegarder
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
void aff_tile(SDL_Renderer *renderer, SDL_Texture *texture, int i, int j, int case_actuelle);

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
void editeur_map(SDL_Window *window, SDL_Renderer *renderer);

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
void settings(SDL_Window *window, SDL_Renderer *renderer);

/**
* \fn void menu(SDL_Window *window, SDL_Renderer *renderer)
* \param window,renderer Affichele menu
*/
void menu(SDL_Window *window, SDL_Renderer *renderer);

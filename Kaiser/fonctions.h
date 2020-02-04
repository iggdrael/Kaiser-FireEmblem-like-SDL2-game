#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//#define DEBUG SDL_TRUE

#define WIDTH 1366 /**Largeur de la fenetre principale**/
#define HEIGHT 768 /**Hauteur de la fenetre principale**/
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


case_t *init_matrice();
void detruire_matrice(case_t *map);
void aff_matrice(case_t *A);
void load_matrice(case_t *map);
void save_map(case_t *map);
void aff_map(case_t *map, SDL_Renderer *renderer, SDL_Texture *pack_texture);
SDL_Texture *creerTexture(SDL_Window *window, SDL_Renderer *renderer, char sourceIMG[30]);
void aff_tile(SDL_Renderer *renderer, SDL_Texture *texture, int i, int j, int case_actuelle);
coords_t case_to_coords(int case_actuelle);
void fill_map(case_t *map, int case_actuelle);
void ajout_texture_case(case_t *map,  int i, int j, int case_actuelle);
void editeur_map(SDL_Window *window, SDL_Renderer *renderer);
SDL_bool valides(int x, int y);
void creerTexte(SDL_Renderer *renderer, TTF_Font *police, char *str, int x, int y);
void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);
type_t type_case(int case_actuelle);
type_t type_texture(int case_actuelle);

void menu(SDL_Window *window, SDL_Renderer *renderer);
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define WIDTH 1366 /**Largeur de la fenetre principale**/
#define HEIGHT 768 /**Hauteur de la fenetre principale**/
#define W_TEXTURES 544 /**Largeur de la fenetre du pack de texture**/
#define H_TEXTURES 960 /**Hauteur de la fenetre du pack de texture**/
#define LARGEUR_TILE 32 /**Taille d un tile en pixels**/
#define HAUTEUR_TILE 32
#define NOMBRE_BLOCS_LARGEUR 17 /**Nombre de tiles sur le pack de texture**/
#define NOMBRE_BLOCS_HAUTEUR 30

#define M 39 /**Matrice de N * M cases, N est calculee automatiquement pour rester en 16/9**/ 
#define N (int)(M / (16.0/9.0) + 1)

#define LARGEUR_CASE (WIDTH / M) /**Largeur en pixels d une case en fonction de la taille de la fenetre**/

typedef struct coords_s{int x, y;}coords_t;
/**Structure de coordonees x, y**/

int *init_matrice();
void aff_matrice(int *A);
void load_matrice(int *map);
void save_map(int *map);
void aff_map(int *map, SDL_Renderer *renderer, SDL_Texture *texture_tiles);
SDL_Texture *creerTexture(SDL_Window *window, SDL_Renderer *renderer, char sourceIMG[30]);
void aff_tile(SDL_Renderer *renderer, SDL_Texture *texture, int i, int j, int case_actuelle);
coords_t case_to_coords(int case_actuelle);
void fill_map(SDL_Renderer *renderer, SDL_Texture *texture_tiles, int *map, int case_actuelle);
void ecraser_case_actuelle(SDL_Renderer *renderer, SDL_Texture *texture, int *map,  int i, int j, int case_actuelle);
void editeur_map(SDL_Window *window, SDL_Renderer *renderer);
SDL_bool valides(int x, int y);
void creerTexte(SDL_Renderer *renderer, TTF_Font *police, char *str, int x, int y);
void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);
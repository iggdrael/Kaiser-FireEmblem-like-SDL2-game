#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define WIDTH 1366//1920//1366//800
#define HEIGHT 768//1080//768//800
#define W_TEXTURES 640//736
#define H_TEXTURES 920//672
#define LARGEUR_TILE 20 // hauteur et largeur des tiles.
#define HAUTEUR_TILE 20
#define NOMBRE_BLOCS_LARGEUR (W_TEXTURES / LARGEUR_TILE)
#define NOMBRE_BLOCS_HAUTEUR (H_TEXTURES / HAUTEUR_TILE)

#define W_MAP (WIDTH - (WIDTH / 3))
#define H_MAP (HEIGHT - (HEIGHT / 15))
#define M 25
#define N (int)(M / (16.0/9.0)) //Grille de N*M Format 16/9
#define LARGEUR_EDIT (WIDTH / M)
#define LARGEUR_CASE (W_MAP / M)

enum{HUD, CASE};
enum{VIDE, EAU, TERRE, HERBE, DECOR};
typedef struct{int x, y;}coords;

int *init_map();
void aff_map(int *A);
void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);
void editeur_map(SDL_Window *window, SDL_Renderer *renderer, int *map);
void creer_map_rendu(SDL_Window *window, SDL_Renderer *renderer);
SDL_Texture *creerTexture(SDL_Window *window, SDL_Renderer *renderer, char sourceIMG[30]);
void creerTexte(SDL_Renderer *renderer, TTF_Font *police, char str[], int x, int y);
void aff_texture(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, int x_texture, int y_texture, int type_texture, int type_largeur);
void select_tile(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int i, int j);
void save_map(int *map);
void load_map(int *map, SDL_Renderer *renderer, SDL_Texture *texture_tiles);
SDL_bool valides(int x, int y);
#ifndef _SELECTION_EQUIPE_H_
#define _SELECTION_EQUIPE_H_


void perso_copy(perso_t *src, perso_t *dest);

void clean_perso(perso_t *perso);

void aff_perso_console(perso_t *perso);

void aff_persos_console(case_t *map);

int classe_to_text(int n_classe, J_t J);

void change_val_text(case_t *map, int n_text, int i, int j, int val);

SDL_bool case_valide(case_t *map, int i, int j);

void aff_deplacements_deb(SDL_Renderer *renderer, case_t *map);

void placer_persos(case_t *map, perso_t *team, const int NB_PERS, int col_inf, int col_sup);

void move_perso(case_t *map, int i, int j, int old_i, int old_j);

void deplacer_persos(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *police,
 SDL_Window *window_gui, SDL_Renderer *renderer_gui, TTF_Font *police_gui, case_t *map,
  SDL_Texture *pack_texture, SDL_Texture *pack_texture_gui, SDL_Texture *interface);

void bouton_check(SDL_Renderer *renderer, SDL_Rect * validation, TTF_Font *police);

SDL_bool perso_joueur(int n_text);

SDL_bool perso_bot(int n_text);

SDL_bool perso_allie(J_t J, int n_text);

void validation_team(perso_t * team, int g, int m, int a, int h, int v, J_t J);
/**
* \fn validation_team(perso_t * team, int g, int m, int a, int h, int v)
* \param team Contient les personnages utilisés par le joueur
* \param g,m,a,h,v Contient le nombre de personnages de chaque classe
*/

void rectPosWH(SDL_Rect * rectP, SDL_Rect * rectM, int valeur);
/**
* \fn rectPosWH(SDL_Rect * rectP, SDL_Rect * rectM, int valeur)
* \param rectP,rectM Deux carrés "+" et "-"
* \param valeur taille en pixel du côté des carrés
*/

perso_t * create_team(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *police, SDL_Window *window_gui,
 SDL_Renderer *renderer_gui, TTF_Font *police_gui, case_t *map, SDL_Texture *pack_texture,
  SDL_Texture *pack_texture_gui, SDL_Texture *interface, const int NB_PERS);
/**
* \fn create_team(SDL_Window *window, SDL_Renderer *renderer, case_t *map, SDL_Texture *pack_texture, const int NB_PERS)
* \param window,renderer Affiche le menu
* \param team Contient les personnages utilisés par le joueur
* \param NB_PERS Nombre maximum de personnages dans une équipe
*/

void aff_team_console(perso_t *team, int nb_persos);
/**
* \fn void aff_team_console(perso_t *team)
* \param team L equipe que l on souhaite afficher en console
* \param nb_persos Le nombre de persos de l equipe
*/

perso_t * create_team_bot(const int NB_PERS);
/**
* \fn perso_t * create_team_bot(const int NB_PERS);
* \param NB_PERS Nombre de persos de l equipe
*/

#endif
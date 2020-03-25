#ifndef _SELECTION_EQUIPE_H_
#define _SELECTION_EQUIPE_H_

void validation_team(perso_t * team, int g, int m, int a, int h, int v);
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

void create_team(SDL_Window *window, SDL_Renderer *renderer, case_t *map, SDL_Texture *pack_texture, perso_t * team, const int NB_PERS);
/**
* \fn create_team(SDL_Window *window, SDL_Renderer *renderer, case_t *map, SDL_Texture *pack_texture, perso_t * team, const int NB_PERS)
* \param window,renderer Affiche le menu
* \param team Contient les personnages utilisés par le joueur
* \param NB_PERS Nombre maximum de personnages dans une équipe
*/

#endif
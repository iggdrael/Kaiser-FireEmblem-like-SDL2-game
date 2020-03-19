#ifndef _JEU_H_
#define _JEU_H_

#define MIN_PERSO 5
#define MAX_PERSO 10
#define NB_MAPS 1

typedef struct perso_s{
	int CLASSE, PV, ATK, DEF, ESQ, CRIT, POR, DEP;
}perso_t;

typedef struct joueur_s{
	perso_t *team;
	int nb_persos;
}joueur_t;

enum{GUERRIER, MAGE, VOLEUR, ARCHER, PRETRE};
enum{HUMAIN, GOBELIN, ELFE, NAIN};

int randint(int min, int max);
void lancer_jeu(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *pack_texture, case_t *map);

#endif
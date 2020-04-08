#ifndef _JEU_H_
#define _JEU_H_

#define MIN_PERSO 5
#define MAX_PERSO 10
#define NB_MAPS 5
#define NB_CLASSES 5


//Emplacement sur le pack de texture :
#define TEXT_GUERRIER		481
#define	TEXT_MAGE 			476
#define	TEXT_ARCHER			478
#define	TEXT_HEALER			477
#define	TEXT_VOLEUR 		480

#define TEXT_GUERRIER_BOT	487
#define	TEXT_MAGE_BOT 		482
#define	TEXT_ARCHER_BOT		484
#define	TEXT_HEALER_BOT		483
#define	TEXT_VOLEUR_BOT 	486

/**Stats par classe**/

#define G_PV 	100
#define G_ATK 	40
#define G_DEF 	10
#define G_ESQ 	0
#define G_CRIT 	5
#define G_POR	1
#define G_DEP 	5

#define M_PV 	65
#define M_ATK 	60
#define M_DEF 	3
#define M_ESQ 	5
#define M_CRIT 	8
#define M_POR	4
#define M_DEP 	6

#define A_PV 	60
#define A_ATK 	50
#define A_DEF 	4
#define A_ESQ 	5
#define A_CRIT 	6
#define A_POR	5
#define A_DEP 	6

#define H_PV 	80
#define H_ATK 	15
#define H_DEF 	0
#define H_ESQ 	2
#define H_CRIT 	5
#define H_POR	2
#define H_DEP 	6

#define V_PV 	45
#define V_ATK 	65
#define V_DEF 	3
#define V_ESQ 	20
#define V_CRIT  33
#define V_POR	1
#define V_DEP 	6

#define TAILLE_FONT_GUI 30
#define TAILLE_MAIN_FONT 50

/**Opacite des cases couleur**/

#define OP_R 128
#define OP_V 128
#define OP_B 64

typedef enum J_s{J1, BOT}J_t;

typedef struct perso_s{
	int CLASSE, RACE, PV, ATK, DEF, ESQ, CRIT, POR, DEP;
	int x, y, indice;
	J_t J;
}perso_t;

typedef struct joueur_s{
	perso_t *team;
	int nb_persos;
}joueur_t;

typedef enum classe_s{GUERRIER, MAGE, VOLEUR, ARCHER, PRETRE}classe_t;
typedef enum race_s{HUMAIN, ELFE}race_t;

joueur_t *creer_joueurs(int nb_persos);

void aff_perso(SDL_Renderer *renderer, SDL_Texture *pack_texture, TTF_Font *police, perso_t *perso, int text_perso);

void lancer_jeu(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *pack_texture, case_t *map);

SDL_bool chercher_chemin(int *tab,int xd, int yd, int xa, int ya);

void marquer_chemin(int *tab,int x, int y, int *lgmin);

void *map_to_bool(case_t *map, int *tab);

void aff_mat(int *tab);

void mat_copy(int *src, int *dest);

coords_t remarquer_chemin(int *tab, int x1, int y1, int dep);



#endif
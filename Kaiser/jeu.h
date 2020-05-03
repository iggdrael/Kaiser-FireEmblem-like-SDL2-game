/**
 * \file jeu.h
 * \brief fichier regroupant les fonctions permettantde jouer
 * \author GUYON Arthur SANNA Florian RICHEFEU Mattéo
 */

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

#define PERSO_MORT 			488

/**Stats par classe**/

#define G_PV 	100
#define G_ATK 	40
#define G_DEF 	20
#define G_ESQ 	0
#define G_CRIT 	5
#define G_POR	1
#define G_DEP 	5

#define M_PV 	65
#define M_ATK 	60
#define M_DEF 	8
#define M_ESQ 	5
#define M_CRIT 	8
#define M_POR	4
#define M_DEP 	6

#define A_PV 	60
#define A_ATK 	50
#define A_DEF 	9
#define A_ESQ 	5
#define A_CRIT 	6
#define A_POR	5
#define A_DEP 	6

#define H_PV 	80
#define H_ATK 	15
#define H_DEF 	10
#define H_ESQ 	2
#define H_CRIT 	5
#define H_POR	2
#define H_DEP 	6

#define V_PV 	45
#define V_ATK 	80
#define V_DEF 	0
#define V_ESQ 	20
#define V_CRIT  33
#define V_POR	1
#define V_DEP 	6

#define TAILLE_FONT_GUI 30
#define TAILLE_MAIN_FONT 50

/**Opacite des cases couleur**/

#define OP_R 100
#define OP_V 80
#define OP_B 64


/**
 * \enum J_t
 * \brief definir si c'est le joueur ou le bot
 */
typedef enum J_s{J1, BOT}J_t;


/**
 * \struct perso_t
 * \brief definie un perso
 */
typedef struct perso_s{
	int CLASSE, RACE, PV, ATK, DEF, ESQ, CRIT, POR, DEP;  /*!< caractéristique des personnage */
	int x, y, indice; /*!< emplacement du personnage */
	SDL_bool is_dep;
	J_t J; /*!< savoir si c'est un personnage joueur ou bot */
}perso_t;



/**
 * \struct joueur_t
 * \brief definie l'équipe et le nombre de personnags d'un joueur
 */
typedef struct joueur_s{
	perso_t *team; /*!< l'équipe du joueur */
	int nb_persos; /*!< nombre de personnage  */
}joueur_t;


/**
 * \enum classe_t
 * \brief definir la calsse d'un personnage
 */
typedef enum classe_s{GUERRIER, MAGE, VOLEUR, ARCHER, PRETRE}classe_t;

/**
 * \enum race_t
 * \brief definir la race d'un personnage
 */
typedef enum race_s{HUMAIN, ELFE}race_t;


/**
 * \fn creer_joueurs(int nb_persos);
 * \brief Fonction qui initialise les joueurs
 * \param nb_persos Contientle nombre de personnages
 * \return les personnages initialisés
 */
joueur_t *creer_joueurs(int nb_persos);



/**
 * \fn aff_perso(SDL_Renderer *renderer, SDL_Texture *pack_texture, TTF_Font *police, perso_t *perso, int text_perso);
 * \brief Fonction qui affiche le personnage et les statistiques d'un personnage donnée
 * \param renderer affichage
 * \param pack_texture prend le pack de texture
 * \param police prend la police
 * \param perso Le personnagea afficher
 * \param text_perso permet de savoir les différentes statistiques du personnage
 */
void aff_perso(SDL_Renderer *renderer, SDL_Texture *pack_texture, TTF_Font *police, perso_t *perso, int text_perso);

/**
 * \fn lancer_jeu(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *pack_texture, case_t *map);
 * \brief Fonction principal qui permet de jouer
 * \param window, renderer Affichage
 * \param pack_texture charge le pack de texture
 * \param map
 */
void lancer_jeu(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *pack_texture, case_t *map);

/**
 * \fn chercher_chemin(int *tab,int xd, int yd, int xa, int ya);
 * \brief Fonction qui cherche le chemin le plus court entre deux points
 * \param  tab
 * \param xd, yd, xa, ya coordonnées
 * \return vrai si le chemin existe, si non renvoi faux
 */
SDL_bool chercher_chemin(int *tab,int xd, int yd, int xa, int ya);


/**
 * \fn marquer_chemin(int *tab,int x, int y, int *lgmin);
 * \brief Marque le chemin le plus court a partir de *(tab+x*M+y)
 * \param  tab
 * \param x, y coordonnées
 * \param lgmin prend la taille du chemin
 */
void marquer_chemin(int *tab,int x, int y, int *lgmin);


/**
 * \fn map_to_bool(case_t *map, int *tab, int xa, int ya);
 * \brief Fonction qui transforme la map en couloirs/murs
 * \param  map,tab
 * \param xa, ya coordonnées
 */
void *map_to_bool(case_t *map, int *tab, int xa, int ya);



/**
 * \fn aff_mat(int *tab);
 * \brief affiche une matrice
 * \param  tab la matrice
 */
void aff_mat(int *tab);



/**
 * \fn mat_copy(int *src, int *dest);
 * \brief Copie une matrice
 * \param scr la matrice a copié
 * \param dest copie de la matrice
 */
void mat_copy(int *src, int *dest);



/**
 * \fn remarquer_chemin(int *tab, int x1, int y1, int dep);
 * \brief remarque le chemin, regarde autour de chaque position si elle est valide
 * \param tab
 * \param x1, y1 coordonnées
 * \param dep depart
 * \return les coordonnées d'arrivées
 */
coords_t remarquer_chemin(int *tab, int x1, int y1, int dep);



/**
 * \fn retirer_perso(case_t *map, joueur_t *joueur, int indice);
 * \brief retire personnage de la carte
 * \param map
 * \param joueur joueur a retirer
 * \param indice
 */
void retirer_perso(case_t *map, joueur_t *joueur, int indice);


#endif

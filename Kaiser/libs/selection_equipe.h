/**
 * \file selection_equipe.h
 * \brief fichier regroupant les fonctions pour la selection d'équipe avant de jouer
 * \author GUYON Arthur SANNA Florian RICHEFEU Mattéo
 */

#ifndef _SELECTION_EQUIPE_H_
#define _SELECTION_EQUIPE_H_

/**
 * \fn perso_copy(perso_t *src, perso_t *dest)
 * \brief Fonction permettant de copier le perso src dans le perso dest
 * \param src Personnage source
 * \param dest
 */
void perso_copy(perso_t *src, perso_t *dest);

/**
 * \fn clean_perso(perso_t *perso)
 * \brief Fonction permettant de nettoyer un personnage passé en paramètre
 * \param perso Personnage à nettoyer
 */
void clean_perso(perso_t *perso);

/**
 * \fn aff_perso_console(perso_t *perso)
 * \brief Fonction qui affiche un personnage passé en paramètre en console
 * \param perso Personnage à afficher
 */
void aff_perso_console(perso_t *perso);

/**
 * \fn aff_persos_console(case_t *map)
 * \brief Fonction de debuggage permettant de vérifier que les persos sont bien placés sur la map passée en paramètre
 * \param map Contient la map avec les personnages
 */
void aff_persos_console(case_t *map);

/**
 * \fn classe_to_text(int n_classe, J_t J)
 * \brief Fonction qui retourne le numéro de la texture correspondant à la classe du perso en fonction de son équipe
 * \param n_classe
 * \param J
 */
int classe_to_text(int n_classe, J_t J);

/**
 * \fn change_val_text(case_t *map, int n_text, int i, int j, int val)
 * \brief Fonction permettant de changer la valeur d'une texture sur une case passée en paramètre
 * \param map
 * \param n_text
 * \param i,j
 * \param val
 */
void change_val_text(case_t *map, int n_text, int i, int j, int val);

/**
 * \fn case_valide(case_t *map, int i, int j)
 * \brief Fonction qui retourne vrai si la case passée en paramètre est accessible par un personnage
 * \param map
 * \param i,j
 */
SDL_bool case_valide(case_t *map, int i, int j);

/**
 * \fn aff_deplacements_deb(SDL_Renderer *renderer, case_t *map)
 * \brief Fonction affichant où l'on peut déplacer ses personnagess en début de partie
 * \param renderer
 * \param map
 */
void aff_deplacements_deb(SDL_Renderer *renderer, case_t *map);

/**
 * \fn placer_persos(case_t *map, perso_t *team, const int NB_PERS, int col_inf, int col_sup)
 * \brief Fonction permettant au joueur de placer ses personnagess en début de partie
 * \param map
 * \param team
 * \param NB_PERS
 * \param col_inf
 * \param col_sup
 */
void placer_persos(case_t *map, perso_t *team, const int NB_PERS, int col_inf, int col_sup);

/**
 * \fn move_perso(case_t *map, int i, int j, int old_i, int old_j)
 * \brief Fonction permettant de déplacer un personnage
 * \param map Contient la map utilisée
 * \param i,j Contient les coordonnées (en case) du personnage
 * \param old_t,old_j Contient les anciennes coordonnées (en case) du personnage
 */
void move_perso(case_t *map, int i, int j, int old_i, int old_j);

/**
 * \fn deplacer_persos(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *police,
  SDL_Window *window_gui, SDL_Renderer *renderer_gui, TTF_Font *police_gui, case_t *map,
  SDL_Texture *pack_texture, SDL_Texture *pack_texture_gui, SDL_Texture *interface)
 * \brief Fonction permettant au joueur de déplacer ses personnages en début de partie
 * \param window,renderer Affiche le menu
 * \param police Contient la police utilisée pour le menu
 * \param window_gui,renderer_gui Affiche le gui
 * \param police_gui Contient la police utilisée pour le gui
 * \param map Contient la map jouée par le joueur
 * \param pack_texture Contient le pack de texture
 * \param pack_texture_gui Contient la texture utilisée pour le gui
 * \param interface Contient l'interface du gui
 */
void deplacer_persos(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *police,
 SDL_Window *window_gui, SDL_Renderer *renderer_gui, TTF_Font *police_gui, case_t *map,
  SDL_Texture *pack_texture, SDL_Texture *pack_texture_gui, SDL_Texture *interface);

/**
 * \fn bouton_check(SDL_Renderer *renderer, SDL_Rect * validation, TTF_Font *police)
 * \brief Fonction affichant le bouton pour valider
 * \param renderer Renderer utilisé pour l'interface de création d'équipe
 * \param validation Rectangle contenant les paramètres du bouton validation
 * \param police Police utilisée pour le texte du bouton
 */
void bouton_check(SDL_Renderer *renderer, SDL_Rect * validation, TTF_Font *police);

/**
 * \fn perso_allie(int n_text)
 * \brief Retourne vrai si le numéro de la texture passée en paramètre correspond à un personnage allié
 * \param n_text Contient le numéro de la texture passée en paramètre
 */
SDL_bool perso_allie(J_t J, int n_text);

/**
 * \fn perso_bot(int n_text)
 * \brief Retourne vrai si le numéro de la texture passée en paramètre correspond à un personnage ennemi
 * \param n_text Contient le numéro de la texture passée en paramètre
 */
SDL_bool perso_bot(int n_text);

/**
 * \fn perso_joueur(int n_text)
 * \brief Retourne vrai si le numéro de la texture passée en paramètre correspond à un personnage joueur
 * \param n_text Contient le numéro de la texture passée en paramètre
 */
SDL_bool perso_joueur(int n_text);

/**
 * \fn validation_team(perso_t * team, int g, int m, int a, int h, int v)
 * \brief Confirme l'équipe sélectionnée par le joueur
 * \param team Contient les personnages utilisés par le joueur
 * \param g,m,a,h,v Contient le nombre de personnages de chaque classe
 */
void validation_team(perso_t * team, int g, int m, int a, int h, int v, J_t J);

/**
 * \fn rectPosWH(SDL_Rect * rectP, SDL_Rect * rectM, int valeur)
 * \brief Initialise la largeur et longueur des deux rectangle par la valeur passée en paramètre
 * \param rectP,rectM Deux carrés "+" et "-"
 * \param valeur taille en pixel du côté des carrés
 */
void rectPosWH(SDL_Rect * rectP, SDL_Rect * rectM, int valeur);

/**
 * \fn create_team(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *police, SDL_Window *window_gui,
 SDL_Renderer *renderer_gui, TTF_Font *police_gui, case_t *map, SDL_Texture *pack_texture,
  SDL_Texture *pack_texture_gui, SDL_Texture *interface, const int NB_PERS)
 * \brief Affiche une interface pour que le joueur puisse créer l'équipe souhaitée
 * \param window,renderer Affiche le menu
 * \param police Contient la police utilisée pour le menu
 * \param window_gui,renderer_gui Affiche le gui
 * \param police_gui Contient la police utilisée pour le gui
 * \param map Contient la map jouée par le joueur
 * \param pack_texture Contient le pack de texture
 * \param pack_texture_gui Contient la texture utilisée pour le gui
 * \param interface Contient l'interface du gui
 * \param NB_PERS Nombre maximum de personnages dans une équipe
 */
perso_t * create_team(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *police, SDL_Window *window_gui,
 SDL_Renderer *renderer_gui, TTF_Font *police_gui, case_t *map, SDL_Texture *pack_texture,
  SDL_Texture *pack_texture_gui, SDL_Texture *interface, const int NB_PERS);

/**
 * \fn void aff_team_console(perso_t *team)
 * \brief Affiche en console l'équipe passée en paramètre
 * \param team L'équipe que l'on souhaite afficher en console
 * \param nb_persos Le nombre de personnages de l'équipe
 */
void aff_team_console(perso_t *team, int nb_persos);

/**
 * \fn perso_t * create_team_bot(const int NB_PERS);
 * \brief Crée une équipe aléatoire pour le bot
 * \param NB_PERS Nombre de personnages de l'équipe
 */
perso_t * create_team_bot(const int NB_PERS);

#endif

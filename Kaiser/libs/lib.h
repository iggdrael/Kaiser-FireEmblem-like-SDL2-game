/**
 * \file lib.h
 * \brief fichier regroupant les fonctions créer pour la simplification de certaine tache
 * \author GUYON Arthur SANNA Florian RICHEFEU Mattéo
 */


#ifndef _lib_H_
#define _lib_H_

int randint(int min, int max);
/**
 * \fn int randint(int min, int max)
 * \param min borne inferieure
 * \param max borne superieure
**/

int int_len(unsigned x);
/**
 * \fn int int_len(unsigned x);
 * \param x l entier a etudier
**/

void swap(char *c1, char *c2);
/**
* \fn void swap(char *c1, char *c2)
* \param c1 caractere a echanger
* \param c2 le second
**/

void reverse(char str[], int length);
/**
 * \fn void reverse(char str[], int length)
 * \param str la string a retourner
 * \param length la taille de la string
**/

char* ft_itoa(int num, int base);
/**
 * \fn char* ft_itoa(int num, int base);
 * \param num le nombre a convertir
 * \param base la base du nombre
**/

void aff_mat(int *tab);
/**
 * \fn aff_mat(int *tab);
 * \brief affiche une matrice
 * \param  tab la matrice
 */

void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);
/**
* \fn void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t)
* \param massage,x,r,t  Gestion des erreurs et l'affiche
*/

SDL_bool valides(int x, int y);
/**
* \fn SDL_bool valides(int x, int y)
* \param x,y coordonnees dans une matrice
*/


typedef struct coords_s{int x, y;}coords_t;

coords_t case_to_coords(int case_actuelle);
/**
* \fn coords_t case_to_coords(int case_actuelle)
* \param case_actuelle Transforme la case en coordonees de son emplacement dans le pack de texture
*/

/**Primitives de files**/

typedef struct element {int nombre; struct element* suivant;} t_element;

t_element* tete;
t_element* queue;

void initfile(void);
/**
 * \fn void initfile(void);
 */

void ajouter(int v);
/**
 * \fn void ajouter(int v);
 * \param v l entier a ajouter a la file
 */

void retirer(int* v);
/**
 * \fn void retirer(int v);
 * \param v l entier a retirer de la file
 */

int filevide(void);
/**
 * \fn int filevide(void)
 */
#endif

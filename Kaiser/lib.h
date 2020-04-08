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

/**Primitives de files**/

typedef struct element {int nombre; struct element* suivant;} t_element;

t_element* tete;
t_element* queue;

void initfile(void);
void ajouter(int v);
void retirer(int* v);
int filevide(void);


#endif
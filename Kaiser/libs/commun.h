/**
 * \file commun.h
 * \brief fichier regroupant les constante utilisées dans les différents fichiers
 * \author GUYON Arthur SANNA Florian RICHEFEU Mattéo
 */


#ifndef _COMMUN_H_
#define _COMMUN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <time.h>

#include "lib.h"
#include "fonctions.h"
#include "jeu.h"
#include "selection_equipe.h"

//#define DEBUG

int WIDTH; /**Largeur de la fenetre principale**/
int HEIGHT; /**Hauteur de la fenetre principale**/
int W_GUI; /**Largeur de la fenetre interface combat**/
int H_GUI; /**Hauteur de la fenetre interface combat**/
#define W_TEXTURES 408/**Largeur de la fenetre du pack de texture**/
#define H_TEXTURES 720/**Hauteur de la fenetre du pack de texture**/
#define LARGEUR_TILE 32 /**Taille d un tile en pixels**/
#define HAUTEUR_TILE 32
#define NOMBRE_BLOCS_LARGEUR 17 /**Nombre de tiles sur le pack de texture**/
#define NOMBRE_BLOCS_HAUTEUR 30
#define MAX_TEXTURES 3 /**Nombre maximum de textures qu une case de la matrice peut avoir**/

#define NOM_FONT "polices/LLHP.ttf" /**Nom de la police d ecriture**/

/**Code RGB de la police d ecriture**/

#define P_R 25
#define P_G 25
#define P_B 25

/**Code RGB des rectangles d affichage**/

#define R_R 125
#define R_G 125
#define R_B 125


#define M 39 /**Matrice de N * M cases, N est calculee automatiquement pour rester en 16/9**/
#define N (int)(M / (16.0/9.0) + 1)

#define LARGEUR_CASE (WIDTH / M) /**Largeur en pixels d une case en fonction de la taille de la fenetre**/


#endif

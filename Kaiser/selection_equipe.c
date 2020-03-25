#include "commun.h"

/*
	Au lieu de changer les positions de l'archer pour le placer entre le + et le -
	Changer les positions du + et du - en fonction des coordonnées de l'archer

*/


void rectPosWH(SDL_Rect * rectP, SDL_Rect * rectM, int valeur){
	rectP->w = rectP->h = rectM->w = rectM->h = valeur;
}

void validation_team(perso_t * team, int g, int m, int a, int h, int v){ //Guerrier, Mage, Archer, Healer, Voleur
	int i;
	for (i=0; i<g; i++){
		team[i].CLASSE = GUERRIER;
		team[i].PV 	= 100;
		team[i].ATK = 40;
		team[i].DEF = 10;
		team[i].ESQ = 0;
		team[i].CRIT= 5;
		team[i].POR = 1;
		team[i].DEP = 3;
	}

	for (i=0; i<m; i++){
		team[i].CLASSE = MAGE;
		team[i].PV 	= 65;
		team[i].ATK = 60;
		team[i].DEF = 3;
		team[i].ESQ = 5;
		team[i].CRIT= 8;
		team[i].POR = 2;
		team[i].DEP = 4;
	}

	for (i=0; i<a; i++){
		team[i].CLASSE = ARCHER;
		team[i].PV 	= 60;
		team[i].ATK = 50;
		team[i].DEF = 4;
		team[i].ESQ = 5;
		team[i].CRIT= 6;
		team[i].POR = 3;
		team[i].DEP = 4;
	}

	for (i=0; i<h; i++){
		team[i].CLASSE = PRETRE;
		team[i].PV 	= 80;
		team[i].ATK = 15;
		team[i].DEF = 0;
		team[i].ESQ = 2;
		team[i].CRIT= 5;
		team[i].POR = 2;
		team[i].DEP = 4;
	}

	for (i=0; i<v; i++){
		team[i].CLASSE = VOLEUR;
		team[i].PV 	= 45;
		team[i].ATK = 65;
		team[i].DEF = 3;
		team[i].ESQ = 20;
		team[i].CRIT= 33;
		team[i].POR = 1;
		team[i].DEP = 5;
	}
}

void create_team(SDL_Window *window, SDL_Renderer *renderer, case_t *map, SDL_Texture *pack_texture, perso_t * team, const int NB_PERS){

	team = malloc(NB_PERS * sizeof(perso_t));

	SDL_Rect rect_pg, rect_mg, 	//Guerrier
			rect_pm, rect_mm,	//Mage
			rect_pa, rect_ma,	//Archer
			rect_ph, rect_mh,	//Healer
			rect_pv, rect_mv;	//Voleur
	const int taille_police = 72;

	SDL_Rect validation;
	validation.w = taille_police*5;
	validation.h = taille_police;
	validation.x = WIDTH/2 - validation.w/2;
	validation.y = HEIGHT - validation.h;

	SDL_Rect guerrier, mage, archer, healer, voleur;
	// x = case en x
	// y = case en y
	// w = valeur sur le pack de texture
	// h = nombre de personnage de cette classe

	//En case et non en pixel
	guerrier.x = mage.x = archer.x = healer.x = voleur.x = M/2;	// M étant le nombre de cases max en largeur de fenêtre
	guerrier.y = 5;
	mage.y = 8;
	archer.y = 11;
	healer.y = 14;
	voleur.y = 17;

	/*
	Valeurs sur le pack de texture :
		Guerrier :	485
		Mage :		482
		Archer :	484
		Healer :	483
		Voleur :	486
	*/
	guerrier.w = 485;
	mage.w = 482;
	archer.w = 484;
	healer.w = 483;
	voleur.w = 486;

	/* INITIALISATION À 0 DU NOMBRE DE PERSONNAGES DE CHAQUE CLASSE */

	guerrier.h = mage.h = archer.h = healer.h = voleur.h = 0;

	/* ATTRIBUTION DES COORDONNÉES AUX CARRÉS */
	rectPosWH(&rect_pg, &rect_mg, (2*LARGEUR_CASE));
	rectPosWH(&rect_pm, &rect_mm, (2*LARGEUR_CASE));
	rectPosWH(&rect_pa, &rect_ma, (2*LARGEUR_CASE));
	rectPosWH(&rect_ph, &rect_mh, (2*LARGEUR_CASE));
	rectPosWH(&rect_pv, &rect_mv, (2*LARGEUR_CASE));

	rect_pg.x = rect_pm.x = rect_pa.x = rect_ph.x = rect_pv.x = (guerrier.x*LARGEUR_CASE)+(2*LARGEUR_CASE);
	rect_pg.y = rect_mg.y = (guerrier.y*LARGEUR_CASE)-(0.5*LARGEUR_CASE);
	rect_pm.y = rect_mm.y = (mage.y*LARGEUR_CASE)-(0.5*LARGEUR_CASE);
	rect_pa.y = rect_ma.y = (archer.y*LARGEUR_CASE)-(0.5*LARGEUR_CASE);
	rect_ph.y = rect_mh.y = (healer.y*LARGEUR_CASE)-(0.5*LARGEUR_CASE);
	rect_pv.y = rect_mv.y = (voleur.y*LARGEUR_CASE)-(0.5*LARGEUR_CASE);

	rect_mg.x = rect_mm.x = rect_ma.x = rect_mh.x = rect_mv.x = (guerrier.x*LARGEUR_CASE)-(3*LARGEUR_CASE);

	TTF_Font *police = TTF_OpenFont("caviardreams.ttf", taille_police);
	SDL_Texture *pack_textures_for_window = creerTexture(window, renderer, "packtexture.png");

	if (!police)
		SDL_ExitWithError("Erreur du chargement de la police", window, renderer, NULL);

	load_matrice(map);
	aff_map(map, renderer, pack_texture);

	SDL_SetRenderDrawColor(renderer, 46, 180, 100, 255);

/* CREATION DES CARRÉS + ET - DANS LE CHOIX DE LA TEAM */
	SDL_RenderFillRect(renderer, &rect_pg);//Guerrier
	SDL_RenderFillRect(renderer, &rect_mg);
	SDL_RenderFillRect(renderer, &rect_pm);//Mage
	SDL_RenderFillRect(renderer, &rect_mm);
	SDL_RenderFillRect(renderer, &rect_pa);//Archer
	SDL_RenderFillRect(renderer, &rect_ma);
	SDL_RenderFillRect(renderer, &rect_ph);//Healer
	SDL_RenderFillRect(renderer, &rect_mh);
	SDL_RenderFillRect(renderer, &rect_pv);//Voleur
	SDL_RenderFillRect(renderer, &rect_mv);

	SDL_RenderFillRect(renderer, &validation);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderDrawRect(renderer, &rect_pg);//Guerrier
	SDL_RenderDrawRect(renderer, &rect_mg);
	SDL_RenderDrawRect(renderer, &rect_pm);//Mage
	SDL_RenderDrawRect(renderer, &rect_mm);
	SDL_RenderDrawRect(renderer, &rect_pa);//Archer
	SDL_RenderDrawRect(renderer, &rect_ma);
	SDL_RenderDrawRect(renderer, &rect_ph);//Healer
	SDL_RenderDrawRect(renderer, &rect_mh);
	SDL_RenderDrawRect(renderer, &rect_pv);//Voleur
	SDL_RenderDrawRect(renderer, &rect_mv);

	SDL_RenderDrawRect(renderer, &validation);

/* CREATION DES TEXTES "+" ET "-" DANS LES CARRÉS */

	creerTexte(renderer, police, "+", rect_pg.x, rect_pg.y);//Guerrier
	creerTexte(renderer, police, "-", rect_mg.x, rect_mg.y);
	creerTexte(renderer, police, "+", rect_pm.x, rect_pm.y);//Mage
	creerTexte(renderer, police, "-", rect_mm.x, rect_mm.y);
	creerTexte(renderer, police, "+", rect_pa.x, rect_pa.y);//Archer
	creerTexte(renderer, police, "-", rect_ma.x, rect_ma.y);
	creerTexte(renderer, police, "+", rect_ph.x, rect_ph.y);//Healer
	creerTexte(renderer, police, "-", rect_mh.x, rect_mh.y);
	creerTexte(renderer, police, "+", rect_pv.x, rect_pv.y);//Voleur
	creerTexte(renderer, police, "-", rect_mv.x, rect_mv.y);

	creerTexte(renderer, police, "Validation", validation.x, validation.y);

/* AFFICHAGE DES CLASSES ENTRE LES CARRÉS */
	aff_tile(renderer, pack_textures_for_window, guerrier.y, guerrier.x, guerrier.w);
	aff_tile(renderer, pack_textures_for_window, mage.y, mage.x, mage.w);
	aff_tile(renderer, pack_textures_for_window, archer.y, archer.x, archer.w);
	aff_tile(renderer, pack_textures_for_window, healer.y, healer.x, healer.w);
	aff_tile(renderer, pack_textures_for_window, voleur.y, voleur.x, voleur.w);

	SDL_RenderPresent(renderer);

	SDL_Event event;
	SDL_bool selection_launched = SDL_TRUE;
	SDL_bool menu_asked = SDL_FALSE;
	SDL_bool game_start = SDL_FALSE;
	int nb_perso_actuel = 0;

	while (selection_launched && menu_asked == SDL_FALSE && game_start == SDL_FALSE){
        SDL_WaitEvent(&event);

			switch(event.type){
				case SDL_QUIT: selection_launched = SDL_FALSE;break;

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT){
						if (clickSurCase(event, rect_pg)){//Guerrier
							if (nb_perso_actuel < NB_PERS){
								guerrier.h++;
								nb_perso_actuel++;
								printf("+Guerrier : %d\n", nb_perso_actuel);
							}
						}
						else if (clickSurCase(event, rect_mg)){
							if (nb_perso_actuel > 0 && guerrier.h > 0){
								guerrier.h--;
								nb_perso_actuel--;
								printf("-Guerrier : %d\n", nb_perso_actuel);
							}
						}
						else if (clickSurCase(event, rect_pm)){//Mage
							if (nb_perso_actuel < NB_PERS){
								mage.h++;
								nb_perso_actuel++;
								printf("+Mage : %d\n", nb_perso_actuel);
							}
						}
						else if (clickSurCase(event, rect_mm)){
							if (nb_perso_actuel > 0 && mage.h > 0){
								mage.h--;
								nb_perso_actuel--;
								printf("-Mage : %d\n", nb_perso_actuel);
							}
						}
						else if (clickSurCase(event, rect_pa)){//Archer
							if (nb_perso_actuel < NB_PERS){
								archer.h++;
								nb_perso_actuel++;
								printf("+Archer : %d\n", nb_perso_actuel);
							}
						}
						else if (clickSurCase(event, rect_ma)){
							if (nb_perso_actuel > 0 && archer.h > 0){
								archer.h--;
								nb_perso_actuel--;
								printf("-Archer : %d\n", nb_perso_actuel);
							}
						}
						else if (clickSurCase(event, rect_ph)){//Healer
							if (nb_perso_actuel < NB_PERS){
								healer.h++;
								nb_perso_actuel++;
								printf("+Healer : %d\n", nb_perso_actuel);
							}
						}
						else if (clickSurCase(event, rect_mh)){
							if (nb_perso_actuel > 0 && healer.h > 0){
								healer.h--;
								nb_perso_actuel--;
								printf("-Healer : %d\n", nb_perso_actuel);
							}
						}
						else if (clickSurCase(event, rect_pv)){//Voleur
							if (nb_perso_actuel < NB_PERS){
								voleur.h++;
								nb_perso_actuel++;
								printf("+Voleur : %d\n", nb_perso_actuel);
							}
						}
						else if (clickSurCase(event, rect_mv)){ 
							if (nb_perso_actuel > 0 && voleur.h > 0){
								voleur.h--; 
								nb_perso_actuel--;
								printf("-Voleur : %d\n", nb_perso_actuel);
							}
						}
						else if (clickSurCase(event, validation)){
							validation_team(team, guerrier.h, mage.h, archer.h, healer.h, voleur.h);
							game_start = SDL_TRUE;
						}
					}
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE: menu_asked = SDL_TRUE;break;

					}
			}
	}

	free(police);

	if (menu_asked)
		menu(window, renderer, map, pack_texture);

	if (game_start){
		for(int i=0; i<NB_PERS; i++){
			printf("%d\n", team[i].CLASSE);
		}
		lancer_jeu(window, renderer, pack_texture, map);
	}
}

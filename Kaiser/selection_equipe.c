#include "commun.h"

int classe_to_text(int n_classe, J_t J){
/**Fonction qui retourne le numero de la texture correspondant à la classe du perso en fonction de son equipe**/
	if (J == J1){
		switch (n_classe){
			case GUERRIER: return TEXT_GUERRIER; break;
			case MAGE: return TEXT_MAGE; break;
			case VOLEUR: return TEXT_VOLEUR; break;
			case PRETRE: return TEXT_HEALER; break;
			case ARCHER: return TEXT_ARCHER; break;
			default: return -1;
		}
	}
	else if (J == BOT){
		switch (n_classe){
			case GUERRIER: return TEXT_GUERRIER_BOT; break;
			case MAGE: return TEXT_MAGE_BOT; break;
			case VOLEUR: return TEXT_VOLEUR_BOT; break;
			case PRETRE: return TEXT_HEALER_BOT; break;
			case ARCHER: return TEXT_ARCHER_BOT; break;
			default: return -1;
		}
	}
}

void change_val_text(case_t *map, int n_text, int i, int j, int val){
/**Fonction permettant de changer la valeur d'une texture sur une case**/
	(map + M*i + j)->textures[n_text] = val;
}

SDL_bool case_valide(case_t *map, int i, int j){
/**Fonction qui retourne vrai si la case est accessible par un perso**/
	if ((map + M*i + j)->textures[RP] == RIEN || (map + M*i + j)->textures[RP] == PERSO_MORT){
		if ((map + M*i + j)->textures[DECOR] == RIEN)
			return (type_case((map + M*i + j)->textures[FOND]) == LIBRE);
		else if ((type_case((map + M*i + j)->textures[DECOR]) == LIBRE))
			return SDL_TRUE;
		else
			return SDL_FALSE;
	}
	else
		return SDL_FALSE;
}

void aff_persos_console(case_t *map){
/**Fonction de debuggage permettant de verifier que les persos sont bien places**/
	int i, j;

	for (i = 0; i < N; i++){
		for (j = 0; j < M; j++){
			if ((map + M*i + j)->is_perso == SDL_TRUE)
				putchar('1');
			else
				putchar('0');
		}
		putchar('\n');
	}
	putchar('\n');
	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			if ((map + M*i + j)->is_perso == SDL_TRUE)
				aff_perso_console((map + M*i + j)->perso);
}

void aff_perso_console(perso_t *perso){
/**Fonction qui affiche un perso en console**/
	printf("%d %d %d %d %d %d %d %d %d\n", perso->CLASSE, perso->RACE, perso->PV, perso->ATK, perso->DEF, perso->ESQ, perso->CRIT, perso->POR, perso->DEP);
	printf("x : %d y : %d\n", perso->x, perso->y);
	printf("J : %d\n", perso->J);
}

void placer_persos(case_t *map, perso_t *team, const int NB_PERS, int col_inf, int col_sup){
/**Place les persos aléatoirement dans la zone du joueur**/
	int i, j, k;

	for (k = 0; k != NB_PERS;k++){
		do{
			i = randint(0, N - 1);
			j = randint(col_inf, col_sup);
		}while (case_valide(map, i, j) == SDL_FALSE);
		change_val_text(map, RP, i, j, classe_to_text((team+k)->CLASSE, (team+k)->J));

		(team+k)->x = i;
		(team+k)->y = j;

		perso_copy((team + k), (map + M*i + j)->perso);
		(map + M*i + j)->is_perso = SDL_TRUE; 
	}
}

void aff_deplacements_deb(SDL_Renderer *renderer, case_t *map){
/**Fonction affichant ou l on peut deplacer ses persos en debut de partie*/
	int i, j;
	SDL_Rect rect_select;
	rect_select.w = rect_select.h = LARGEUR_CASE;

	for (i = 0; i < N; i++)
		for (j = 0; j < 6; j++){
			rect_select.x = j * LARGEUR_CASE;
			rect_select.y = i * LARGEUR_CASE;
			if (case_valide(map, i, j) == SDL_TRUE)
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, OP_B);
			else
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, OP_R);

			SDL_RenderFillRect(renderer, &rect_select);
		}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

SDL_bool perso_joueur(int n_text){
/**Fonction qui return vrai si le numero de la texture passe en parametre correspond a un perso allie**/
	switch (n_text){
		case TEXT_ARCHER:
		case TEXT_GUERRIER:
		case TEXT_HEALER:
		case TEXT_MAGE:
		case TEXT_VOLEUR: return SDL_TRUE; break;
		default: return SDL_FALSE;
	}
}

SDL_bool perso_bot(int n_text){
/**Fonction qui return vrai si le numero de la texture passe en parametre correspond a un perso ennemi**/
	switch (n_text){
		case TEXT_ARCHER_BOT:
		case TEXT_GUERRIER_BOT:
		case TEXT_HEALER_BOT:
		case TEXT_MAGE_BOT:
		case TEXT_VOLEUR_BOT: return SDL_TRUE; break;
		default: return SDL_FALSE;
	}
}

SDL_bool perso_allie(J_t J, int n_text){
	if (J == BOT)
		return perso_bot(n_text);
	else if (J == J1)
		return perso_joueur(n_text);
}

void bouton_check(SDL_Renderer *renderer, SDL_Rect * validation, TTF_Font *police){
/**Fonction affichant le bouton pour valider**/
	SDL_SetRenderDrawColor(renderer, R_R,  R_G, R_B, 255);
	SDL_RenderFillRect(renderer, validation);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, validation);
	creerTexte(renderer, police, "Valider", validation->x, validation->y);
}

void clean_perso(perso_t *perso){
/**Fonction permettant de clean un perso**/
	perso->CLASSE 	= RIEN;
	perso->RACE 	= RIEN;
	perso->PV 		= RIEN;
	perso->ATK 		= RIEN;
	perso->DEF 		= RIEN;
	perso->ESQ 		= RIEN;
	perso->CRIT 	= RIEN;
	perso->POR 		= RIEN;
	perso->DEP 		= RIEN;
	perso->J 		= RIEN;
	perso->x 		= RIEN;
	perso->y        = RIEN;
	perso->indice   = RIEN;
	perso->is_dep	= RIEN;
}

void perso_copy(perso_t *src, perso_t *dest){
/**Fonction permettant de copier le perso src dans le perso dest**/
	dest->CLASSE =	src->CLASSE;
	dest->RACE = 	src->RACE;
	dest->PV = 		src->PV;
	dest->ATK = 	src->ATK;
	dest->DEF = 	src->DEF;
	dest->ESQ = 	src->ESQ;
	dest->CRIT = 	src->CRIT;
	dest->POR = 	src->POR;
	dest->DEP = 	src->DEP;
	dest->J =		src->J;
	dest->x =		src->x;
	dest->y =		src->y;
	dest->indice =	src->indice;
	dest->is_dep = 	src->is_dep;
}

void move_perso(case_t *map, int i, int j, int old_i, int old_j){
/**Fonction permettant de deplacer un perso**/
	change_val_text(map, RP, i, j, (map + old_i*M + old_j)->textures[RP]);
	perso_copy((map + old_i*M + old_j)->perso, (map + i*M + j)->perso);
	(map + i*M + j)->is_perso = SDL_TRUE;

	(map + i*M + j)->perso->x = i;
	(map + i*M + j)->perso->y = j;

	change_val_text(map, RP, old_i, old_j, RIEN);
	clean_perso((map + old_i*M + old_j)->perso);
	(map + old_i*M + old_j)->is_perso = SDL_FALSE;
}

void deplacer_persos(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *police,
 SDL_Window *window_gui, SDL_Renderer *renderer_gui, TTF_Font *police_gui, case_t *map,
  SDL_Texture *pack_texture, SDL_Texture *pack_texture_gui, SDL_Texture *interface){
/**Fonction permettant au joueur de deplacer ses persos en debut de partie**/
	int i, j, old_i, old_j;

	SDL_Rect rect_select;
	rect_select.w = rect_select.h = LARGEUR_CASE;

	SDL_Rect validation;
	validation.w = TAILLE_FONT_GUI*5;
	validation.h = TAILLE_FONT_GUI;
	validation.x = (WIDTH / 3.5)/2 - validation.w/2;
	validation.y = HEIGHT - validation.h;

	Uint32 id_main_window = SDL_GetWindowID(window);
	Uint32 id_window_gui = SDL_GetWindowID(window_gui);

	bouton_check(renderer_gui, &validation, police_gui);
	SDL_RenderPresent(renderer_gui);

	SDL_Event event;
	SDL_bool dep_launched = SDL_TRUE, menu_asked = SDL_FALSE, click = SDL_FALSE;

	while(dep_launched){
		SDL_WaitEvent(&event);

		if (event.window.windowID == id_main_window){
			switch(event.type){
				case SDL_QUIT: 
					dep_launched = SDL_FALSE; 
					menu_asked = SDL_TRUE;
					break;

				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT){
						i = event.button.y / LARGEUR_CASE;
						j = event.button.x / LARGEUR_CASE;

						SDL_RenderClear(renderer);

						if (click == SDL_TRUE){
							if (case_valide(map, i, j) && j < 6)
								move_perso(map, i, j, old_i, old_j);
							aff_map(map, renderer, pack_texture);
							click = SDL_FALSE;
						}
						else if (perso_joueur( (map + M*i + j)->textures[RP])){
							SDL_RenderClear(renderer_gui);
							aff_tile(renderer_gui, interface, 0, 0, -1, 1);

							#ifdef DEBUG
								aff_perso_console((map + M*i +j)->perso);
							#endif

							aff_perso(renderer_gui, pack_texture_gui, police_gui, (map + M*i +j)->perso, VIDE);
							bouton_check(renderer_gui, &validation, police_gui);
							SDL_RenderPresent(renderer_gui);

							rect_select.x = j * LARGEUR_CASE;
							rect_select.y = i * LARGEUR_CASE;

							aff_map(map, renderer, pack_texture);
							SDL_SetRenderDrawColor(renderer, 0, 255, 0, OP_V);
							SDL_RenderFillRect(renderer, &rect_select);

							aff_deplacements_deb(renderer, map);

							click = SDL_TRUE;
							old_i = i;
							old_j = j;
						}
						else if (perso_bot( (map + M*i + j)->textures[RP])){
							SDL_RenderClear(renderer_gui);
							aff_tile(renderer_gui, interface, 0, 0, -1, 1);
							aff_perso(renderer_gui, pack_texture_gui, police_gui, (map + M*i +j)->perso, VIDE);
							bouton_check(renderer_gui, &validation, police_gui);
							SDL_RenderPresent(renderer_gui);

							aff_map(map, renderer, pack_texture);
						}
						else
							aff_map(map, renderer, pack_texture);
						SDL_RenderPresent(renderer);
					}
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE: 
							dep_launched = SDL_FALSE;
							menu_asked = SDL_TRUE;
							break;
					}
					break;
			}
		}
		else if (event.window.windowID == id_window_gui){
			switch(event.type){
				case SDL_QUIT: 
					dep_launched = SDL_FALSE; 
					menu_asked = SDL_TRUE;
					break;

				case SDL_MOUSEBUTTONDOWN:
					if (clickSurCase(event, validation))
						dep_launched = SDL_FALSE;
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE: 
							dep_launched = SDL_FALSE;
							menu_asked = SDL_TRUE;
							break;
					}
					break;
			}
		}
	}

	if (menu_asked){
		free(police_gui);
		free(police);
		SDL_DestroyTexture(pack_texture_gui);
		SDL_DestroyTexture(interface);
		SDL_DestroyRenderer(renderer_gui);
		SDL_DestroyWindow(window_gui);
		menu(window, renderer, map, pack_texture);
	}
}

perso_t * create_team_bot(const int NB_PERS){
/**Fonction qui cree aleatoirement l equipe du bot**/
	perso_t * team = malloc(NB_PERS * sizeof(perso_t));
	
	int i, r, g=0, m=0, a=0, p=0, v=0;
	for (i = 0; i < NB_PERS; i++){
		r = randint(0, NB_CLASSES - 1);
		switch (r){
			case GUERRIER: g++; break;
			case MAGE: m++; break;
			case ARCHER: a++; break;
			case PRETRE: p++; break;
			case VOLEUR: v++; break;
		}
	}
	validation_team(team, g, m, a, p, v, BOT);
	
	return team;
}


void aff_team_console(perso_t *team, int nb_persos){
/**Fonction qui affiche la constitution de l equipe en console**/
	for (int i = 0; i < nb_persos; i++){
		printf("classe: %d pv: %d atk: %d def: %d esq: %d crit: %d por: %d dep: %d J: %d x: %d y: %d indice : %d\n", (team+i)->CLASSE, (team+i)->PV, (team+i)->ATK, (team+i)->DEF, (team+i)->ESQ, (team+i)->CRIT, (team+i)->POR, (team+i)->DEP, (team+i)->J, (team+i)->x, (team+i)->y, (team+i)->indice);
	}
}

void rectPosWH(SDL_Rect * rectP, SDL_Rect * rectM, int valeur){
/**Initialise un SDL_rect avec la valeur passee en parametres**/
	rectP->w = rectP->h = rectM->w = rectM->h = valeur;
}

void validation_team(perso_t * team, int g, int m, int a, int h, int v, J_t J){ //Guerrier, Mage, Archer, Healer, Voleur
/**Fonction qui initialise l equipe avec le nombre de persos par classe passees en parametres**/
	int i, j = 0;
	for (i=0; i<g; i++, j++){
		(team+j)->CLASSE = GUERRIER;
		(team+j)->RACE = HUMAIN;
		(team+j)->PV 	= G_PV;
		(team+j)->ATK 	= G_ATK;
		(team+j)->DEF 	= G_DEF;
		(team+j)->ESQ 	= G_ESQ;
		(team+j)->CRIT	= G_CRIT;
		(team+j)->POR 	= G_POR;
		(team+j)->DEP 	= G_DEP;
	}

	for (i=0; i<m; i++, j++){
		(team+j)->CLASSE = MAGE;
		(team+j)->RACE = HUMAIN;
		(team+j)->PV 	= M_PV;
		(team+j)->ATK 	= M_ATK;
		(team+j)->DEF 	= M_DEF;
		(team+j)->ESQ 	= M_ESQ;
		(team+j)->CRIT	= M_CRIT;
		(team+j)->POR 	= M_POR;
		(team+j)->DEP 	= M_DEP;
	}

	for (i=0; i<a; i++, j++){
		(team+j)->CLASSE = ARCHER;
		(team+j)->RACE = ELFE;
		(team+j)->PV 	= A_PV;
		(team+j)->ATK 	= A_ATK;
		(team+j)->DEF 	= A_DEF;
		(team+j)->ESQ 	= A_ESQ;
		(team+j)->CRIT	= A_CRIT;
		(team+j)->POR 	= A_POR;
		(team+j)->DEP 	= A_DEP;
	}

	for (i=0; i<h; i++, j++){
		(team+j)->CLASSE = PRETRE;
		(team+j)->RACE = ELFE;
		(team+j)->PV 	= H_PV;
		(team+j)->ATK 	= H_ATK;
		(team+j)->DEF 	= H_DEF;
		(team+j)->ESQ 	= H_ESQ;
		(team+j)->CRIT	= H_CRIT;
		(team+j)->POR 	= H_POR;
		(team+j)->DEP 	= H_DEP;
	}

	for (i=0; i<v; i++, j++){
		(team+j)->CLASSE = VOLEUR;
		(team+j)->RACE = HUMAIN;
		(team+j)->PV 	= V_PV;
		(team+j)->ATK 	= V_ATK;
		(team+j)->DEF 	= V_DEF;
		(team+j)->ESQ 	= V_ESQ;
		(team+j)->CRIT	= V_CRIT;
		(team+j)->POR 	= V_POR;
		(team+j)->DEP 	= V_DEP;
	}

	for (i = 0; i < j; i++){
		(team+i)->indice = i;
		if (J == J1)
			(team+i)->J = J1;
		else if (J == BOT)
			(team+i)->J = BOT;
	}
}

perso_t * create_team(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *police, SDL_Window *window_gui,
 SDL_Renderer *renderer_gui, TTF_Font *police_gui, case_t *map, SDL_Texture *pack_texture,
  SDL_Texture *pack_texture_gui, SDL_Texture *interface, const int NB_PERS){
/**Fonction permettant a l utilisateur de creer son equipe**/

	perso_t * team = malloc(NB_PERS * sizeof(perso_t));

	SDL_Rect rect_pg, rect_mg, 	//Guerrier
			rect_pm, rect_mm,	//Mage
			rect_pa, rect_ma,	//Archer
			rect_ph, rect_mh,	//Healer
			rect_pv, rect_mv;	//Voleur

	SDL_Rect validation;
	validation.w = TAILLE_FONT_GUI*5;
	validation.h = TAILLE_FONT_GUI;
	validation.x = (WIDTH / 3.5)/2 - validation.w/2;
	validation.y = HEIGHT - validation.h;

	SDL_Rect guerrier, mage, archer, healer, voleur;
	// x = case en x
	// y = case en y
	// w = valeur sur le pack de texture
	// h = nombre de personnages de cette classe

	//En case et non en pixel
	guerrier.x = mage.x = archer.x = healer.x = voleur.x = M/2;	// M étant le nombre de cases max en largeur de fenêtre
	guerrier.y = 5;
	mage.y = 8;
	archer.y = 11;
	healer.y = 14;
	voleur.y = 17;

	guerrier.w = TEXT_GUERRIER;
	mage.w = TEXT_MAGE;
	archer.w = TEXT_ARCHER;
	healer.w = TEXT_HEALER;
	voleur.w = TEXT_VOLEUR;

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

	SDL_Texture *pack_textures_for_window = creerTexture(window, renderer, "packtexture.png");

	load_matrice(map, 0);

	SDL_RenderClear(renderer); aff_map(map, renderer, pack_texture); SDL_SetRenderDrawColor(renderer, R_R,  R_G, R_B, 255);SDL_RenderFillRect(renderer, &rect_pg);SDL_RenderFillRect(renderer, &rect_mg); SDL_RenderFillRect(renderer, &rect_pm);SDL_RenderFillRect(renderer, &rect_mm); SDL_RenderFillRect(renderer, &rect_pa);SDL_RenderFillRect(renderer, &rect_ma); SDL_RenderFillRect(renderer, &rect_ph);SDL_RenderFillRect(renderer, &rect_mh); SDL_RenderFillRect(renderer, &rect_pv);SDL_RenderFillRect(renderer, &rect_mv); SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); SDL_RenderDrawRect(renderer, &rect_pg);SDL_RenderDrawRect(renderer, &rect_mg); SDL_RenderDrawRect(renderer, &rect_pm);SDL_RenderDrawRect(renderer, &rect_mm); SDL_RenderDrawRect(renderer, &rect_pa); SDL_RenderDrawRect(renderer, &rect_ma); SDL_RenderDrawRect(renderer, &rect_ph);SDL_RenderDrawRect(renderer, &rect_mh); SDL_RenderDrawRect(renderer, &rect_pv);SDL_RenderDrawRect(renderer, &rect_mv);creerTexte(renderer, police, "+", rect_pg.x, rect_pg.y);creerTexte(renderer, police, "-", rect_mg.x, rect_mg.y);creerTexte(renderer, police, "0", rect_pg.x + 100, rect_pg.y); creerTexte(renderer, police, "+", rect_pm.x, rect_pm.y);creerTexte(renderer, police, "-", rect_mm.x, rect_mm.y); creerTexte(renderer, police, "0", rect_pm.x + 100, rect_pm.y); creerTexte(renderer, police, "+", rect_pa.x, rect_pa.y);creerTexte(renderer, police, "-", rect_ma.x, rect_ma.y); creerTexte(renderer, police, "0", rect_pa.x + 100, rect_pa.y); creerTexte(renderer, police, "+", rect_ph.x, rect_ph.y);creerTexte(renderer, police, "-", rect_mh.x, rect_mh.y); creerTexte(renderer, police, "0", rect_ph.x + 100, rect_ph.y); creerTexte(renderer, police, "+", rect_pv.x, rect_pv.y);creerTexte(renderer, police, "-", rect_mv.x, rect_mv.y); creerTexte(renderer, police, "0", rect_pv.x + 100, rect_pv.y);aff_tile(renderer, pack_textures_for_window, guerrier.y-1, guerrier.x-1, guerrier.w, 3); aff_tile(renderer, pack_textures_for_window, mage.y-1, mage.x-1, mage.w, 3); aff_tile(renderer, pack_textures_for_window, archer.y-1, archer.x-1, archer.w, 3); aff_tile(renderer, pack_textures_for_window, healer.y-1, healer.x-1, healer.w, 3); aff_tile(renderer, pack_textures_for_window, voleur.y-1, voleur.x-1, voleur.w, 3); SDL_RenderPresent(renderer);
	
	bouton_check(renderer_gui, &validation, police_gui);
	SDL_RenderPresent(renderer_gui);


	SDL_Event event;
	SDL_bool selection_launched = SDL_TRUE;
	SDL_bool menu_asked = SDL_FALSE;
	SDL_bool game_start = SDL_FALSE;
	int nb_perso_actuel = 0;

	while (selection_launched && menu_asked == SDL_FALSE && game_start == SDL_FALSE){
        SDL_WaitEvent(&event);

		switch(event.type){
			case SDL_QUIT: 
				selection_launched = SDL_FALSE; 
				menu_asked = SDL_TRUE;
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT){
					if (clickSurCase(event, rect_pg)){//Guerrier
						if (nb_perso_actuel < NB_PERS){
							guerrier.h++;
							nb_perso_actuel++;

							#ifdef DEBUG
								printf("+Guerrier : %d, Total : %d\n", guerrier.h, nb_perso_actuel);
							#endif
						}
						SDL_RenderClear(renderer_gui);
						aff_tile(renderer_gui, interface, 0, 0, -1, 1);
						aff_perso(renderer_gui, pack_texture_gui, police_gui, NULL, TEXT_GUERRIER);
						bouton_check(renderer_gui, &validation, police_gui);
						SDL_RenderPresent(renderer_gui);
					}
					else if (clickSurCase(event, rect_mg)){
						if (nb_perso_actuel > 0 && guerrier.h > 0){
							guerrier.h--;
							nb_perso_actuel--;

							#ifdef DEBUG
								printf("-Guerrier : %d, Total : %d\n", guerrier.h, nb_perso_actuel);
							#endif
						}
						SDL_RenderClear(renderer_gui);
						aff_tile(renderer_gui, interface, 0, 0, -1, 1);
						aff_perso(renderer_gui, pack_texture_gui, police_gui, NULL, TEXT_GUERRIER);
						bouton_check(renderer_gui, &validation, police_gui);
						SDL_RenderPresent(renderer_gui);
					}
					else if (clickSurCase(event, rect_pm)){//Mage
						if (nb_perso_actuel < NB_PERS){
							mage.h++;
							nb_perso_actuel++;

							#ifdef DEBUG
								printf("+Mage : %d, Total : %d\n", mage.h, nb_perso_actuel);
							#endif
						}
						SDL_RenderClear(renderer_gui);
						aff_tile(renderer_gui, interface, 0, 0, -1, 1);
						aff_perso(renderer_gui, pack_texture_gui, police_gui, NULL, TEXT_MAGE);
						bouton_check(renderer_gui, &validation, police_gui);
						SDL_RenderPresent(renderer_gui);
					}
					else if (clickSurCase(event, rect_mm)){
						if (nb_perso_actuel > 0 && mage.h > 0){
							mage.h--;
							nb_perso_actuel--;

							#ifdef DEBUG
								printf("-Mage : %d, Total : %d\n", mage.h, nb_perso_actuel);
							#endif
						}
						SDL_RenderClear(renderer_gui);
						aff_tile(renderer_gui, interface, 0, 0, -1, 1);
						aff_perso(renderer_gui, pack_texture_gui, police_gui, NULL, TEXT_MAGE);
						bouton_check(renderer_gui, &validation, police_gui);
						SDL_RenderPresent(renderer_gui);
					}
					else if (clickSurCase(event, rect_pa)){//Archer
						if (nb_perso_actuel < NB_PERS){
							archer.h++;
							nb_perso_actuel++;

							#ifdef DEBUG
								printf("+Archer : %d, Total : %d\n", archer.h, nb_perso_actuel);
							#endif
						}
						SDL_RenderClear(renderer_gui);
						aff_tile(renderer_gui, interface, 0, 0, -1, 1);
						aff_perso(renderer_gui, pack_texture_gui, police_gui, NULL, TEXT_ARCHER);
						bouton_check(renderer_gui, &validation, police_gui);
						SDL_RenderPresent(renderer_gui);
					}
					else if (clickSurCase(event, rect_ma)){
						if (nb_perso_actuel > 0 && archer.h > 0){
							archer.h--;
							nb_perso_actuel--;

							#ifdef DEBUG
								printf("-Archer : %d, Total : %d\n", archer.h, nb_perso_actuel);
							#endif
						}
						SDL_RenderClear(renderer_gui);
						aff_tile(renderer_gui, interface, 0, 0, -1, 1);
						aff_perso(renderer_gui, pack_texture_gui, police_gui, NULL, TEXT_ARCHER);
						bouton_check(renderer_gui, &validation, police_gui);
						SDL_RenderPresent(renderer_gui);
					}
					else if (clickSurCase(event, rect_ph)){//Healer
						if (nb_perso_actuel < NB_PERS){
							healer.h++;
							nb_perso_actuel++;

							#ifdef DEBUG
								printf("+Healer : %d, Total : %d\n", healer.h, nb_perso_actuel);
							#endif
						}
						SDL_RenderClear(renderer_gui);
						aff_tile(renderer_gui, interface, 0, 0, -1, 1);
						aff_perso(renderer_gui, pack_texture_gui, police_gui, NULL, TEXT_HEALER);
						bouton_check(renderer_gui, &validation, police_gui);
						SDL_RenderPresent(renderer_gui);
					}
					else if (clickSurCase(event, rect_mh)){
						if (nb_perso_actuel > 0 && healer.h > 0){
							healer.h--;
							nb_perso_actuel--;

							#ifdef DEBUG
								printf("-Healer : %d, Total : %d\n", healer.h, nb_perso_actuel);
							#endif
						}
						SDL_RenderClear(renderer_gui);
						aff_tile(renderer_gui, interface, 0, 0, -1, 1);
						aff_perso(renderer_gui, pack_texture_gui, police_gui, NULL, TEXT_HEALER);
						bouton_check(renderer_gui, &validation, police_gui);
						SDL_RenderPresent(renderer_gui);
					}
					else if (clickSurCase(event, rect_pv)){//Voleur
						if (nb_perso_actuel < NB_PERS){
							voleur.h++;
							nb_perso_actuel++;

							#ifdef DEBUG
								printf("+Voleur : %d, Total : %d\n", voleur.h, nb_perso_actuel);
							#endif
						}
						SDL_RenderClear(renderer_gui);
						aff_tile(renderer_gui, interface, 0, 0, -1, 1);
						aff_perso(renderer_gui, pack_texture_gui, police_gui, NULL, TEXT_VOLEUR);
						bouton_check(renderer_gui, &validation, police_gui);
						SDL_RenderPresent(renderer_gui);
					}
					else if (clickSurCase(event, rect_mv)){ 
						if (nb_perso_actuel > 0 && voleur.h > 0){
							voleur.h--; 
							nb_perso_actuel--;

							#ifdef DEBUG
								printf("-Voleur : %d, Total : %d\n", voleur.h, nb_perso_actuel);
							#endif
						}
						SDL_RenderClear(renderer_gui);
						aff_tile(renderer_gui, interface, 0, 0, -1, 1);
						aff_perso(renderer_gui, pack_texture_gui, police_gui, NULL, TEXT_VOLEUR);
						bouton_check(renderer_gui, &validation, police_gui);
						SDL_RenderPresent(renderer_gui);
					}
					else if (clickSurCase(event, validation)){
						if ((guerrier.h + mage.h + archer.h + healer.h + voleur.h) == NB_PERS){
							validation_team(team, guerrier.h, mage.h, archer.h, healer.h, voleur.h, J1);
							game_start = SDL_TRUE;
						}
					}
					SDL_RenderClear(renderer);
					aff_map(map, renderer, pack_texture);
					SDL_SetRenderDrawColor(renderer, R_R,  R_G, R_B, 255);

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

				/* CREATION DES TEXTES "+" ET "-" DANS LES CARRÉS */

					creerTexte(renderer, police, "+", rect_pg.x, rect_pg.y);//Guerrier
					creerTexte(renderer, police, "-", rect_mg.x, rect_mg.y);
					creerTexte(renderer, police, ft_itoa(guerrier.h, 10), rect_pg.x + 100, rect_pg.y);
					creerTexte(renderer, police, "+", rect_pm.x, rect_pm.y);//Mage
					creerTexte(renderer, police, "-", rect_mm.x, rect_mm.y);
					creerTexte(renderer, police, ft_itoa(mage.h, 10), rect_pm.x + 100, rect_pm.y);
					creerTexte(renderer, police, "+", rect_pa.x, rect_pa.y);//Archer
					creerTexte(renderer, police, "-", rect_ma.x, rect_ma.y);
					creerTexte(renderer, police, ft_itoa(archer.h, 10), rect_pa.x + 100, rect_pa.y);
					creerTexte(renderer, police, "+", rect_ph.x, rect_ph.y);//Healer
					creerTexte(renderer, police, "-", rect_mh.x, rect_mh.y);
					creerTexte(renderer, police, ft_itoa(healer.h, 10), rect_ph.x + 100, rect_ph.y);
					creerTexte(renderer, police, "+", rect_pv.x, rect_pv.y);//Voleur
					creerTexte(renderer, police, "-", rect_mv.x, rect_mv.y);
					creerTexte(renderer, police, ft_itoa(voleur.h, 10), rect_pv.x + 100, rect_pv.y);

				/* AFFICHAGE DES CLASSES ENTRE LES CARRÉS */
					aff_tile(renderer, pack_textures_for_window, guerrier.y - 1, guerrier.x - 1, guerrier.w, 3);
					aff_tile(renderer, pack_textures_for_window, mage.y - 1, mage.x - 1, mage.w, 3);
					aff_tile(renderer, pack_textures_for_window, archer.y - 1, archer.x - 1, archer.w, 3);
					aff_tile(renderer, pack_textures_for_window, healer.y - 1, healer.x - 1, healer.w, 3);
					aff_tile(renderer, pack_textures_for_window, voleur.y - 1, voleur.x - 1, voleur.w, 3);

					SDL_RenderPresent(renderer);
				}
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE: menu_asked = SDL_TRUE;break;
				}
				break;
		}
	}

	if (menu_asked){
		free(police_gui);
		free(police);
		SDL_DestroyTexture(pack_texture_gui);
		SDL_DestroyTexture(interface);
		SDL_DestroyRenderer(renderer_gui);
		SDL_DestroyWindow(window_gui);
		menu(window, renderer, map, pack_texture);
	}
	else
		return team;
}

#include "libs/commun.h"

void aff_perso(SDL_Renderer *renderer, SDL_Texture *pack_texture, TTF_Font *police, perso_t *perso, int text_perso){
	int W_GUI = (WIDTH / 3.5);
	char classe[9], race[9];

	creerTexte(renderer, police, "PV", W_GUI / 25, HEIGHT / 4.8);
	creerTexte(renderer, police, "Attaque", W_GUI / 25, HEIGHT / 3.8);
	creerTexte(renderer, police, "Defense", W_GUI / 25, HEIGHT / 3.1);
	creerTexte(renderer, police, "Esquive", W_GUI / 25, HEIGHT / 2.62);
	creerTexte(renderer, police, "Critique", W_GUI / 25, HEIGHT / 2.29);
	creerTexte(renderer, police, "Portee", W_GUI / 1.8, HEIGHT / 4.8);
	creerTexte(renderer, police, "Marche", W_GUI / 1.8, HEIGHT / 3.8);

	if (perso == NULL){
		int pv, atk, def, esq, crit, por, dep;

		switch (text_perso){
			case TEXT_GUERRIER:
				strcpy(classe, "Guerrier");
				strcpy(race, "Humain");
				pv = 	G_PV;
				atk = 	G_ATK;
				def = 	G_DEF;
				esq =	G_ESQ;
				crit = 	G_CRIT;
				por =	G_POR;
				dep = 	G_DEP;
				break;
			case TEXT_MAGE:
				strcpy(classe, "Mage");
				strcpy(race, "Humain");
				pv = 	M_PV;
				atk = 	M_ATK;
				def = 	M_DEF;
				esq =	M_ESQ;
				crit = 	M_CRIT;
				por =	M_POR;
				dep = 	M_DEP;
				break;
			case TEXT_ARCHER:
				strcpy(classe, "Archer");
				strcpy(race, "Elfe");
				pv = 	A_PV;
				atk = 	A_ATK;
				def = 	A_DEF;
				esq =	A_ESQ;
				crit = 	A_CRIT;
				por =	A_POR;
				dep = 	A_DEP;
				break;
			case TEXT_HEALER:
				strcpy(classe, "Pretre");
				strcpy(race, "Elfe");
				pv = 	H_PV;
				atk = 	H_ATK;
				def = 	H_DEF;
				esq =	H_ESQ;
				crit = 	H_CRIT;
				por =	H_POR;
				dep = 	H_DEP;
				break;
			case TEXT_VOLEUR:
				strcpy(classe, "Voleur");
				strcpy(race, "Humain");
				pv = 	V_PV;
				atk = 	V_ATK;
				def = 	V_DEF;
				esq =	V_ESQ;
				crit = 	V_CRIT;
				por =	V_POR;
				dep = 	V_DEP;
				break;
		}
		creerTexte(renderer, police, ft_itoa(pv, 10), W_GUI / 2.6, HEIGHT / 4.8);
		creerTexte(renderer, police, ft_itoa(atk, 10), W_GUI / 2.6, HEIGHT / 3.8);
		creerTexte(renderer, police, ft_itoa(def, 10), W_GUI / 2.6, HEIGHT / 3.1);
		creerTexte(renderer, police, ft_itoa(esq, 10), W_GUI / 2.6, HEIGHT / 2.6);
		creerTexte(renderer, police, ft_itoa(crit, 10), W_GUI / 2.6, HEIGHT / 2.3);
		creerTexte(renderer, police, ft_itoa(por, 10), W_GUI / 1.08, HEIGHT / 4.8);
		creerTexte(renderer, police, ft_itoa(dep, 10), W_GUI / 1.08, HEIGHT / 3.8);
	}
	else{
		switch(perso->CLASSE){
			case GUERRIER: strcpy(classe, "Guerrier"); break;
			case MAGE: strcpy(classe, "Mage"); break;
			case PRETRE: strcpy(classe, "Pretre"); break;
			case ARCHER: strcpy(classe, "Archer"); break;
			case VOLEUR: strcpy(classe, "Voleur"); break;
		}
		switch(perso->RACE){
			case HUMAIN: strcpy(race, "Humain"); break;
			case ELFE: strcpy(race, "Elfe"); break;
		}
		switch(perso->J){
			case J1:
				switch(perso->CLASSE){
					case GUERRIER: text_perso = TEXT_GUERRIER; break;
					case MAGE: text_perso = TEXT_MAGE; break;
					case PRETRE: text_perso = TEXT_HEALER; break;
					case ARCHER: text_perso = TEXT_ARCHER; break;
					case VOLEUR: text_perso = TEXT_VOLEUR; break;
				}
				break;
			case BOT:
				switch(perso->CLASSE){
					case GUERRIER: text_perso = TEXT_GUERRIER_BOT; break;
					case MAGE: text_perso = TEXT_MAGE_BOT; break;
					case PRETRE: text_perso = TEXT_HEALER_BOT; break;
					case ARCHER: text_perso = TEXT_ARCHER_BOT; break;
					case VOLEUR: text_perso = TEXT_VOLEUR_BOT; break;
				}
				break;
		}
		creerTexte(renderer, police, ft_itoa(perso->PV, 10), W_GUI / 2.6, HEIGHT / 4.8);
		creerTexte(renderer, police, ft_itoa(perso->ATK, 10), W_GUI / 2.6, HEIGHT / 3.8);
		creerTexte(renderer, police, ft_itoa(perso->DEF, 10), W_GUI / 2.6, HEIGHT / 3.1);
		creerTexte(renderer, police, ft_itoa(perso->ESQ, 10), W_GUI / 2.6, HEIGHT / 2.6);
		creerTexte(renderer, police, ft_itoa(perso->CRIT, 10), W_GUI / 2.6, HEIGHT / 2.3);
		creerTexte(renderer, police, ft_itoa(perso->POR, 10), W_GUI / 1.08, HEIGHT / 4.8);
		creerTexte(renderer, police, ft_itoa(perso->DEP, 10), W_GUI / 1.08, HEIGHT / 3.8);
	}
	aff_tile(renderer, pack_texture, 1, 1, text_perso, 2.3);
	creerTexte(renderer, police, classe, W_GUI / 2.2, HEIGHT / 70);
	creerTexte(renderer, police, race, W_GUI / 2.2, HEIGHT / 17);
}

void aff_radius_perso(SDL_Renderer *renderer, case_t *map, int x, int y, int DEP){
/**Fonction affichant les deplacements possibles du perso en fonction de sa capacite de deplacement*/
	SDL_Rect rect_select;
	rect_select.w = rect_select.h = LARGEUR_CASE;

	int i, j, k, rad, *tab, nb_dep, POR = (map + x*M + y)->perso->POR, J = (map + x*M + y)->perso->J;

	if (!(tab = malloc(sizeof(int) * (N*M)))){
		printf("Erreur allocation mémoire map_to_bool\n");
		exit(EXIT_FAILURE);
	}

	for (i = x - DEP, rad = 0; i < (x+1); i++, rad++){
		for (j = y - rad, k = 0; k < (rad * 2+1); j++, k++){
			if (valides(i, j)){
				if (perso_allie(J, (map + i*M + j)->textures[RP]))
					continue;
				rect_select.x = j * LARGEUR_CASE;
				rect_select.y = i * LARGEUR_CASE;
				if (case_valide(map, i, j) == SDL_TRUE){

					map_to_bool(map, tab, i, j);
					if (chercher_chemin(tab, x, y, i, j)){
						marquer_chemin(tab, i, j, &nb_dep);

						if (DEP >= nb_dep - 1)
							SDL_SetRenderDrawColor(renderer, 0, 0, 255, OP_B);
						else
							SDL_SetRenderDrawColor(renderer, 255, 0, 0, OP_R);
					}
				}
				else
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, OP_R);

				SDL_RenderFillRect(renderer, &rect_select);
			}
		}
	}
	for (i = x + DEP, rad = 0; i > x; i--, rad++){
		for (j = y - rad, k = 0; k < (rad * 2+1); j++, k++){
			if (valides(i, j)){
				if (perso_joueur((map + i*M + j)->textures[RP]) || perso_bot((map + i*M + j)->textures[RP]))
					continue;
				rect_select.x = j * LARGEUR_CASE;
				rect_select.y = i * LARGEUR_CASE;
				if (case_valide(map, i, j) == SDL_TRUE){

					map_to_bool(map, tab, i, j);
					if (chercher_chemin(tab, x, y, i, j)){
						marquer_chemin(tab, i, j, &nb_dep);

						if (DEP >= nb_dep - 1)
							SDL_SetRenderDrawColor(renderer, 0, 0, 255, OP_B);
						else
							SDL_SetRenderDrawColor(renderer, 255, 0, 0, OP_R);
					}
				}
				else
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, OP_R);

				SDL_RenderFillRect(renderer, &rect_select);
			}
		}
	}

	for (i = x - DEP - POR - 1; i < (x + DEP + POR + 1); i++){
		for (j = y - DEP - POR - 1; j < (y + DEP + POR + 1); j++){
			if (valides(i, j)){
				if (perso_joueur((map + i*M + j)->textures[RP]) || perso_bot((map + i*M + j)->textures[RP])){
					map_to_bool(map, tab, i, j);
					if (chercher_chemin(tab, x, y, i, j)){
						marquer_chemin(tab, i, j, &nb_dep);

						if (DEP + POR >= nb_dep - 1){
							rect_select.x = j * LARGEUR_CASE;
							rect_select.y = i * LARGEUR_CASE;

							if (perso_allie(!J, (map + i*M + j)->textures[RP]))
								SDL_SetRenderDrawColor(renderer, 186, 85, 211, 165);
							else
								SDL_SetRenderDrawColor(renderer, 0, 255, 0, OP_V);
							SDL_RenderFillRect(renderer, &rect_select);
						}
					}
				}
			}
		}
	}


	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	free(tab);
}

void perso_attaquer(case_t *map, joueur_t *joueurs, perso_t *p1, perso_t *p2){
	p2->PV -= (p1->ATK - p2->DEF);

	if (p2->PV <= 0){
		change_val_text(map, RP, p2->x, p2->y, PERSO_MORT);
		clean_perso((map + M*(p2->x) + p2->y)->perso);
		(map + M*(p2->x) + p2->y)->is_perso = SDL_FALSE;
		retirer_perso(map, (joueurs + p2->J), p2->indice);
	}
	else{
		perso_copy(p2, (map + M*(p2->x) + p2->y)->perso);

		if (p2->POR >= p1->POR){
			p1->PV -= (p2->ATK - p1->DEF);

			if (p1->PV <= 0){
				change_val_text(map, RP, p1->x, p1->y, PERSO_MORT);
				clean_perso((map + M*(p1->x) + p1->y)->perso);
				(map + M*(p1->x) + p1->y)->is_perso = SDL_FALSE;
				retirer_perso(map, (joueurs + p1->J), p1->indice);
			}
			else
				perso_copy(p1, (map + M*(p1->x) + p1->y)->perso);
		}
	}
}

int indice_perso(joueur_t *team, J_t J, int x, int y){
	int i;

	for (i = 0; i < (team + J)->nb_persos; i++)
		if (((team+J)->team+i)->x == x && ((team+J)->team+i)->y == y)
			return i;
	
	return -1;
}

void retirer_perso(case_t *map, joueur_t *joueur, int indice){
	int i;

	for (i = indice; i < joueur->nb_persos - 1; i++){
		(joueur->team+i+1)->indice--;
		perso_copy((joueur->team+i+1), (joueur->team+i));
		perso_copy((joueur->team+i), (map + M * ((joueur->team+i)->x) + ((joueur->team+i)->y ))->perso );
	}
	clean_perso((joueur->team+i));
	joueur->nb_persos--;
}

SDL_bool tour_joueur(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *police,
 SDL_Window *window_gui, SDL_Renderer *renderer_gui, TTF_Font *police_gui, case_t *map,
  joueur_t *joueurs, SDL_Texture *pack_texture, SDL_Texture *pack_texture_gui, SDL_Texture *interface){
/**Fonction gérant le tour du joueur**/

	Uint32 id_main_window = SDL_GetWindowID(window);
	Uint32 id_window_gui = SDL_GetWindowID(window_gui);

	/**------------------Autres variables-----------------------------------------------------**/

	SDL_Rect validation;
	validation.w = TAILLE_FONT_GUI*5;
	validation.h = TAILLE_FONT_GUI;
	validation.x = (WIDTH / 3.5)/2 - validation.w/2;
	validation.y = HEIGHT - validation.h;


	SDL_Rect rect_select;
	rect_select.w = rect_select.h = LARGEUR_CASE;

	coords_t c_a;

	int i, j, old_i, old_j, nb_dep;
	int *tab;

	if (!(tab = malloc(sizeof(int) * (N*M)))){
		printf("Erreur allocation mémoire map_to_bool\n");
		exit(EXIT_FAILURE);
	}

	SDL_RenderClear(renderer);
	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			if ((map + M*i + j)->is_perso == SDL_TRUE)
				(map + M*i + j)->perso->is_dep = SDL_FALSE;
	aff_map(map, renderer, pack_texture);
	SDL_RenderPresent(renderer);

	SDL_RenderClear(renderer_gui);
	aff_tile(renderer_gui, interface, 0, 0, -1, 1);
	creerTexte(renderer_gui, police, "Vous jouez !", 90, 500);
	bouton_check(renderer_gui, &validation, police_gui);
	SDL_RenderPresent(renderer_gui);

	SDL_bool tour_launched = SDL_TRUE, click = SDL_FALSE, jeu_launched = SDL_TRUE;
    SDL_Event event;

/**----------------------Debut du tour--------------------------------------------------------**/

	while (tour_launched){
        SDL_WaitEvent(&event);

		if (event.window.windowID == id_main_window){
/**------------------Evenement sur fenetre principale--------------------------------------**/
			switch(event.type){
				case SDL_QUIT: 
					tour_launched = SDL_FALSE;
					jeu_launched = SDL_FALSE;
					break;

				case SDL_MOUSEBUTTONDOWN:

					switch(event.button.button){
						case SDL_BUTTON_LEFT:
							i = event.button.y / LARGEUR_CASE;
							j = event.button.x / LARGEUR_CASE;

							SDL_RenderClear(renderer);

							if (click == SDL_TRUE){
								map_to_bool(map, tab, i, j);
								if(chercher_chemin(tab, old_i, old_j, i, j)){
									marquer_chemin(tab, i, j, &nb_dep);

									nb_dep--;
									if (perso_bot((map + M*i + j)->textures[RP]) && ((map + M*old_i + old_j)->perso->DEP + (map + M*old_i + old_j)->perso->POR) >= nb_dep){
										if (nb_dep > 1){
											c_a = remarquer_chemin(tab, old_i, old_j, (nb_dep - (map + M*old_i + old_j)->perso->POR));

											#ifdef DEBUG
												printf("from %d-%d to %d-%d\n", old_i, old_j, c_a.x, c_a.y);
											#endif

											if (old_i != c_a.x || old_j != c_a.y){
											/**Attaque**/
												(map + M*old_i + old_j)->perso->is_dep = SDL_TRUE;
												move_perso(map, c_a.x, c_a.y, old_i, old_j);
												perso_copy((map + M*c_a.x + c_a.y)->perso, ((joueurs+J1)->team + (map + M*c_a.x + c_a.y)->perso->indice));
											}
										}
										else{
											c_a.x = i;
											c_a.y = j;
										}
										int indice = indice_perso(joueurs, BOT, i, j);
										perso_attaquer(map, joueurs, ((joueurs+J1)->team + (map + M*c_a.x + c_a.y)->perso->indice), ((joueurs+BOT)->team+indice));
									}
									else if (case_valide(map, i, j)){
											if ((map + M*old_i + old_j)->perso->DEP >= nb_dep){
												(map + M*old_i + old_j)->perso->is_dep = SDL_TRUE;
												move_perso(map, i, j, old_i, old_j);
												perso_copy((map + M*i + j)->perso, ((joueurs+J1)->team + (map + M*i + j)->perso->indice));
											}
									}
								}
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
								creerTexte(renderer_gui, police, "Vous jouez !", 90, 500);
								SDL_RenderPresent(renderer_gui);

								rect_select.x = j * LARGEUR_CASE;
								rect_select.y = i * LARGEUR_CASE;

								aff_map(map, renderer, pack_texture);
								SDL_SetRenderDrawColor(renderer, 0, 255, 0, OP_V);
								SDL_RenderFillRect(renderer, &rect_select);

								aff_radius_perso(renderer, map, i, j, (map + M*i +j)->perso->DEP);

								if ((map + M*i +j)->perso->is_dep == SDL_FALSE)
									click = SDL_TRUE;

								old_i = i;
								old_j = j;
							}
							else if (perso_bot( (map + M*i + j)->textures[RP]) && click == SDL_FALSE){
								SDL_RenderClear(renderer_gui);
								aff_tile(renderer_gui, interface, 0, 0, -1, 1);
								aff_perso(renderer_gui, pack_texture_gui, police_gui, (map + M*i +j)->perso, VIDE);
								bouton_check(renderer_gui, &validation, police_gui);
								creerTexte(renderer_gui, police, "Vous jouez !", 90, 500);
								SDL_RenderPresent(renderer_gui);

								aff_map(map, renderer, pack_texture);
							}
							else
								aff_map(map, renderer, pack_texture);
							SDL_RenderPresent(renderer);
							break;
					}
					break;


				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							tour_launched = SDL_FALSE;
							jeu_launched = SDL_FALSE;
							break;

						case SDLK_a:
							aff_persos_console(map);
							break;
					}
			}
		}
		else if (event.window.windowID == id_window_gui){
/**------------------Evenement sur fenetre interface------------------------------------------**/
			switch(event.type){
				case SDL_QUIT: 
					tour_launched = SDL_FALSE;
					jeu_launched = SDL_FALSE;
					break;

				case SDL_MOUSEBUTTONDOWN:
					if (clickSurCase(event, validation))
						tour_launched = SDL_FALSE;
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							tour_launched = SDL_FALSE;
							jeu_launched = SDL_FALSE;
							break;
					}
			}
		}

		if ((joueurs + BOT)->nb_persos == 0 || (joueurs + J1)->nb_persos == 0){
			tour_launched = SDL_FALSE;
			jeu_launched = SDL_FALSE;
		}
	}
	free(tab);

	return jeu_launched;
}

SDL_bool chercher_chemin(int *tab,int xd, int yd, int xa, int ya){
/**Cherche le chemin D -> A le plus court avec une file Renvoie VRAI si un chemin existe, FAUX sinon**/
  int x = xd, y = yd;

  initfile();

  *(tab+xd*M+yd) = 1;

  for(int i = 1; !*(tab+xa*M+ya); i++){
    while(*(tab+x*M+y) == i){
      for(int dRow = -1; dRow <= 1; dRow++){
        for(int dYaw = -1; dYaw <= 1; dYaw++){
          if(valides(x+dRow,y+dYaw) && *(tab+(x+dRow)*M+(y+dYaw)) == 0 && (dRow+dYaw)*(dRow+dYaw) == 1){
            *(tab+(x+dRow)*M+(y+dYaw)) = i+1;
            ajouter(x+dRow);
            ajouter(y+dYaw);
          }
        }
      }
      if(filevide())
        return SDL_FALSE;

      retirer(&x);
      retirer(&y);
    }
  }
  return SDL_TRUE;
}

void marquer_chemin(int *tab,int x, int y, int *lgmin){
/** Marque le chemin le plus court a partir de *(tab+x*M+y) Renvoie sa taille dans lgmin**/

  *lgmin = *(tab+x*M+y);
  for(int val = *(tab+x*M+y); val >= 1; val--)
    for(int i = 0; i < N; i++)
      for(int j = 0; j < M; j++)
        if(*(tab+i*M+j) == val)
          for(int dRow = -1; dRow <= 1; dRow++)
            for(int dYaw = -1; dYaw <= 1; dYaw++)
              if(valides(i+dRow,j+dYaw) && (*(tab+(i+dRow)*M+(j+dYaw)) == -2 || (x == i && y == j)) && (dRow+dYaw)*(dRow+dYaw) == 1)
                *(tab+i*M+j) = -2;

}

void *map_to_bool(case_t *map, int *tab, int xa, int ya){
/**Fonction qui transforme la map en couloirs/murs**/
	int i, j;

	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++){
			if (case_valide(map, i, j) || (i == xa && j == ya))
				*(tab + i*M + j) = 0;
			else
				*(tab + i*M + j) = -1;	
		}
}

void aff_mat(int *tab){
	int i, j;

	for (i = 0; i < N; i++){
		for (j = 0; j < M; printf("%d ", *(tab + i*M + j)), j++);
		putchar('\n');
	}
}

void mat_copy(int *src, int *dest){
	int i, j;

	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			*(dest+i*M+j) = *(src+i*M+j);
}

coords_t remarquer_chemin(int *tab, int x1, int y1, int dep){
	int i, j, k;
	coords_t c;

	for (i = x1, j = y1, k = 0; k < dep;){
		for (; valides(i-1, j) && *(tab + (i-1)*M + j) == -2 && k < dep; *(tab + i*M + j) = 0, i--, k++);
		for (; valides(i+1, j) && *(tab + (i+1)*M + j) == -2 && k < dep; *(tab + i*M + j) = 0, i++, k++);
		for (; valides(i, j-1) && *(tab + i*M + (j-1)) == -2 && k < dep; *(tab + i*M + j) = 0, j--, k++);
		for (; valides(i, j+1) && *(tab + i*M + (j+1)) == -2 && k < dep; *(tab + i*M + j) = 0, j++, k++);
	}
	c.x = i;
	c.y = j;

	return c;
}

SDL_bool tour_bot(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *police,
 SDL_Window *window_gui, SDL_Renderer *renderer_gui, TTF_Font *police_gui, case_t *map,
  joueur_t *joueurs, SDL_Texture *pack_texture, SDL_Texture *pack_texture_gui, SDL_Texture *interface){
/**Fonction gerant le tour de l'adversaire**/
	
	int i, j, xd, yd, xa, ya, nb_dep, min, x_min, y_min;

	SDL_bool do_attaque = SDL_FALSE;

	coords_t c_a;

	int *tab, *tab_copy;
	
	if (!(tab = malloc(sizeof(int) * (N*M)))){
		printf("Erreur allocation mémoire map_to_bool\n");
		exit(EXIT_FAILURE);
	}
	if (!(tab_copy = malloc(sizeof(int) * (N*M)))){
		printf("Erreur allocation mémoire map_to_bool\n");
		exit(EXIT_FAILURE);
	}

	#ifdef DEBUG
		aff_team_console((joueurs + J1)->team, (joueurs + J1)->nb_persos);
	#endif

	for (i = 0; i < (joueurs+BOT)->nb_persos; i++){
		xd = ((joueurs+BOT)->team+i)->x;
		yd = ((joueurs+BOT)->team+i)->y;

		if (!valides(xd, yd))
			continue;

		#ifdef DEBUG
			printf("BOT : %d-%d\n", xd, yd);
		#endif

		for (j = 0, min = 1000; j < (joueurs+J1)->nb_persos; j++){
			xa = ((joueurs+J1)->team+j)->x;
			ya = ((joueurs+J1)->team+j)->y;

			map_to_bool(map, tab, xa, ya);

			if(chercher_chemin(tab, xd, yd, xa, ya)){
				marquer_chemin(tab, xa, ya, &nb_dep);

				#ifdef DEBUG
					printf("J1 : %d-%d\n", xa, ya);
					printf("%d-%d, Nb deps : %d\n", xa, ya, nb_dep);
				#endif

				if (((joueurs+BOT)->team+i)->DEP + ((joueurs+BOT)->team+i)->POR >= nb_dep - 1){
					do_attaque = SDL_TRUE;
					x_min = xa;
					y_min = ya;
					nb_dep--;
					min = nb_dep;
					mat_copy(tab, tab_copy);
					break;
				}
				else if (nb_dep < min){
					min = nb_dep;
					x_min = xa;
					y_min = ya;

					mat_copy(tab, tab_copy);
				}
			}
		}

		#ifdef DEBUG
			printf("%d : Perso le plus proche : %d-%d, %d deps\n\n", i, x_min, y_min, min);
		#endif

		if(chercher_chemin(tab_copy, xd, yd, x_min, y_min)){
			marquer_chemin(tab_copy, x_min, y_min, &nb_dep);

			if (do_attaque)
				c_a = remarquer_chemin(tab_copy, xd, yd, min - ((joueurs+BOT)->team+i)->POR);
			else
				c_a = remarquer_chemin(tab_copy, xd, yd, ((joueurs+BOT)->team+i)->DEP - 1);

			#ifdef DEBUG
				printf("From %d-%d to %d-%d\n", xd, yd, c_a.x, c_a.y);
			#endif
		}

		if (valides(c_a.x, c_a.y)){
			SDL_RenderClear(renderer_gui);
			aff_tile(renderer_gui, interface, 0, 0, -1, 1);
			aff_perso(renderer_gui, pack_texture_gui, police_gui,  ((joueurs+BOT)->team+i), VIDE);
			creerTexte(renderer_gui, police, "Tour du BOT !", 70, 500);
			SDL_RenderPresent(renderer_gui);

			SDL_RenderClear(renderer);
			aff_map(map, renderer, pack_texture);

			aff_radius_perso(renderer, map, ((joueurs+BOT)->team+i)->x, ((joueurs+BOT)->team+i)->y, ((joueurs+BOT)->team+i)->DEP);
			SDL_RenderPresent(renderer);
			SDL_Delay(1000);

			SDL_RenderClear(renderer);

			if (c_a.x != ((joueurs+BOT)->team+i)->x || c_a.y != ((joueurs+BOT)->team+i)->y){
				move_perso(map, c_a.x, c_a.y,  ((joueurs+BOT)->team+i)->x,  ((joueurs+BOT)->team+i)->y);
				perso_copy((map + c_a.x*M + c_a.y)->perso, ((joueurs+BOT)->team+i));

				((joueurs+BOT)->team+i)->x = c_a.x;
				((joueurs+BOT)->team+i)->y = c_a.y;
			}

			if (do_attaque){
				int indice = indice_perso(joueurs, J1, xa, ya);
				perso_attaquer(map, joueurs, ((joueurs+BOT)->team+i), ((joueurs+J1)->team+indice));
			}

			aff_map(map, renderer, pack_texture);
			SDL_RenderPresent(renderer);

			SDL_Delay(800);
		}
		if (do_attaque)
			do_attaque = SDL_FALSE;
	}

	free(tab);
	free(tab_copy);

	return (!((joueurs + BOT)->nb_persos == 0 || (joueurs + J1)->nb_persos == 0));
}

joueur_t *creer_joueurs(int nb_persos){
/**Fonction qui initialise les joueurs**/
	joueur_t *J = malloc(sizeof(joueur_t) * 2);
	(J + J1)->nb_persos = nb_persos;
	(J + BOT)->nb_persos = nb_persos;

	return J;
}

void lancer_jeu(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *pack_texture, case_t *map){
/**Fonction Principale**/
	SDL_Window *window_gui = NULL;
	SDL_Renderer *renderer_gui = NULL;

/**------------------Initialisation de la fenetre et du renderer du gui + polices----------------------**/

	window_gui = SDL_CreateWindow("Interface combat", WIDTH + 15, 50, (WIDTH / 3.5), HEIGHT, SDL_WINDOW_SHOWN);

	if(window_gui == NULL)
		SDL_ExitWithError("Erreur à la création de la fenetre\n", window_gui, NULL, NULL);

	renderer_gui = SDL_CreateRenderer(window_gui, -1, SDL_RENDERER_ACCELERATED);
	if(renderer_gui == NULL)
		SDL_ExitWithError("Erreur à la création du renderer\n", window_gui, renderer_gui, NULL);

	
	TTF_Font *police = TTF_OpenFont(NOM_FONT, TAILLE_MAIN_FONT);
	if (!police)
		SDL_ExitWithError("Erreur du chargement de la police", window, renderer, NULL);

	TTF_Font *police_gui = TTF_OpenFont(NOM_FONT, TAILLE_FONT_GUI);
	if (!police_gui)
		SDL_ExitWithError("Erreur du chargement de la police", window, renderer, NULL);

/**------------------Creation des textures----------------------------------------------------**/

	SDL_Texture *interface = creerTexture(window_gui, renderer_gui, "imgs/gui.png");
	SDL_Texture *pack_texture_gui = creerTexture(window_gui, renderer_gui, "imgs/packtexture.png");

/**------------------Initialisation Jeu---------------------------------------------------**/

	int nb_persos = randint(MIN_PERSO, MAX_PERSO);
	
	aff_tile(renderer_gui, interface, 0, 0, -1, 1);
	SDL_RenderPresent(renderer_gui);

	joueur_t *joueurs = creer_joueurs(nb_persos);

	(joueurs + J1)->team = create_team(window, renderer, police, window_gui, renderer_gui, police_gui, map, pack_texture, pack_texture_gui, interface, nb_persos);
	(joueurs + BOT)->team = create_team_bot(nb_persos);

	load_matrice(map, randint(1, NB_MAPS));
	placer_persos(map, (joueurs + J1)->team, nb_persos, 0, 5);
	placer_persos(map, (joueurs + BOT)->team, nb_persos, M-6, M-1);

	SDL_RenderClear(renderer);
	aff_map(map, renderer, pack_texture);
	SDL_RenderPresent(renderer);

	deplacer_persos(window, renderer, police, window_gui, renderer_gui, police_gui, map, pack_texture, pack_texture_gui, interface);


	#ifdef DEBUG
		aff_team_console((joueurs + J1)->team, nb_persos);
		putchar('\n');
		aff_team_console((joueurs + BOT)->team, nb_persos);
		putchar('\n');
		aff_persos_console(map);
	#endif


	SDL_RenderClear(renderer);
	aff_map(map, renderer, pack_texture);
	SDL_RenderPresent(renderer);


/**------------------Autres variables-----------------------------------------------------**/

	///Determine quel joueur commence à jouer

	SDL_bool jeu_launched = SDL_TRUE, tour_j1 = randint(0, 1);

/**------------------Debut du programme de jeu------------------------------------------**/

	while (jeu_launched){
		if (tour_j1)
			jeu_launched = tour_joueur(window, renderer, police, window_gui, renderer_gui, police_gui, map, joueurs, pack_texture, pack_texture_gui, interface);
		else
			jeu_launched = tour_bot(window, renderer, police, window_gui, renderer_gui, police_gui, map, joueurs, pack_texture, pack_texture_gui, interface);		

		(tour_j1)?(tour_j1 = SDL_FALSE):(tour_j1 = SDL_TRUE);
	}

	if ((joueurs + BOT)->nb_persos == 0 || (joueurs + J1)->nb_persos == 0){

		police = TTF_OpenFont(NOM_FONT, 120);
		if (!police)
			SDL_ExitWithError("Erreur du chargement de la police", window, renderer, NULL);

		if ((joueurs + BOT)->nb_persos == 0 && (joueurs + J1)->nb_persos == 0)
			creerTexte(renderer, police, "Match nul !!!", HEIGHT / 2, (WIDTH/2)- 13 * 120);
		else if ((joueurs + BOT)->nb_persos == 0)
			creerTexte(renderer, police, "Vous gagnez la partie !!!", 150, 300);//HEIGHT / 2, (WIDTH/2)- 25 * 120);
		else if ((joueurs + J1)->nb_persos == 0)
			creerTexte(renderer, police, "Vous perdez la partie !!!", HEIGHT / 2, (WIDTH/2)- 25 * 120);

		SDL_RenderPresent(renderer);
		SDL_Delay(3000);
	}

    

/**------------------Liberation de la mémoire allouee----------------------------------------**/
	free(police);
	free(police_gui);
	SDL_DestroyTexture(interface);
	SDL_DestroyTexture(pack_texture_gui);
	SDL_DestroyRenderer(renderer_gui);
	SDL_DestroyWindow(window_gui);

/**------------------Fin du programme de jeu-------------------------------------------**/

	menu(window, renderer, map, pack_texture);
}

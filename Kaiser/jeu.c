#include "commun.h"

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

	int i, j, k, rad;

	for (i = x - DEP, rad = 0; i < (x+1); i++, rad++){
		for (j = y - rad, k = 0; k < (rad * 2+1); j++, k++){
			if (i == x && j == y)
				continue;
			if (valides(i, j)){
				rect_select.x = j * LARGEUR_CASE;
				rect_select.y = i * LARGEUR_CASE;
				if (case_valide(map, i, j) == SDL_TRUE)
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, OP_B);
				else
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, OP_R);

				SDL_RenderFillRect(renderer, &rect_select);
			}
		}
	}
	for (i = x + DEP, rad = 0; i > x; i--, rad++){
		for (j = y - rad, k = 0; k < (rad * 2+1); j++, k++){
			if (valides(i, j)){
				rect_select.x = j * LARGEUR_CASE;
				rect_select.y = i * LARGEUR_CASE;
				if (case_valide(map, i, j) == SDL_TRUE)
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, OP_B);
				else
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, OP_R);

				SDL_RenderFillRect(renderer, &rect_select);
			}
		}
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

SDL_bool tour_joueur(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *police,
 SDL_Window *window_gui, SDL_Renderer *renderer_gui, TTF_Font *police_gui, case_t *map,
  joueur_t *joueurs, SDL_Texture *pack_texture, SDL_Texture *pack_texture_gui, SDL_Texture *interface){
/**Fonction gérant le tour du joueur**/

	Uint32 id_main_window = SDL_GetWindowID(window);
	Uint32 id_window_gui = SDL_GetWindowID(window_gui);

	/**------------------Autres variables-----------------------------------------------------**/

	SDL_Rect validation;
	validation.w = TAILLE_MAIN_FONT*5;
	validation.h = TAILLE_MAIN_FONT;
	validation.x = WIDTH/2 - validation.w/2;
	validation.y = HEIGHT - validation.h;

	SDL_Rect rect_select;
	rect_select.w = rect_select.h = LARGEUR_CASE;

	int i, j, old_i, old_j, nb_dep;
	int *tab;

	if (!(tab = malloc(sizeof(int) * (N*M)))){
		printf("Erreur allocation mémoire map_to_bool\n");
		exit(EXIT_FAILURE);
	}

	SDL_bool tour_launched = SDL_TRUE, click = SDL_FALSE, menu_asked = SDL_FALSE, jeu_launched = SDL_TRUE;
    SDL_Event event;

/**----------------------Debut du tour--------------------------------------------------------**/

	while (tour_launched){
        SDL_WaitEvent(&event);

		if (event.window.windowID == id_main_window){
/**------------------Evenement sur fenetre principale--------------------------------------**/
			switch(event.type){
				case SDL_QUIT: 
					tour_launched = SDL_FALSE;
					menu_asked = SDL_TRUE;
					break;

				case SDL_MOUSEBUTTONDOWN:

					switch(event.button.button){
						case SDL_BUTTON_LEFT:
							if (clickSurCase(event, validation))
								tour_launched = SDL_FALSE;
							else{
								i = event.button.y / LARGEUR_CASE;
								j = event.button.x / LARGEUR_CASE;

								SDL_RenderClear(renderer);

								if (click == SDL_TRUE){
									if (case_valide(map, i, j)){
										map_to_bool(map, tab);
										if(chercher_chemin(tab, old_i, old_j, i, j)){
											marquer_chemin(tab, i, j, &nb_dep);

											if ((map + M*old_i + old_j)->perso->DEP >= nb_dep - 1){
												move_perso(map, i, j, old_i, old_j);
												perso_copy((map + M*i + j)->perso, ((joueurs+J1)->team + (map + M*i + j)->perso->indice));
											}
										}
									}
									aff_map(map, renderer, pack_texture);
									click = SDL_FALSE;
								}
								else if (perso_allie( (map + M*i + j)->textures[RP])){
									SDL_RenderClear(renderer_gui);
									aff_tile(renderer_gui, interface, 0, 0, -1, 1);

									#ifdef DEBUG
										aff_perso_console((map + M*i +j)->perso);
									#endif

									aff_perso(renderer_gui, pack_texture_gui, police_gui, (map + M*i +j)->perso, VIDE);
									SDL_RenderPresent(renderer_gui);

									rect_select.x = j * LARGEUR_CASE;
									rect_select.y = i * LARGEUR_CASE;

									aff_map(map, renderer, pack_texture);
									SDL_SetRenderDrawColor(renderer, 0, 255, 0, OP_V);
									SDL_RenderFillRect(renderer, &rect_select);

									aff_radius_perso(renderer, map, i, j, (map + M*i +j)->perso->DEP);

									click = SDL_TRUE;
									old_i = i;
									old_j = j;
								}
								else if (perso_bot( (map + M*i + j)->textures[RP])){
									SDL_RenderClear(renderer_gui);
									aff_tile(renderer_gui, interface, 0, 0, -1, 1);
									aff_perso(renderer_gui, pack_texture_gui, police_gui, (map + M*i +j)->perso, VIDE);
									SDL_RenderPresent(renderer_gui);

									aff_map(map, renderer, pack_texture);
								}
								else
									aff_map(map, renderer, pack_texture);
								
								bouton_check(renderer, &validation, police);
								SDL_RenderPresent(renderer);
							}
							break;
					}
					break;


				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							tour_launched = SDL_FALSE;
							menu_asked = SDL_TRUE;
							break;

						case SDLK_e:
							jeu_launched = SDL_FALSE;
					}
			}
		}
		else if (event.window.windowID == id_window_gui){
/**------------------Evenement sur fenetre interface------------------------------------------**/

			switch(event.type){
				case SDL_QUIT: 
					tour_launched = SDL_FALSE;
					menu_asked = SDL_TRUE;
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							tour_launched = SDL_FALSE;
							menu_asked = SDL_TRUE;
							break;
					}
			}
		}
	}
	free(tab);

	if (menu_asked){
		free(police_gui);
		free(police);
		SDL_DestroyTexture(pack_texture_gui);
		SDL_DestroyTexture(interface);
		SDL_DestroyRenderer(renderer_gui);
		SDL_DestroyWindow(window_gui);
		menu(window, renderer, map, pack_texture);
	}
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

void *map_to_bool(case_t *map, int *tab){
/**Fonction qui transforme la map en couloirs/murs**/
	int i, j;

	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++){
			if (case_valide(map, i, j) || perso_allie((map+i*M+j)->textures[RP]))
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
		for (; valides(i-1, j) && *(tab + (i-1)*M + j) == -2 && k < dep; i--, k++);
		for (; valides(i+1, j) && *(tab + (i+1)*M + j) == -2 && k < dep; i++, k++);
		for (; valides(i, j-1) && *(tab + i*M + (j-1)) == -2 && k < dep; j--, k++);
		for (; valides(i, j+1) && *(tab + i*M + (j+1)) == -2 && k < dep; j++, k++);
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

	SDL_Rect rect_select;
	rect_select.w = rect_select.h = LARGEUR_CASE;

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

	aff_team_console((joueurs + J1)->team, (joueurs + J1)->nb_persos);

	for (i = 0; i < (joueurs+BOT)->nb_persos; i++){
		xd = ((joueurs+BOT)->team+i)->x;
		yd = ((joueurs+BOT)->team+i)->y;

		if (!valides(xd, yd))
			continue;

		#ifdef DEBUG
			printf("BOT : %d-%d\n", xd, yd);
		#endif
		map_to_bool(map, tab);
		mat_copy(tab, tab_copy);

		for (j = 0, min = 1000; j < (joueurs+J1)->nb_persos; j++){
			if (j > 0)
				map_to_bool(map, tab);

			xa = ((joueurs+J1)->team+j)->x;
			ya = ((joueurs+J1)->team+j)->y;

			if(chercher_chemin(tab, xd, yd, xa, ya)){
				marquer_chemin(tab, xa, ya, &nb_dep);

				#ifdef DEBUG
					printf("J1 : %d-%d\n", xa, ya);
					printf("%d-%d, Nb deps : %d\n", xa, ya, nb_dep);
				#endif
			}
			if (nb_dep < min){
				min = nb_dep;
				x_min = xa;
				y_min = ya;
			}
		}

		//#ifdef DEBUG
			printf("\n%d : Perso le plus proche : %d-%d, %d deps\n\n", i, x_min, y_min, min);
		//#endif

		if (!valides(x_min, y_min))
			continue;

		if(chercher_chemin(tab_copy, xd, yd, x_min, y_min)){
			marquer_chemin(tab_copy, x_min, y_min, &nb_dep);

			c_a = remarquer_chemin(tab_copy, xd, yd, ((joueurs+BOT)->team+i)->DEP);

			//#ifdef DEBUG
				printf("From %d-%d to %d-%d\n", xd, yd, c_a.x, c_a.y);
			//#endif
			aff_perso_console((joueurs+BOT)->team+i);

		}

		if (valides(c_a.x, c_a.y) && case_valide(map, c_a.x, c_a.y)){
			SDL_RenderClear(renderer_gui);
			aff_tile(renderer_gui, interface, 0, 0, -1, 1);
			aff_perso(renderer_gui, pack_texture_gui, police_gui,  ((joueurs+BOT)->team+i), VIDE);
			SDL_RenderPresent(renderer_gui);

			SDL_RenderClear(renderer);
			aff_map(map, renderer, pack_texture);

			rect_select.x = ((joueurs+BOT)->team+i)->y * LARGEUR_CASE;
			rect_select.y = ((joueurs+BOT)->team+i)->x * LARGEUR_CASE;

			aff_map(map, renderer, pack_texture);
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, OP_V);
			SDL_RenderFillRect(renderer, &rect_select);

			aff_radius_perso(renderer, map, ((joueurs+BOT)->team+i)->x, ((joueurs+BOT)->team+i)->y, ((joueurs+BOT)->team+i)->DEP);
			SDL_RenderPresent(renderer);
			SDL_Delay(1000);

			SDL_RenderClear(renderer);

			move_perso(map, c_a.x, c_a.y,  ((joueurs+BOT)->team+i)->x,  ((joueurs+BOT)->team+i)->y);
			perso_copy((map + c_a.x*M + c_a.y)->perso, ((joueurs+BOT)->team+i));

			((joueurs+BOT)->team+i)->x = c_a.x;
			((joueurs+BOT)->team+i)->y = c_a.y;

			aff_map(map, renderer, pack_texture);
			SDL_RenderPresent(renderer);

			SDL_Delay(800);
		}
	}

	free(tab);
	free(tab_copy);

	return SDL_TRUE;
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

	SDL_Texture *interface = creerTexture(window_gui, renderer_gui, "gui.png");
	SDL_Texture *pack_texture_gui = creerTexture(window_gui, renderer_gui, "packtexture.png");

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

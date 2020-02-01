p = (float)*(map + M*i + j) / (float)NOMBRE_BLOCS_LARGEUR;
texture_actuelle_x = (int)p;
p = (p - texture_actuelle_x) * 100;
texture_actuelle_y = NOMBRE_BLOCS_LARGEUR * p / 100;
select_tile(renderer, texture_tiles, i, j, texture_actuelle_x, texture_actuelle_y);

i--;
select_tile(renderer, texture_tiles, i, j, 44, 15);
SDL_RenderPresent(renderer);


case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							program_launched = SDL_FALSE;
							break;
						case SDLK_UP:
							break;
						case SDLK_DOWN:
							break;
						case SDLK_RIGHT:
							break;
						case SDLK_LEFT:
							break;
					}
					break;


x = event.button.y / LARGEUR_EDIT;
					y = event.button.x / LARGEUR_EDIT;
					SDL_Log("%d-%d  --> map[%d][%d]\n", event.button.x, event.button.y, x, y);
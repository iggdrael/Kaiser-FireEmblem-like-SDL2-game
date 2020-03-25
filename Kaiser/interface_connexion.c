#include "fonctions.h"

char * choix_serveur(SDL_Window *window,SDL_Renderer *renderer, case_t *map, SDL_Texture *pack_texture)
{
  SDL_Event event;
  SDL_bool serv_launched = SDL_TRUE;
  const int taille_police = 40;
  TTF_Font *police = TTF_OpenFont("caviardreams.ttf", taille_police);
  char ip[50];
  char tmp;
  int i=0, j = 0, ecart=0;

  if (!police)
    SDL_ExitWithError("Erreur du chargement de la police", window, renderer, NULL);

  //SDL_RenderClear(renderer);
  load_matrice(map);
  aff_map(map, renderer, pack_texture);


  SDL_Rect rect;
  rect.w = WIDTH/8;
  rect.h = taille_police;
  rect.y = HEIGHT/8;

  rect.x=WIDTH/4;
  rect.y=HEIGHT/2;

  SDL_RenderFillRect(renderer, &rect);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &rect);
  //SDL_RenderPresent(renderer);

  while(serv_launched)
  {
    SDL_WaitEvent(&event);
      switch (event.type)
      {
        case SDL_KEYDOWN:
          if(event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
          {
            tmp = event.key.keysym.sym;
            creerTexte(renderer, police, &tmp, (WIDTH/2+ecart), HEIGHT/2);
            ip[i++] = tmp;
            ecart+=10;
          }

          if(event.key.keysym.sym == SDLK_PERIOD)
          {
            creerTexte(renderer, police, ".", WIDTH/2, HEIGHT/2);
            ip[i++] = '.';
          }

          if(event.key.keysym.sym == SDLK_ESCAPE)
            serv_launched=SDL_FALSE;

          if(event.key.keysym.sym == SDLK_BACKSPACE)
          {
            if(i != 0)
              ip[--i] = ' ';
            ecart-=10;
          }
          break;
      }
  }
  /*for(j=0; j<50; j++)
  {
    printf("%c", ip[j]);
  }
  printf("\n");*/
  free(police);
  return(ip);
}

/* 
Rappels de compilation :
> Windows          : gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
>(Sans le terminal): gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows
*/

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

void clean_ressources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t){
    if(t != NULL)
        SDL_DestroyTexture(t);
    if(r != NULL)
        SDL_DestroyRenderer(r);
    if(w != NULL)
        SDL_DestroyWindow(w);

    SDL_Quit();
}

void move_image(SDL_Rect *img, int direction, SDL_Window *w){
    switch(direction){
        case 0:
            img->y -= 50;
            if(img->y < 0)
                img->y = WINDOW_HEIGHT - img->h;
            break;
        case 1:
            img->x -= 50;
            if(img->x < 0)
                img->x = WINDOW_WIDTH - img->w;
            break;
        case 2:
            img->y += 50;
            if(img->y > WINDOW_HEIGHT - img->h)
                img->y = 0;
            break;
        case 3:
            img->x += 50;
            if(img->x > WINDOW_WIDTH - img->w)
                img->x = 0;
            break;
    }
}

int main(int argc, char **argv){

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *picture = NULL;
    SDL_Texture *texture = NULL;

    SDL_Rect personnage = {50, 0, 50, 90};
    SDL_Rect background = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    //Lancement SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_ressources(NULL, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    //Création fenêtre
    window = SDL_CreateWindow("Le bonhomme qui bougeait", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if(window == NULL){
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_ressources(NULL, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    //Création rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(renderer == NULL){
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_ressources(window, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    //Création du background
    if(SDL_SetRenderDrawColor(renderer, 86, 125, 70, SDL_ALPHA_OPAQUE) != 0){
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_ressources(window, renderer, texture);
        exit(EXIT_FAILURE);
    }

    SDL_RenderFillRect(renderer, &background);

    //Création image
    picture = IMG_Load("src/perso1.png");
    if(picture == NULL){
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_ressources(window, renderer, NULL);
        exit(EXIT_FAILURE);
    }

    //Création texture
    texture = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);
    if(texture == NULL){
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_ressources(window, renderer, NULL);
        exit(EXIT_FAILURE);
    }

    //Chargement texture
    if(SDL_QueryTexture(texture, NULL, NULL, &personnage.w, &personnage.h) != 0){
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_ressources(window, renderer, texture);
        exit(EXIT_FAILURE);
    }

    //Affichage texture
    if(SDL_RenderCopy(renderer, texture, NULL, &personnage) != 0){
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        clean_ressources(window, renderer, texture);
        exit(EXIT_FAILURE);
    }

    SDL_RenderPresent(renderer);
    
    /*-------------------------------------------------------------------*/
    SDL_bool program_launched = SDL_TRUE;
    int *window_w = NULL;
    int *window_h = NULL;

    while (program_launched){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_UP || event.key.keysym.scancode == SDL_SCANCODE_W){
                        move_image(&personnage, 0, window);
                        printf("UP, %dx:%dy\n", personnage.x, personnage.y);
                    }
                    if(event.key.keysym.sym == SDLK_LEFT || event.key.keysym.scancode == SDL_SCANCODE_A){
                        move_image(&personnage, 1, window);
                        printf("LEFT, %dx:%dy\n", personnage.x, personnage.y);
                    }
                    if(event.key.keysym.sym == SDLK_DOWN || event.key.keysym.scancode == SDL_SCANCODE_S){
                        move_image(&personnage, 2, window);
                        printf("DOWN, %dx:%dy\n", personnage.x, personnage.y);
                    }
                    if(event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.scancode == SDL_SCANCODE_D){
                        move_image(&personnage, 3, window);
                        printf("RIGHT, %dx:%dy\n", personnage.x, personnage.y);
                    }
                    /*if(event.key.keysym.sym == SDLK_c){
                        SDL_GetWindowSize(window, window_w, window_h);      //DOESN'T WORK
                        printf("Taille de la fenetre : %dpx/%dpx\n", window_w, window_h);
                    }*/
                    SDL_RenderClear(renderer);
                    if(SDL_RenderCopy(renderer, texture, NULL, &personnage) != 0){
                        SDL_Log("ERREUR > %s\n", SDL_GetError());
                        clean_ressources(window, renderer, texture);
                        exit(EXIT_FAILURE);
                    }
                    if(SDL_UpdateWindowSurfaceRects(window, &personnage, 1) != 0){
                        SDL_Log("ERREUR > %s\n", SDL_GetError());
                        clean_ressources(window, renderer, texture);
                        exit(EXIT_FAILURE);
                    }
                    if(SDL_UpdateWindowSurface(window) != 0){
                        SDL_Log("ERREUR > %s\n", SDL_GetError());
                        clean_ressources(window, renderer, texture);
                        exit(EXIT_FAILURE);
                    }
                    SDL_RenderPresent(renderer);

                break;


                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;

                default:
                    break;
            }
        }
    }
    /*-------------------------------------------------------------------*/

    //Fin du programme.
    clean_ressources(window, renderer, texture);

    return EXIT_SUCCESS; //return 0
}
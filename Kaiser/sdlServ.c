#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include<strings.h>
#include <sys/time.h>
#include <string.h>

#include <SDL.h>
#include <SDL_ttf.h>

#define SERVEURNAME "127.0.0.1" 
#define WIDTH 300
#define HEIGHT 300

void creerTexte(SDL_Renderer *renderer, TTF_Font *police, char *str, int x, int y){
/**Fonction affichant un texte "str" sur le renderer aux coordonees passees en parametres**/
	SDL_Surface *texte = NULL;
	SDL_Rect txtDestRect;
	SDL_Color NOIR = {0, 0, 0};

	texte = TTF_RenderUTF8_Blended(police, str, NOIR);
	if (!texte){
		fprintf (stderr, "Erreur a la creation du texte : %s\n", SDL_GetError ());
		exit (EXIT_FAILURE);
	}
	SDL_Texture * texte_tex = SDL_CreateTextureFromSurface(renderer, texte);
	if (!texte_tex){
		fprintf(stderr, "Erreur a la creation du rendu du texte : %s\n", SDL_GetError ());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(texte);
	txtDestRect.x = x;
  	txtDestRect.y = y;
	SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
	SDL_RenderCopy(renderer, texte_tex, NULL, &txtDestRect);
}

void SDL_ExitWithError(const char *message, SDL_Window *w, SDL_Renderer *r, SDL_Texture *t){
/**Fonction de gestion d erreur qui affiche l erreur SDL rencontree et libere la memoire allouee avant de quitter le programme**/
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
	if(t != NULL)
        SDL_DestroyTexture(t);
    if(r != NULL)
        SDL_DestroyRenderer(r);
    if(w != NULL)
        SDL_DestroyWindow(w);
    SDL_Quit();

    exit(EXIT_FAILURE);
}

int main(int argc, char** argv){
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) != 0 )
  		SDL_ExitWithError("Initialisation SDL", NULL, NULL, NULL);

	window = SDL_CreateWindow("Kaiser",10, 50, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
		SDL_ExitWithError("Erreur à la création de la fenetre\n", window, NULL, NULL);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		SDL_ExitWithError("Erreur à la création du renderer\n", window, renderer, NULL);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	if(!TTF_WasInit() && TTF_Init() == -1)
		SDL_ExitWithError("TTF_Init", NULL, NULL, NULL);

	TTF_Font *police = TTF_OpenFont("caviardreams.ttf", 40);

	if (!police)
		SDL_ExitWithError("Erreur du chargement de la police\n", window, renderer, NULL);

	SDL_bool launched = SDL_TRUE;
	SDL_Event event;

/*-----------------------------------------------------------------------------------*/
	char buffer[512];
	fd_set rdfs;

	struct sockaddr_in servaddr;
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock == -1) perror("Socket");

	bzero((void *) &servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(30000);
	servaddr.sin_addr.s_addr = inet_addr(SERVEURNAME);

	if (-1 == connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)))
		perror("Connect");


	memset(buffer, 0, sizeof(buffer));
	recv(sock,buffer,512,0);
	printf("[client] Server name is : '%s'\n", buffer);

	while (launched){
		FD_ZERO(&rdfs);
      	FD_SET(STDIN_FILENO, &rdfs);
      	FD_SET(sock, &rdfs);

	    if (select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
	      {
	         perror("select()");
	         exit(errno);
	      }

	    if (FD_ISSET(STDIN_FILENO, &rdfs)){
	    	char message[6];
	    	fgets(message, 6, stdin);
	    	message[5] = '\0';
	    	send(sock, message, 6, 0);
	    }
	    else if (FD_ISSET(sock, &rdfs)){
			memset(buffer, 0, sizeof(buffer));
			recv(sock,buffer,512,0);
			printf("[client] response from server : '%s'\n", buffer);

			SDL_RenderClear(renderer);
			creerTexte(renderer, police, buffer, 10, 10);
			SDL_RenderPresent(renderer);
	    }

		SDL_WaitEvent(&event);

		switch (event.type){
			case SDL_QUIT: launched = SDL_FALSE; break;
			default: break;
		}
	}

	close(sock);
	free(police);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}

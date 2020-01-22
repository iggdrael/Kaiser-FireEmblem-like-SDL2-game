#include <SDL.h>
#define SHAPE_SIZE 60

int main(int argc, char *argv[])
{
  SDL_Window* Main_Window;
  SDL_Renderer* Main_Renderer;
  SDL_Surface* Loading_Surf;
  SDL_Texture* Background_Tx;
  SDL_Texture* BlueShapes;

  SDL_Rect SrcR;
  SDL_Rect DestR;

  SrcR.x = 0;
  SrcR.y = 0;
  SrcR.w = SHAPE_SIZE;
  SrcR.h = SHAPE_SIZE;

  DestR.x = 640 / 2 - SHAPE_SIZE / 2;
  DestR.y = 580 / 2 - SHAPE_SIZE / 2;
  DestR.w = SHAPE_SIZE;
  DestR.h = SHAPE_SIZE;

  Main_Window = SDL_CreateWindow("SDL_RenderCopy Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 580, 0);
  Main_Renderer = SDL_CreateRenderer(Main_Window, -1, SDL_RENDERER_ACCELERATED);

  Loading_Surf = SDL_LoadBMP("src/img/CAV_N.bmp");
  Background_Tx = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
  SDL_FreeSurface(Loading_Surf);

  Loading_Surf = SDL_LoadBMP("src/img/CAV_B.bmp");
  BlueShapes = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
  SDL_FreeSurface(Loading_Surf);


  SDL_RenderCopy(Main_Renderer, Background_Tx, NULL, NULL);
  SDL_RenderPresent(Main_Renderer);


/*  int i;
  int n;
  for (i = 0; i < 2; ++i) {
    for(n = 0; n < 4; ++n) {
      SrcR.x = SHAPE_SIZE * (n % 2);
      if (n > 1) {
        SrcR.y = SHAPE_SIZE;
      } else {
        SrcR.y = 0;
      }
      SDL_RenderCopy(Main_Renderer, Background_Tx, NULL, NULL);
      SDL_RenderCopy(Main_Renderer, BlueShapes, &SrcR, &DestR);
      SDL_RenderPresent(Main_Renderer);
      SDL_Delay(500);
    }
  }
*/
  SDL_Delay(3000);
  SDL_DestroyTexture(BlueShapes);
  SDL_DestroyTexture(Background_Tx);
  SDL_DestroyRenderer(Main_Renderer);
  SDL_DestroyWindow(Main_Window);
  SDL_Quit();


  return 0;
}
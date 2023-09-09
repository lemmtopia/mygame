#include <SDL2/SDL.h>
#include <stdio.h>

#include "./defs.h"
#include "./gameplay.c"

SDL_Window* window;
SDL_Renderer* renderer;
int running;

SDL_Color black, white, cyan, magenta;
Actor player;

int initialize_sdl() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("%s", SDL_GetError());
    return FALSE;
  }

  window = SDL_CreateWindow("Game",
			    SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED,
			    960, 540,
			    0);

  if (window == NULL) {
    printf("%s", SDL_GetError());
    return FALSE;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (renderer == NULL) {
    printf("%s", SDL_GetError());
    return FALSE;
  }

  black.r = 0;
  black.g = 0;
  black.b = 0;
  black.a = 255;

  cyan.r = 85;
  cyan.g = 255;
  cyan.b = 255;
  cyan.a = 255;

  magenta.r = 255;
  magenta.g = 85;
  magenta.b = 255;
  magenta.a = 255;

  white.r = 255;
  white.g = 255;
  white.b = 255;
  white.a = 255;

  
  printf("SDL has been initialized.\n");
  return TRUE;
}

void process_input() {
  SDL_Event ev;
  if (SDL_PollEvent(&ev)) {
    if (ev.type == SDL_QUIT) running = FALSE;
  }
}

void render() {
  SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
  SDL_RenderClear(renderer);
  
  SDL_SetRenderDrawColor(renderer, cyan.r, cyan.g, cyan.b, cyan.a);
  SDL_RenderDrawLine(renderer, 100, 100, 300, 300);

  SDL_SetRenderDrawColor(renderer, player.color.r, player.color.g, player.color.b, player.color.a);
  SDL_RenderFillRect(renderer, &player.rect);
  
  SDL_SetRenderDrawColor(renderer, magenta.r, magenta.g, magenta.b, magenta.a);
  SDL_RenderDrawLine(renderer, 200, 400, 300, 300);
  
  SDL_RenderPresent(renderer);
}

int main(void) {
  running = initialize_sdl();
  make_actor(&player, 30, 30, 40, 40, magenta);

  while (running == TRUE) {
    process_input();
    render();

    SDL_Delay(1000 / 60);
  }
  
  SDL_Quit();
  return 0;
}

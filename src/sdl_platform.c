#include <SDL2/SDL.h>
#include <stdio.h>

#include "./defs.h"
#include "./gameplay.c"

SDL_Window* window;
SDL_Renderer* renderer;
int running;

SDL_Color black, white, cyan, magenta;
Actor player;

Uint32 pixels[WIDTH * HEIGHT];
SDL_Texture *screen;

SDL_Rect dest = {0, 0, WIDTH * 3, HEIGHT * 3};

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

  screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB444, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
  printf("SDL has been initialized.\n");
  return TRUE;
}

void process_input() {
  SDL_Event ev;
  if (SDL_PollEvent(&ev)) {
    if (ev.type == SDL_QUIT) running = FALSE;
    if (ev.type == SDL_KEYDOWN) {
      switch (ev.key.keysym.sym) {
      case SDLK_ESCAPE:
	running = FALSE;
	break;
      }
    }
  }
}

void render() {
  /*
  SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
  SDL_RenderClear(renderer);
  
  SDL_SetRenderDrawColor(renderer, cyan.r, cyan.g, cyan.b, cyan.a);
  SDL_RenderDrawLine(renderer, 100, 100, 300, 300);

  SDL_SetRenderDrawColor(renderer, player.color.r, player.color.g, player.color.b, player.color.a);
  SDL_RenderFillRect(renderer, &player.rect);
  
  SDL_SetRenderDrawColor(renderer, magenta.r, magenta.g, magenta.b, magenta.a);
  SDL_RenderDrawLine(renderer, 200, 400, 300, 300);
  */
  
  for (int i = 0; i < WIDTH * HEIGHT; i++) {
    pixels[i]++;
  }

  /*
  player.rect.x += 1;
  player.rect.y += 1;
  */
  
  SDL_UpdateTexture(screen, NULL, &pixels, 4);
  SDL_RenderCopy(renderer, screen, NULL, &dest);
  
  SDL_RenderPresent(renderer);
}

int main(void) {
  running = initialize_sdl();
  make_actor(&player, 30, 30, 40, 40, magenta);

  for (int i = 0; i < WIDTH * HEIGHT; i++) {
    pixels[i] = i;
  }

  while (running == TRUE) {
    process_input();
    render();

    SDL_Delay(1000 / 60);
  }
  
  SDL_Quit();
  return 0;
}

#include <SDL2/SDL.h>

typedef struct {
  SDL_Rect rect;
  SDL_Color color;
} Actor;

void make_actor(Actor* actor, int x, int y, int w, int h, SDL_Color c) {
  actor->rect.x = x;
  actor->rect.y = y;
  actor->rect.w = w;
  actor->rect.h = h;

  actor->color = c;
}

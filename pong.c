#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

SDL_Renderer *renderer;

int Player_1_Y = 280, Player_2_Y = 280;
short int y_status = 1, x_status = 1;
int BallX = 640, BallY = 360;
int Points_Player_1 =0, Points_Player_2 = 0;

SDL_Rect Ball, Player_1, Player_2;
SDL_Rect Wall1 = {0, 0, 1280, 5};
SDL_Rect Wall2 = {0, 715, 1280, 5};

void windowLoop(SDL_Window *window);
void gameUI();
static int regionMatch(const SDL_Rect *rect, int x, int y);
void ballCollision(int x, int y, const SDL_Rect *player1, const SDL_Rect *player2, const SDL_Rect *wall1, const SDL_Rect *wall2);

int main(){
  SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  windowLoop(window);
}

void windowLoop(SDL_Window *window){
  SDL_Init(SDL_INIT_VIDEO);
  int done = 0;
  SDL_Event event;
  while(!done){
    while(SDL_PollEvent(&event)){
      switch(event.type){
        case SDL_WINDOWEVENT_CLOSE:
          {
            if (window){
              SDL_DestroyWindow(window);
              window = NULL;
            }
          }
          break;
        case SDL_QUIT:
          done = 1;
          break;
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym){
            case SDLK_ESCAPE:
              done = 1;
              break;
            case SDLK_w:
              Player_1_Y -= 65;
              break;
            case SDLK_s:
              Player_1_Y += 65;
              break;
            case SDLK_UP:
              Player_2_Y -= 65;
              break;
            case SDLK_DOWN:
              Player_2_Y += 65;
              break;  
          }
      }
    }
    gameUI();
  }
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
}

void gameUI(){  
  SDL_Rect Player_1 = {20, Player_1_Y, 10, 120};
  SDL_Rect Player_2 = {1260, Player_2_Y, 10, 120};
  ballCollision(BallX, BallY, &Player_1, &Player_2, &Wall1, &Wall2);
  BallX += 7 * (x_status);
  BallY += 10 * (y_status);
  SDL_SetRenderDrawColor(renderer, 1, 1, 1, 1);
  SDL_RenderFillRect(renderer, &Wall2);
  SDL_RenderFillRect(renderer, &Wall1);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_Rect center = {640, 0, 2, 720};
  SDL_Rect Ball = {BallX, BallY, 15, 15};
  SDL_RenderFillRect(renderer, &Ball);
  SDL_RenderFillRect(renderer, &center);
  SDL_RenderFillRect(renderer, &Player_1);
  SDL_RenderFillRect(renderer, &Player_2);
  SDL_RenderPresent(renderer);
}

static int regionMatch(const SDL_Rect *rect, int x, int y){
  return ((x >= rect->x) && (x<= rect->x + rect->w) && (y >= rect->y) && (y <= rect->y + rect->h));
}

void ballCollision(int x, int y, const SDL_Rect *player1, const SDL_Rect *player2, const SDL_Rect *wall1, const SDL_Rect *wall2){
  if ((regionMatch(wall1, x, y)) || (regionMatch(wall2, x, y))){
    y_status = y_status * -1;
  }
  if ((regionMatch(player1, x, y) || regionMatch(player2, x, y))){
    x_status = x_status * -1;
  }
  if (x > 1280){
    BallX = 100;
    Points_Player_1++;
  }
  if (x < 0){
    BallX = 1200;
    Points_Player_2++;
  }
}

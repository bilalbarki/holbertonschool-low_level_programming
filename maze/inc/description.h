#include <SDL2/SDL.h>
#include "player.h"
float horizontal_distance(float angle, float rel_angle, int);
float vertical_distance(float angle, float rel_angle, int);
float convertAngleZeroToThreeSixty(float raw_angle);
int detectCollision(int direction);
int readfromfile(char *path);
SDL_Texture *loadTexture(char *path, SDL_Renderer *renderTarget);
void setValuesForPlayer();
float convertAngleZeroToThreeSixty(float raw_angle);
void quit_game(SDL_Window* window, SDL_Renderer* gRenderer, SDL_Texture *wallTexture, SDL_Texture *ceilingTexture, SDL_Texture *wTexture);
int gameloop( SDL_Window* window, SDL_Renderer* gRenderer, SDL_Texture *wallTexture, SDL_Texture *floorTexture, SDL_Texture *ceilingTexture, SDL_Texture *wTexture );
void movePlayer(int inc, int direction);
void movePlayerSideways(int inc, int direction);
void viewingangleinc(int inc);
int load_all_textures(SDL_Renderer* gRenderer, SDL_Texture **wallTexture, SDL_Texture **floorTexture,  __attribute__ ((unused)) SDL_Texture **ceilingTexture, SDL_Texture **wTexture);
void rain(SDL_Renderer* gRenderer, int index);
void weatexture(SDL_Renderer* gRenderer, SDL_Texture *wTexture);
void draw_floor(SDL_Renderer* gRenderer, int projected_height_half, float angle, float rel_angle, SDL_Texture *floorTexture, SDL_Rect fcSrcRect, SDL_Rect fcDestRect);
void draw_wall( SDL_Renderer* gRenderer, int i, float angle, float rel_angle, int *projected_height, SDL_Rect wallSrcRect, SDL_Rect wallDestRect, SDL_Texture *wallTexture);
void showMap(SDL_Renderer* gRenderer);

#define move_step_pos 10
#define move_step_neg -10
#define True 1
#define False 0
#define block_size 64
#define VIEW_DISTANCE 400

struct wallHits {
    float distance;
    int *x;
    int *y;
    int texture_offset;
};

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern maze_player player;
extern float piRadRatio;
extern struct wallHits wallHit;
extern int mapWidth;
extern int mapHeight;
extern int worldMap[100][100];



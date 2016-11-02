#include <SDL2/SDL.h>
#include "../inc/extern.h"
#include "../inc/definitions.h"
#include "../inc/prototypes.h"

#define SCALE 2
/**
 * Draws a mini-map
 * @gRenderer: the main renderer for drawing
 */
void draw_map(SDL_Renderer* gRenderer)
{
    int i, j, p;
    struct screen_coords 
    {
        int x;
        int y;
    } screen_coord1, screen_coord2;
    screen_coord1.x = 0;
    screen_coord1.y = 0;
    screen_coord2.x = 0;
    screen_coord2.y = SCALE;
    for (i=0; i<worldMap.height; i++)
    {
        screen_coord1.x = 0;
        screen_coord2.x = 0;
        for (j=0; j<worldMap.width; j++)
        {
            if (worldMap.map[i][j] > 0)
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
            else
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

            for (p=0; p<SCALE; p++)
            {
                SDL_RenderDrawLine( gRenderer, screen_coord1.x, screen_coord1.y, screen_coord2.x, screen_coord2.y );
                screen_coord1.x++;
                screen_coord2.x++;
            }
        }
        screen_coord1.y+=SCALE;
        screen_coord2.y+=SCALE;
    }
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_Rect position;
    position.x = player.x*SCALE/BLOCK_SIZE;
    position.y = player.y*SCALE/BLOCK_SIZE;
    position.w = SCALE;
    position.h = SCALE;
    SDL_RenderFillRect(gRenderer, &position);

    SDL_SetRenderDrawColor(gRenderer, 155, 155, 255, 255);
    for (i=0; i<SCREEN_WIDTH; i++)
    {
        SDL_RenderDrawLine( gRenderer, player.x*SCALE/BLOCK_SIZE, player.y*SCALE/BLOCK_SIZE, wallHit.x[i]*SCALE/BLOCK_SIZE, wallHit.y[i]*SCALE/BLOCK_SIZE );
    }
}

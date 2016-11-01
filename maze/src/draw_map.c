#include <SDL2/SDL.h>
#include "../inc/extern.h"
#include "../inc/definitions.h"
#include "../inc/prototypes.h"

/**
 * Draws a mini-map
 * @gRenderer: the main renderer for drawing
 */
void draw_map(SDL_Renderer* gRenderer)
{
    int i, j, p;
    struct screen_coords {
        int x;
        int y;
    } screen_coord1, screen_coord2;
        screen_coord1.x = 0;
        screen_coord1.y = 0;
        screen_coord2.x = 0;
        screen_coord2.y = 2;
        for (i=0; i<mapHeight; i++)
        {
            screen_coord1.x = 0;
            screen_coord2.x = 0;
            for (j=0; j<mapWidth; j++)
            {
                if (worldMap[i][j] == 1)
                    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
                else
                    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

                for (p=0; p<2; p++)
                {
                    SDL_RenderDrawLine( gRenderer, screen_coord1.x, screen_coord1.y, screen_coord2.x, screen_coord2.y );
                    screen_coord1.x++;
                    screen_coord2.x++;
                }
            }
                    screen_coord1.y+=2;
                    screen_coord2.y+=2;
        }
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_Rect position;
        position.x = player.x*2/BLOCK_SIZE;
        position.y = player.y*2/BLOCK_SIZE;
        position.w = 2;
        position.h = 2;
        SDL_RenderFillRect(gRenderer, &position);

        SDL_SetRenderDrawColor(gRenderer, 155, 155, 255, 100);
        for (i=0; i<SCREEN_WIDTH; i++)
        {
            SDL_RenderDrawLine( gRenderer, player.x*2/BLOCK_SIZE, player.y*2/BLOCK_SIZE, wallHit.x[i]*2.0/BLOCK_SIZE, wallHit.y[i]*2.0/BLOCK_SIZE );
        }
}

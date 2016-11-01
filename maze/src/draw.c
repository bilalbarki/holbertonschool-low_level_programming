#include <SDL2/SDL.h>
#include "../inc/description.h"
#include "../inc/definitions.h"
#include "../inc/prototypes.h"

/**
 * Simulates rain
 * @gRenderer: the main renderer for drawing
 * @index: This is the current column index of the screen we are working on, it is same as the iterator for the main game loop, see game.c
 */
void draw_rain(SDL_Renderer* gRenderer, int index) {
    SDL_Rect rain_rect;
    rain_rect.w = rand()%5;
    rain_rect.h = 15-rand()%10;
    rain_rect.y = rand()%SCREEN_HEIGHT;
    rain_rect.x = index;
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, rand()%50 );
    SDL_RenderFillRect(gRenderer, &rain_rect);
}

/**
 * Draws first person
 * @gRenderer: the main renderer for drawing
 * @wTexture: first person texture
 */
void draw_first_person(SDL_Renderer* gRenderer, SDL_Texture *wTexture) {
    SDL_Rect wsrc, wdest;
    wsrc.w = 421;
    wsrc.h = 352;
    wsrc.y = 0;
    wsrc.x = 0;

    wdest.w = 180;
    wdest.h = 160;
    wdest.y = SCREEN_HEIGHT - 160;
    wdest.x = SCREEN_WIDTH>>1;

    SDL_RenderCopy(gRenderer, wTexture,&wsrc, &wdest);
}

/**
 * Draws floor
 * @gRenderer: the main renderer for drawing
 * @projected_height_half: half the projected height
 * @angle: the angle of the current ray that has been casted
 * @rel_angle: angle of the ray relative to the viewing angle, [range: FOV/2 to -FOV/2], used for removing fish eye effect
 * @floorTexture: SDL floor texture
 * @fcSrcRect: Source SDL_Rect for floor texture
 * @fcDestRect: Destination SDL_Rect for floor texture
 */
void draw_floor(SDL_Renderer* gRenderer, int projected_height_half, float angle, float rel_angle, SDL_Texture *floorTexture, SDL_Rect fcSrcRect, SDL_Rect fcDestRect)
{
    int y;
    float floordistance;
    for (y=SCREEN_HEIGHT/2+projected_height_half; y<SCREEN_HEIGHT; y++)
    {
        floordistance = BLOCK_SIZE*( (SCREEN_HEIGHT) / (2.0 * y - SCREEN_HEIGHT) );

        if (floordistance < VIEW_DISTANCE)
        {
            SDL_SetTextureAlphaMod( floorTexture, 255 - ( (floordistance)/VIEW_DISTANCE * 255 ) );
            //cosecant for removing fish-eye effect on floor
            floordistance *= 1.0 / ( cos(piRadRatio*rel_angle) );
            fcSrcRect.x = (int) ( player.x + floordistance*cos(piRadRatio*angle) ) % 64;
            fcSrcRect.y = (int) ( player.y - floordistance*sin(piRadRatio*angle) ) % 64;
            fcDestRect.y = y;
            SDL_RenderCopy(gRenderer, floorTexture,&fcSrcRect, &fcDestRect);

        }
    }
}

/**
 * Draws wall
 * @gRenderer: the main renderer for drawing
 * @index: This is the current column index of the screen we are working on, it is same as the iterator for the main game loop, see game.c
 * @angle: the angle of the current ray that has been casted
 * @rel_angle: angle of the ray relative to the viewing angle, [range: FOV/2 to -FOV/2], used for removing fish eye effect
 * @projected_height: the projected height
 * @wallSrcRect: Source SDL_Rect for wall texture
 * @wallDestRect: Destination SDL_Rect for wall texture
 * @floorTexture: SDL wall texture
 */
void draw_wall( SDL_Renderer* gRenderer, int index, float angle, float rel_angle, int *projected_height, SDL_Rect wallSrcRect, SDL_Rect wallDestRect, SDL_Texture *wallTexture)
{
    wallHit.distance = horizontal_distance(angle, rel_angle, index);
    wallSrcRect.x = wallHit.texture_offset;

    *projected_height = ceil( (BLOCK_SIZE)/(wallHit.distance) * player.distanceFromProjectionPlane);
    wallDestRect.h = *projected_height;
    wallDestRect.x = index;
    wallDestRect.y = SCREEN_HEIGHT/2-*projected_height/2; //SCREEN_HEIGHT/2-projected_height/2
    if (wallHit.distance < VIEW_DISTANCE)
    {
        SDL_SetTextureAlphaMod( wallTexture, 255-( (wallHit.distance)/VIEW_DISTANCE * 255 ) );
        SDL_RenderCopy(gRenderer, wallTexture,&wallSrcRect, &wallDestRect);
    }
}
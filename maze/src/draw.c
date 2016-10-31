#include <SDL2/SDL.h>
#include "../inc/description.h"

void rain(SDL_Renderer* gRenderer, int index) {
    SDL_Rect rain_rect;
    rain_rect.w = rand()%5;
    rain_rect.h = 15-rand()%10;
    rain_rect.y = rand()%SCREEN_HEIGHT;
    rain_rect.x = index;
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, rand()%50 );
    SDL_RenderFillRect(gRenderer, &rain_rect);
}

void weatexture(SDL_Renderer* gRenderer, SDL_Texture *wTexture) {
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

void draw_floor(SDL_Renderer* gRenderer, int projected_height_half, float angle, float rel_angle, SDL_Texture *floorTexture, SDL_Rect fcSrcRect, SDL_Rect fcDestRect)
{
    int y;
    float floordistance;
    for (y=SCREEN_HEIGHT/2+projected_height_half; y<SCREEN_HEIGHT; y++)
    {
        floordistance = block_size*( (SCREEN_HEIGHT) / (2.0 * y - SCREEN_HEIGHT) );

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

void draw_wall( SDL_Renderer* gRenderer, int i, float angle, float rel_angle, int *projected_height, SDL_Rect wallSrcRect, SDL_Rect wallDestRect, SDL_Texture *wallTexture)
{
    wallHit.distance = horizontal_distance(angle, rel_angle, i);
    wallSrcRect.x = wallHit.texture_offset;

    *projected_height = ceil( (block_size)/(wallHit.distance) * player.distanceFromProjectionPlane);
    wallDestRect.h = *projected_height;
    wallDestRect.x = i;
    wallDestRect.y = SCREEN_HEIGHT/2-*projected_height/2; //SCREEN_HEIGHT/2-projected_height/2
    if (wallHit.distance < VIEW_DISTANCE)
    {
        SDL_SetTextureAlphaMod( wallTexture, 255-( (wallHit.distance)/VIEW_DISTANCE * 255 ) );
        SDL_RenderCopy(gRenderer, wallTexture,&wallSrcRect, &wallDestRect);
    }
}
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture *loadTexture(char *path, SDL_Renderer *renderTarget) {
    SDL_Texture *texture = NULL;
    //SDL_Surface *surface = SDL_LoadBMP(path);
    SDL_Surface *surface = IMG_Load(path);
    if (surface == NULL)
        printf("Error surface, %s\n", SDL_GetError());
    else {
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        if (texture == NULL)
            printf("error texture");
    }
    SDL_FreeSurface(surface);
    return texture;
}

int load_all_textures(SDL_Renderer* gRenderer, SDL_Texture **wallTexture, SDL_Texture **floorTexture,  __attribute__ ((unused)) SDL_Texture **ceilingTexture, SDL_Texture **wTexture) {
    *wallTexture = loadTexture("textures/marble.bmp", gRenderer);
    if (*wallTexture == NULL) {
        printf("Wall texture loading error");
        return 1;
    }
    SDL_SetTextureBlendMode( *wallTexture, SDL_BLENDMODE_BLEND );

    *floorTexture = loadTexture("textures/1212.bmp", gRenderer);
    if (*floorTexture == NULL) {
        printf("Floor texture loading error");
        return 1;
    }
    SDL_SetTextureBlendMode( *floorTexture, SDL_BLENDMODE_BLEND );

    *ceilingTexture = loadTexture("textures/clouds.bmp", gRenderer);
    if (*ceilingTexture == NULL) {
        printf("Floor texture loading error");
        return 1;
    }
    SDL_SetTextureBlendMode( *ceilingTexture, SDL_BLENDMODE_BLEND );

    *wTexture = loadTexture("textures/wtexture.png", gRenderer);
    if (*floorTexture == NULL) {
        printf("W texture loading error");
        return 1;
    }

    return 0;
}
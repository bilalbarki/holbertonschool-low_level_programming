#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL_image.h>
#include "../inc/extern.h"
#include "../inc/camera.h"
#include "../inc/prototypes.h"
#include "../inc/definitions.h"

/**
 * main function
 * @argc: number of input arguments
 * @**args: 2d array to input arguments
 * RETURNS: returns 0 if all goes well, 1 if there is an error in some texture loading
 */
int main( __attribute__ ((unused)) int argc, __attribute__ ((unused)) char* args[] )
{
    SDL_Window* window = NULL;
    SDL_Texture *wallTexture= NULL;
    SDL_Texture *floorTexture= NULL;
    SDL_Texture *ceilingTexture= NULL;
    SDL_Texture *wTexture= NULL;
    int imgFlags = IMG_INIT_PNG;
    initialize_world_map("maps/map.txt");
    SDL_Renderer* gRenderer = NULL;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }
    
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }
    
    window = SDL_CreateWindow( "Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        SDL_Renderer* gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
        if( gRenderer == NULL )
        {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            return 1;
        }
        else 
        {
            SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
            wallHit.x = malloc(sizeof(int)*SCREEN_WIDTH);
            wallHit.y = malloc(sizeof(int)*SCREEN_WIDTH);
            setValuesForPlayer();
            gameloop(window, gRenderer, wallTexture, floorTexture, ceilingTexture, wTexture);
        }
    }
    quit_game(window, gRenderer, wallTexture, ceilingTexture, wTexture);
    return 0;
}




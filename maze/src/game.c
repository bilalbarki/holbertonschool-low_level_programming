#include <SDL2/SDL.h>
#include "../inc/extern.h"
#include "../inc/definitions.h"
#include "../inc/prototypes.h"

/**
 * Called upon exiting the game
 * @window: SDL window
 * @gRenderer: SDL renderer
 * @wallTexture: SDL texture used for walls
 * @ceilingTexture: SDL texture used for ceilings
 * @wTexture: SDL texture for first person
 */
void quit_game(SDL_Window* window, SDL_Renderer* gRenderer, SDL_Texture *wallTexture,SDL_Texture *ceilingTexture, SDL_Texture *wTexture)
{
    int i;
    /* free 2d worldMap.map */
    for (i=0 ; worldMap.map[i] ; i++)
    {
        free(worldMap.map[i]);
    }
    free(worldMap.map[i]);
    free(worldMap.map);
    
    /*free wall hit coordinates*/
    free(wallHit.x);
    free(wallHit.y);
    
    /*free all textures*/
    SDL_DestroyTexture( wTexture );
    SDL_DestroyTexture( ceilingTexture );
    SDL_DestroyTexture( wallTexture );
    
    /*free renderer*/
    SDL_DestroyRenderer( gRenderer );
    
    /*free window*/
    SDL_DestroyWindow( window );
    
    SDL_Quit();
}

/**
 * Sets initial values for player/camera
 */
void setValuesForPlayer() {
    player.FOV = 60; /*player field of view, 60 is looks good on a computer screen with experimentations*/
    player.height = 0;
    player.x = 190; /*x-coordinate for player in the map*/
    player.y = 568; /*y-coordinate for the player in the map*/
    player.viewing_angle =90; /*initial viewing angle for the player*/
    player.distanceFromProjectionPlane = (SCREEN_WIDTH>>1)/tan(M_PI/180*(player.FOV>>1)); /*this is the distance of the player from the project plane, used to calculate projection distance*/
    player.AngleBetweenSubsequentRays = (float)player.FOV / SCREEN_WIDTH; /*angle between each horizontal pixel for the ray that will be cast from the player*/
}

/**
 * Keeps angle between 0-359
 * @raw_angle: raw angle that will be converted to 0-359 range
 */
float convertAngleZeroToThreeSixty(float raw_angle)
{
    if (raw_angle < 0) 
    {
        return (360 + raw_angle);
    }
    else if (raw_angle >= 360) 
    {
        return (raw_angle - 360);
    }
    else 
    {
        return raw_angle;
    }
}

/**
 * This contains the main game loop
 * @window: SDL window - should already be initialized
 * @gRenderer: SDL renderer - should already be initialized
 * @wallTexture: SDL texture used for walls, should be NULL
 * @ceilingTexture: SDL texture used for ceilings, should be NULL
 * @wTexture: SDL texture for first person, should be NULL
 */
int gameloop( SDL_Window* window, SDL_Renderer* gRenderer, SDL_Texture *wallTexture, SDL_Texture *floorTexture,  SDL_Texture *ceilingTexture, SDL_Texture *wTexture )
{
    int i, projected_height, projected_height_half, SCREEN_HEIGHT_HALF, showmap = TRUE, quit = TRUE;
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    float angle, rel_angle, raw_angle;
    SDL_Event e;
    SDL_Rect wallSrcRect, wallDestRect, fcSrcRect, fcDestRect, ceilingSRC, ceilingDST;

    SCREEN_HEIGHT_HALF = SCREEN_HEIGHT/2;
    
    wallSrcRect.h = BLOCK_SIZE; wallSrcRect.w = 1; wallSrcRect.y = 0; 
    wallDestRect.w = 1;
    fcSrcRect.h = 1; fcSrcRect.w = 1; 
    fcDestRect.h = 1; fcDestRect.w = 1;
    
    ceilingSRC.w = 1; ceilingSRC.y = 0;
    ceilingDST.w = 1; ceilingDST.y = 0;

    /*loads all textures, i.e. wall, floor, ceiling, first person*/
    load_all_textures(gRenderer, &wallTexture, &floorTexture, &ceilingTexture, &wTexture);

    /*main game loop*/
    while (quit) {
        /*handles all events like quit, and keypresses*/
        handle_events(keystates, e, &quit, &showmap);
        /*resetting color to black is important because crossing the view distance nothing will be drawn, hence it should be pitch black*/
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
        /*clears renderer for redrawing*/
        SDL_RenderClear( gRenderer );
        /*
        raw_angle is the angle that is before it is converted to 0-359 range, 
        e.g. if the viewing angle is 359, going FOV/2 above will result in angle that is e.g. 389
        */
        raw_angle = player.viewing_angle + (player.FOV>>1); /*we have to go through viewing_angle - FOV/2 to viewing_angle + FOV/2, and number of iterations between this range is the number of horizontal pixels, i.e. SCREEN_WIDTH*/
        /*for every column*/
        for (i=0; i<SCREEN_WIDTH; i++, raw_angle -= player.AngleBetweenSubsequentRays)
        {
            rel_angle = player.viewing_angle - raw_angle; /*rel_angle is the angle that is relative to the viewing angle, such that the viewing angle is assumed to be zero, this will be used for removing fish-eye effect*/
            /* convert angle to range 0 to 360 */
            angle = convertAngleZeroToThreeSixty(raw_angle); /*converts the angle to 0-359 range*/
            draw_wall(gRenderer, i, angle, rel_angle, &projected_height, wallSrcRect, wallDestRect, wallTexture);
            
            projected_height_half = projected_height>>1;
            fcDestRect.x = i;
            draw_floor(gRenderer, projected_height_half, angle, rel_angle, floorTexture, fcSrcRect, fcDestRect);

            /*draw ceiling, this is just a static image, if you want to have a full texturized ceiling, you can mirror image the floor coordinates*/
            ceilingSRC.h = SCREEN_HEIGHT_HALF-projected_height_half;
            ceilingSRC.x = i;
            ceilingDST.h = SCREEN_HEIGHT_HALF-projected_height_half;
            ceilingDST.x = i;
            SDL_SetTextureAlphaMod( ceilingTexture,150 );
            SDL_RenderCopy(gRenderer, ceilingTexture,&ceilingSRC, &ceilingSRC);
            /*ceiling draw end*/

            draw_rain(gRenderer, i);
    }
    draw_first_person(gRenderer, wTexture);

    if (showmap) /*disables or enables minimap depending if showmap is TRUE or FALSE*/
    {
        draw_map(gRenderer);
    }

    SDL_RenderPresent( gRenderer );

    }

    return 0;
}





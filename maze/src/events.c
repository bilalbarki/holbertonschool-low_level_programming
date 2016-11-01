#include <SDL2/SDL.h>
#include "../inc/description.h"
#include "../inc/definitions.h"
#include "../inc/prototypes.h"

/**
 * Handles the quit event and all keyboard events
 * @keystates: An array of all keyboard key states, obtained through SDL_GetKeyboardState function
 * @*quit: Address to the quit variable that is used to detect quit state for the game
 * @*showmap: Address to the show map variable, for enabling/disabling minimap
 */
void handle_events(const Uint8 *keystates, SDL_Event e, int *quit, int *showmap)
{
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
            *quit = FALSE;
        }

        //User presses a key
        else if( e.type == SDL_KEYDOWN )
        {
            switch( e.key.keysym.sym )
            {
                case SDLK_m:
                *showmap = !*showmap;
                break;
            }

        }

    }

    if( keystates[ SDL_SCANCODE_UP ] )
        move_player_front_backwards(MOVE_STEP_POS, 0);
    if( keystates[ SDL_SCANCODE_DOWN ] )
        move_player_front_backwards(MOVE_STEP_NEG, 180);
    if( keystates[ SDL_SCANCODE_RIGHT ] )
        move_player_sideways(MOVE_STEP_NEG,-90 );
    if( keystates[ SDL_SCANCODE_LEFT ] )
        move_player_sideways(MOVE_STEP_POS, 90);
    if( keystates[ SDL_SCANCODE_Z ] )
        increment_viewing_angle(MOVE_STEP_POS);
    if( keystates[  SDL_SCANCODE_X ] )
        increment_viewing_angle(MOVE_STEP_NEG);
}
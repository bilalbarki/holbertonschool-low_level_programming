#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include "description.h"

int gameloop(SDL_Window* window, SDL_Renderer* gRenderer);
void quit_game(SDL_Window* window, SDL_Renderer* gRenderer);
void line_color_altitude(int z1, int z2, SDL_Renderer* gRenderer);

int x_cart_to_iso(int cartX, int cartY, float incline);
int y_cart_to_iso(int cartX, int cartY, int z, float incline);
int rotate_xy(int deg, int *isoX, int *isoY, int centerX, int centerY);
int xy_cart_to_iso(int cartX, int cartY);


/*const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int altitude[8][8] = {
        {5, 10, 40, 60, 20, -20, -80, -120},
        {40, 20, 30, 30, -10, -40, -90, -110},
        {20, 30, 10, 06, -6, -20, -26, -90},
        {0, -6, 10, 10, -6, -20, -20, -40},
        {-20, -20, -18, -14, -40, -20, -20, -30},
        {-10, -10, -10, -10, -8, -20, -20, -30},
        {20, 10, 10, 10, 10, 04, 10, -10},
        {30, 24, 24, 22, 20, 18, 14, 16}
};
int rotate = 0;
int tile_dimension = 30;
float incline = 0.7;
int tiles =7;
*/
int main( __attribute__ ((unused)) int argc, __attribute__ ((unused)) char* args[] )
{

	SDL_Window* window = NULL;

	/*SDL_Surface* screenSurface = NULL;*/

    SDL_Renderer* gRenderer = NULL;


	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		gameloop(window, gRenderer);
	}

    quit_game(window, gRenderer);
	return 0;
}

void quit_game(SDL_Window* window, SDL_Renderer* gRenderer)
{
    SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
}

int gameloop(SDL_Window* window, SDL_Renderer* gRenderer)
{
    window = SDL_CreateWindow( "Bilal", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        int quit, x_offset, y_offset, clickX, clickY, clicked, selected, region[2];
        SDL_Event e;
        quit = 1;

        x_offset = 0;
        y_offset = 0;

        clickX = -1;
        clickY = -1;
        clicked = 0;
        selected = 0;
        region[1] = 0;
        region[0] = 0;


        gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC );
        if( gRenderer == NULL )
        {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            return 1;
        }

        while (quit) {

            while( SDL_PollEvent( &e ) != 0 )
            {

                if( e.type == SDL_QUIT )
                {
                    quit = 0;
                }

                else if( e.type == SDL_KEYDOWN )
                {

                    switch( e.key.keysym.sym )
                    {
                        case SDLK_ESCAPE:
                            selected = 0;
                            break;


                        case SDLK_UP:
                            if (selected)
                            {
                                altitude[region[0]][region[1]]++;
                                break;
                            }
                                else
                                    y_offset+=2;
                                break;

                        case SDLK_DOWN:
                            if (selected)
                            {
                                altitude[region[0]][region[1]]--;
                                break;
                            }
                            else
                                y_offset-=2;
                            break;

                        case SDLK_LEFT:
                            x_offset+=2;
                            break;

                        case SDLK_RIGHT:
                            x_offset-=2;
                            break;

                        case SDLK_z:
                            tile_dimension++;
                            break;

                        case SDLK_x:
                            tile_dimension--;
                            break;

                        case SDLK_r:
                            rotate--;
                            break;

                        case SDLK_t:
                            rotate++;
                            break;

                        case SDLK_i:
                            incline+=0.01;
                            break;

                        case SDLK_o:
                            incline-=0.01;
                            break;

                        }
                    }

                    if( e.type == SDL_MOUSEBUTTONUP )
                    {

                        clickX = e.button.x;
                        clickY = e.button.y;
                        clicked = 1;
                    }
				}

                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
                SDL_RenderClear( gRenderer );

				SDL_SetRenderDrawColor( gRenderer, 0x98, 0xF6, 0xFF, 0x22);

				int hyp = (tile_dimension*(tiles) )/2;
				int x_center = (SCREEN_WIDTH / 2) ;
				int y_center = (SCREEN_HEIGHT / 2) - hyp;

                for (int j = 0, m=0; j <= tiles*tile_dimension; j += tile_dimension, m++ )
                {
                    for( int i = 0, k=0; i < (tiles)*tile_dimension; i += tile_dimension, k++)
                    {
                        int x1, y1, x2, y2, z1, z2, iso_x1, iso_x2, iso_y1, iso_y2;
                        x1 = i;
                        y1 = j;
                        y2 = y1;
                        x2 = x1 + tile_dimension;
                        z1 = altitude[k][m];
                        z2 = altitude[k+1][m];


                        rotate_xy(rotate, &x1, &y1, hyp, hyp);
                        rotate_xy(rotate, &x2, &y2, hyp, hyp);

                        line_color_altitude(z1, z2, gRenderer);


                        iso_x1 = x_cart_to_iso(x1, y1, incline)+x_center + x_offset;
                        iso_y1 = y_cart_to_iso(x1, y1,z1, incline )+y_center+y_offset;

                        iso_x2 = x_cart_to_iso(x2, y2, incline)+x_center+ x_offset;
                        iso_y2 = y_cart_to_iso(x2, y2, z2, incline)+y_center+y_offset;

                        SDL_RenderDrawLine( gRenderer, iso_x1 , iso_y1, iso_x2 , iso_y2 );

                        if (abs(clickX - (iso_x1)) < 10 && abs(clickY - (iso_y1)) < 10 && clicked)
                        {
                            region[0] = k;
                            region[1] = m;
                            printf("selected: [%d, %d]\n", k, m);
                            clicked = 0;
                            selected = 1;
                        }

                        else if (abs(clickX - abs(iso_x2)) < 10 && abs(clickY - (iso_y2)) < 10 && clicked)
                        {
                            region[0] = k+1;
                            region[1] = m;
                            printf("selected: [%d, %d]\n", k, m);
                            clicked = 0;
                            selected = 1;
                        }


                        x1 = j;
                        y1 = i;
                        x2 = x1;
                        y2 = y1+tile_dimension;

                        z1 = altitude[j/tile_dimension][i/tile_dimension];
                        z2 = altitude[j/tile_dimension][i/tile_dimension+1];

                        rotate_xy(rotate, &x1, &y1, hyp, hyp);
                        rotate_xy(rotate, &x2, &y2, hyp, hyp);

                        iso_x1 = x_cart_to_iso(x1, y1, incline)+x_center + x_offset;
                        iso_y1 = y_cart_to_iso(x1, y1, z1, incline)+y_center+y_offset;

                        iso_x2 = x_cart_to_iso(x2, y2, incline)+x_center+ x_offset;
                        iso_y2 = y_cart_to_iso(x2, y2, z2, incline)+y_center+y_offset;

                        SDL_RenderDrawLine( gRenderer, iso_x1 , iso_y1, iso_x2 , iso_y2 );

                        /*SDL_RenderDrawLine( gRenderer, (x1 + x_offset)*0.5, (y1+y_offset)*0.5, (x2+ x_offset)*0.5, (y2+y_offset)*0.5 );
                        SDL_RenderDrawLine( gRenderer, (x1 + x_offset)*0.5, (y1+y_offset)*(0.5), (x2+ x_offset)*(0.5), (y2+y_offset)*0.5 );*/

                    }

                }
                SDL_RenderPresent( gRenderer );

            }
        }

        return 0;
}

void line_color_altitude(int z1, int z2, SDL_Renderer* gRenderer)
{
    if (z1 >= 0 && z2 <= 20)
    {
        SDL_SetRenderDrawColor( gRenderer, 0x15, 0x6D, 0x71, 0x22);
    }
    else if (z1 > 20 && z2 <= 40)
    {
        SDL_SetRenderDrawColor( gRenderer, 0x2E, 0x4B, 0x9B, 0x22);
    }

    else if (z1 > 40 && z2 <= 80)
    {
        SDL_SetRenderDrawColor( gRenderer, 0xC1, 0xc6, 0x18, 0x22);
    }

    else if (z1 > 80)
    {
        SDL_SetRenderDrawColor( gRenderer, 0x8D, 0x97, 0xd4, 0x22);
    }

    if (z1 < 0 && z2 >= -20)
    {
        SDL_SetRenderDrawColor( gRenderer, 0x11, 0x5D, 0x1F, 0x22);
    }
    else if (z1 < -20 && z2 >= -40)
    {
        SDL_SetRenderDrawColor( gRenderer, 0x7A, 0x1C, 0x93, 0x22);
    }
    else if (z1 < -40 && z2 >= -80)
    {
        SDL_SetRenderDrawColor( gRenderer, 0x93, 0x1C, 0x1F, 0x22);
    }

    else if (z1 < -80)
    {
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }

}

int x_cart_to_iso(int cartX, int cartY, float incline)
{
    return (incline*cartX - incline*cartY);
}

int y_cart_to_iso(int cartX, int cartY, int z, float incline)
{
    return ((1-incline)*cartX + (1-incline)*cartY) - z;
}

int rotate_xy(int deg, int *isoX, int *isoY, int centerX, int centerY)
{
    int temp_x;
    /*int a = (M_PI / 180) * deg;*/
    *isoY = *isoY-centerY;
    *isoX = *isoX-centerX;
    temp_x = *isoX;
    /*isoX = cos(deg*0.1)*(*isoX - centerX) - sin(deg*0.1)*(*isoY - centerY) + centerX;
    isoX = sin(deg*0.1)*(temp_x - centerX) + cos(deg*0.1)*(*isoY - centerY) + centerY;*/
    *isoX = *isoX * cos(deg*0.1) - *isoY * sin(deg*0.1);
    *isoY = temp_x * sin(deg*0.1) + *isoY * cos(deg*0.1);
    *isoY += centerY;
    *isoX = *isoX+centerX;
    return 0;
}

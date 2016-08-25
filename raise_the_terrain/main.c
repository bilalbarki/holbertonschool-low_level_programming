#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include "description.h"

int gameloop(SDL_Window* window, SDL_Renderer* gRenderer, TTF_Font *font, SDL_Texture *texture);
void quit_game(SDL_Window* window, SDL_Renderer* gRenderer, TTF_Font *font, SDL_Texture *texture);
void line_color_altitude(int z1, int z2, SDL_Renderer* gRenderer);

int x_cart_to_iso(int cartX, int cartY, float incline);
int y_cart_to_iso(int cartX, int cartY, int z, float incline);
int rotate_xy(int deg, int *isoX, int *isoY, int centerX, int centerY);
int xy_cart_to_iso(int cartX, int cartY);

int main( __attribute__ ((unused)) int argc, __attribute__ ((unused)) char* args[] )
{


        SDL_Window* window = NULL;
	TTF_Font *font = NULL;
	SDL_Texture *texture= NULL;
	SDL_Renderer* gRenderer = NULL;


        if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        {
                printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
                return 1;
        }
        if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		return 1;
	}

	gameloop(window, gRenderer, font, texture);

	quit_game(window, gRenderer, font, texture);
        return 0;
}

void quit_game(SDL_Window* window, SDL_Renderer* gRenderer, TTF_Font *font, SDL_Texture *texture)
{
	if (texture != NULL)
	{
		SDL_DestroyTexture( texture );
	}
	TTF_CloseFont(font);
	SDL_DestroyRenderer( gRenderer );
        SDL_DestroyWindow( window );
        SDL_Quit();
}

int gameloop(SDL_Window* window, SDL_Renderer* gRenderer, TTF_Font *font, SDL_Texture *texture)
{
	window = SDL_CreateWindow( "Bilal", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( window == NULL )
	{
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		int quit, x_offset, y_offset, clickX, clickY, clicked, selected, region[2], MouseOver, toolX = 0, toolY = 0, tooloffset = 0, timer, normalize = 0;
		int hyp, x_center, y_center, j, i, m, k;
		char coordtext[30];
		SDL_Event e;

		texture = NULL;
		MouseOver = 1;
		font = TTF_OpenFont("open-sans.ttf", 16);

		if (font == NULL)
		{
			printf( "Error loading font: %s\n", TTF_GetError());
			return 1;
		}

		quit = 1;

		x_offset = 0;
		y_offset = 0;

		clickX = -1;
		clickY = -1;
		clicked = 0;
		selected = 0;
		region[1] = 0;
		region[0] = 0;


		gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
		if( gRenderer == NULL )
		{
			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			return 1;
		}

        if (tile_dimension*tiles >= SCREEN_HEIGHT)
        {
            int temp = tile_dimension;
            printf("4444 %d\n", tile_dimension*tiles);
            tile_dimension = SCREEN_HEIGHT/tiles;

            if (tile_dimension >=16 && tile_dimension <= 40) tile_dimension-=2;
           y_offset-=tile_dimension/tiles*(temp-tile_dimension);

        }


        else if (tile_dimension*tiles >= SCREEN_WIDTH)
        {
            int temp = tile_dimension;
            tile_dimension = SCREEN_WIDTH/tiles;
           y_offset-=tile_dimension/tiles*(temp-tile_dimension);

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
						  tooloffset++;
						  toolY--;
						  break;
					  }
					  else {
						  y_offset+=2;

						  break;
					  }

					case SDLK_DOWN:
					  if (selected)
					  {
						  altitude[region[0]][region[1]]--;
						  tooloffset--;
						  toolY++;
						  break;
					  }
					  else {
						  y_offset-=2;


						  break;
					  }

					case SDLK_LEFT:
					  x_offset+=2;
					  break;

					case SDLK_RIGHT:
					  x_offset-=2;
					  break;

					case SDLK_z:
					  tile_dimension++;
					  y_offset+=tile_dimension/tiles;
					  break;

					case SDLK_x:
					  tile_dimension--;
					  y_offset-=tile_dimension/tiles;
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

					case SDLK_RETURN:
					  selected = 0;
					  normalize = 1;
					  break;

                    case SDLK_b:
					  tiles++;

					  break;

                    case SDLK_n:
					  tiles--;
					  break;



					}
				}

				if( e.type == SDL_MOUSEBUTTONUP )
				{

					clickX = e.button.x;
					clickY = e.button.y;
					clicked = 1;
				}
				else if ( e. type == SDL_MOUSEMOTION)
				{
					clickX = e.button.x;
					clickY = e.button.y;
				}
			}

			if ((MouseOver == 0 && abs(clickX - toolX) > 7) || (abs(clickY - toolY) > 7)) {
                                if (!selected)
					MouseOver = 1;
                                SDL_DestroyTexture( texture );
                                texture = NULL;
                                tooloffset = 0;

                        }

			if (normalize == 1) {
				int run = 0;
				timer = SDL_GetTicks();
				if (timer % 40 == 0)
				{
					int i, j;
					float factor = 0.99;


					for (i=0; i<tiles+1; i++) {
						for (j=0; j<tiles+1; j++)
						{

							altitude[i][j]*=factor;
							if (altitude[i][j] != 0) {
								run = 1;
							}
						}

					}

					if (run == 0)
					{
						normalize = 0;

					}

				}

			}

			SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
			SDL_RenderClear( gRenderer );

			SDL_SetRenderDrawColor( gRenderer, 0x98, 0xF6, 0xFF, 0x22);

			hyp = ( (tile_dimension)*(tiles) )/2;
			x_center = (SCREEN_WIDTH / 2);
			y_center = (SCREEN_HEIGHT / 2) - (hyp)/2 - sqrt(tile_dimension*4)*4;


			for (j = 0, m=0; j <= tiles*tile_dimension; j += tile_dimension, m++ )
			{
				for( i = 0, k=0; i < (tiles)*tile_dimension; i += tile_dimension, k++)
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


					if (abs(clickX - iso_x1) < 7 && abs(clickY - iso_y1) < 7)
					{

						if (clicked)
						{
							region[0] = k;
							region[1] = m;
							printf("selected: [%d, %d]\n", k, m);
							clicked = 0;
							selected = 1;

							toolX = iso_x1;
							toolY = iso_y1;
						}
						else if (MouseOver)
						{


							MouseOver = 0;
							toolX = iso_x1;
							toolY = iso_y1;

						}


					}

					if (abs(clickX - abs(iso_x2)) < 7 && abs(clickY - (iso_y2)) < 7)
					{
						if (clicked)
						{
							region[0] = k+1;
							region[1] = m;
							printf("selected: [%d, %d]\n", k, m);
							clicked = 0;
							selected = 1;
							toolX = iso_x2;
							toolY = iso_y2;
						}
						else if (MouseOver)
						{


							MouseOver = 0;
							toolX = iso_x2;
							toolY = iso_y2;

						}
					}

					if (MouseOver == 0 && !normalize) {
						SDL_Color textColor;
						SDL_Color bg;
						SDL_Surface *textsurface;
						textColor.a = 0x00;
						textColor.b = 0x00;
						textColor.g = 0x00;
						textColor.r = 0x00;

						bg.a = 0xFF;
						bg.b = 0xFF;
						bg.g = 0xFF;
						bg.r = 0xFF;

						sprintf(coordtext, " ( %d, %d ) ", toolX, toolY);

						textsurface = TTF_RenderText_Shaded(font, coordtext, textColor, bg);
						if (textsurface != NULL)
						{
							if (texture != NULL) {
								SDL_DestroyTexture( texture );
							}

							texture = SDL_CreateTextureFromSurface(gRenderer, textsurface);
							SDL_FreeSurface(textsurface);
							if (texture != NULL)
							{

								SDL_Rect rect;
								rect.x = abs(toolX-20);
								rect.y = abs(toolY-25) - tooloffset;
								rect.w = 70;
								rect.h = 15;
								SDL_RenderCopy(gRenderer, texture, NULL, &rect);

							}

						}
					}

					x1 = j;
					y1 = i;
					x2 = x1;
					y2 = y1+tile_dimension;

					z1 = altitude[j/tile_dimension][i/tile_dimension];
					z2 = altitude[j/tile_dimension][i/tile_dimension+1];

					line_color_altitude(z1, z2, gRenderer);

					rotate_xy(rotate, &x1, &y1, hyp, hyp);
					rotate_xy(rotate, &x2, &y2, hyp, hyp);

					iso_x1 = x_cart_to_iso(x1, y1, incline)+x_center + x_offset;
					iso_y1 = y_cart_to_iso(x1, y1, z1, incline)+y_center+y_offset;

					iso_x2 = x_cart_to_iso(x2, y2, incline)+x_center+ x_offset;
					iso_y2 = y_cart_to_iso(x2, y2, z2, incline)+y_center+y_offset;

					SDL_RenderDrawLine( gRenderer, iso_x1 , iso_y1, iso_x2 , iso_y2 );

					/* SDL_RenderDrawLine( gRenderer, (x1 + x_offset), (y1+y_offset), (x2+ x_offset), (y2+y_offset) );
					SDL_RenderDrawLine( gRenderer, (x1 + x_offset), (y1+y_offset), (x2+ x_offset), (y2+y_offset) );*/

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

	else if (z1 < 0 && z2 >= -20)
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

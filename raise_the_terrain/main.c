#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include "coord.h"
#include "description.h"


int gameloop(SDL_Window* window, SDL_Renderer* gRenderer, TTF_Font *font, SDL_Texture *texture);
void quit_game(SDL_Window* window, SDL_Renderer* gRenderer, TTF_Font *font, SDL_Texture *texture);
void line_color_altitude(int z1, int z2, SDL_Renderer* gRenderer);

int x_cart_to_iso(int cartX, int cartY, float incline);
int y_cart_to_iso(int cartX, int cartY, int z, float incline);
int rotate_xy(int deg, int *isoX, int *isoY, int centerX, int centerY);
int xy_cart_to_iso(int cartX, int cartY);
int fill_color(SDL_Renderer* gRenderer);
int filledPolygonRGBA(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
int filledPolygonColor(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy, int n, Uint32 color);

coordinates coord[102][102];

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
                int quit, x_offset, y_offset, clickX, clickY, selected, region[2], MouseOver, toolX = 0, toolY = 0, timer, normalize = 0;
                int hyp, x_center, y_center, j, i, m, k, color_fill = 0, corners;
                int locked = 0, mousememX=0, mousememY=0;
                char coordtext[30];
                SDL_Event e;
                corners = tiles+1;
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
                                          MouseOver = 1;
                                          SDL_DestroyTexture( texture );
                                          texture = NULL;

                                          break;


                                        case SDLK_UP:
                                          if (selected)
                                          {
                                                  altitude[region[0]][region[1]]++;

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

                                        case SDLK_RETURN:
                                          selected = 0;
                                          normalize = 1;
                                          break;

					case SDLK_SPACE:
                                          selected = 0;
                                          normalize = 2;
                                          break;

					case SDLK_b:
                                          if (tiles <= 100)
						  tiles++;

                                          break;

					case SDLK_n:
                                          tiles--;
                                          break;

					case SDLK_c:
					  if (color_fill) color_fill = 0;
					  else {
						  color_fill = 1;

					  }


                                        }
                                }


                                if( e.button.button == SDL_BUTTON_LEFT )
                                {

					for (i=0;i<tiles+1;i+=1) {
						for (j=0; j<tiles+1; j+=1) {
							if (abs(clickX - coord[i][j].iso_x) < 7 && abs(clickY - coord[i][j].iso_y) < 7)
							{


								region[0] = i;
								region[1] = j;
								printf("selected: [%d, %d]\n", k, m);

								selected = 1;

								toolX = coord[i][j].iso_x;
								toolY = coord[i][j].iso_y;

							}
						}
					}

                                }

				else if( e.type == SDL_MOUSEMOTION )
				{
					clickX = e.button.x;
                                        clickY = e.button.y;
					if (e.motion.state & SDL_BUTTON_RMASK)
					{
						if (locked == 0)
						{
							mousememX = e.button.x;
							mousememY = e.button.y;
							locked = 1;
							selected = 0;
						}


						if (abs(mousememX-clickX) >1) {
							x_offset += (mousememX - clickX) ;
							mousememX = clickX;
						}
						if (abs(mousememY-clickY) >1) {
							y_offset += (mousememY - clickY) ;
							mousememY = clickY;
						}
					}
					for (i=0;i<tiles+1;i+=1) {
						for (j=0; j<tiles+1; j+=1) {
							if (abs(clickX - coord[i][j].iso_x) < 7 && abs(clickY - coord[i][j].iso_y) < 7)
							{


								if (MouseOver)
								{


									MouseOver = 0;
									toolX = coord[i][j].iso_x;
									toolY = coord[i][j].iso_y;

								}



							}
						}
					}

					if ((MouseOver == 0 && abs(clickX - toolX) > 7) || (abs(clickY - toolY) > 7)) {
						if (!selected)
							MouseOver = 1;
						SDL_DestroyTexture( texture );
						texture = NULL;


					}
				}
				else if (locked == 1) {
					locked =0;
				}

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

                        if (normalize == 2) {
                                timer = SDL_GetTicks();
                                if (timer % 100 == 0)
                                {
                                        int i, j;
                                        for (i=0; i<tiles+1; i++) {
                                                for (j=0; j<tiles+1; j++)
                                                {
                                                        altitude[i][j]+=rand() % 2;
                                                }

                                        }
                                        if (timer % rand()%5000 == 0)

                                        {
                                                normalize = 0;

                                        }

                                }

                        }

                        if (color_fill) {
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        }
                        else {

				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
			}
                        SDL_RenderClear( gRenderer );

                        SDL_SetRenderDrawColor( gRenderer, 0x98, 0xF6, 0xFF, 0x22);

                        hyp = ( (tile_dimension)*(tiles) )/2;
                        x_center = (SCREEN_WIDTH / 2);
                        y_center = (SCREEN_HEIGHT / 2) - (hyp)/2 - sqrt(tile_dimension*4)*2;

			/*produce coordinates*/
			for (i=0; i<corners; i++ )
                        {
                                int tempx, tempy;
                                for( j=0; j < corners; j++)
                                {
                                        coord[i][j].x = j*tile_dimension;
                                        coord[i][j].y = i*tile_dimension;

                                        tempx = coord[i][j].x;
                                        tempy = coord[i][j].y;

                                        rotate_xy(rotate, &tempx, &tempy, hyp, hyp);

                                        coord[i][j].iso_x = x_cart_to_iso(tempx, tempy, incline)+x_center + x_offset;
					coord[i][j].iso_y = y_cart_to_iso(tempx, tempy, altitude[i][j], incline )+y_center+y_offset;

                                }

                        }

			for (m = 0; m < tiles+1; m++ )
                        {
                                for( k=0; k < tiles; k++)
                                {

                                        line_color_altitude(altitude[m][k], altitude[m][k+1], gRenderer);
                                        SDL_RenderDrawLine( gRenderer, coord[m][k].iso_x, coord[m][k].iso_y, coord[m][k+1].iso_x, coord[m][k+1].iso_y);

                                }

                        }

			for (m = 0; m < tiles; m++ )
                        {
                                for( k=0; k < tiles+1; k++)
                                {
					line_color_altitude(altitude[m][k], altitude[m+1][k], gRenderer);
					SDL_RenderDrawLine( gRenderer, coord[m][k].iso_x, coord[m][k].iso_y, coord[m+1][k].iso_x, coord[m+1][k].iso_y);

                                }

                        }


                        if (color_fill) {
				fill_color(gRenderer);
			}
			else SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_NONE);
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
						rect.y = abs(toolY-25);
						rect.w = 70;
						rect.h = 15;
						SDL_RenderCopy(gRenderer, texture, NULL, &rect);

					}

				}
			}
                        SDL_RenderPresent( gRenderer );

                }
	}

        return 0;
}

int fill_color(SDL_Renderer* gRenderer)
{
	int i, j;
	for (i=0;i<tiles;i+=1) {
		Sint16 vx[4], vy[4];

		for (j=0; j<tiles; j+=1)
		{
                        vx[0] = coord[i][j].iso_x;
                        vx[1] = coord[i][j+1].iso_x;
                        vx[2] = coord[i+1][j+1].iso_x;
                        vx[3] = coord[i+1][j].iso_x;

                        vy[0] = coord[i][j].iso_y;
                        vy[1] = coord[i][j+1].iso_y;
                        vy[2] = coord[i+1][j+1].iso_y;;
                        vy[3] = coord[i+1][j].iso_y;;

                        if (i % 2 == 0 && j%2 == 0) {
				filledPolygonColor(gRenderer,vx,vy,4, 0x81BDF310);
                        }
                        else {
				filledPolygonColor(gRenderer,vx,vy,4, 0x2E4B9B00);
			}
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
        /*cartY -= centerY;
        cartY = cartX * sin(rotate*0.1) + cartY * cos(rotate*0.1);
        cartY += centerY;*/
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

int _gfxPrimitivesCompareInt(const void *a, const void *b)
{
	return (*(const int *) a) - (*(const int *) b);
}


int hline(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y)
{
	return SDL_RenderDrawLine(renderer, x1, y, x2, y);;
}


int filledPolygonRGBAMT(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int **polyInts, int *polyAllocated)
{
	int result;
	int i;
	int y, xa, xb;
	int miny, maxy;
	int x1, y1;
	int x2, y2;
	int ind1, ind2;
	int ints;
	int *gfxPrimitivesPolyInts = NULL;
	int *gfxPrimitivesPolyIntsNew = NULL;
	int gfxPrimitivesPolyAllocated = 0;

	/*
         * Vertex array NULL check
         */
	if (vx == NULL) {
		return (-1);
	}
	if (vy == NULL) {
		return (-1);
	}

	/*
         * Sanity check number of edges
         */
	if (n < 3) {
		return -1;
	}

	/*
         * Map polygon cache
         */
	if ((polyInts==NULL) || (polyAllocated==NULL)) {
		/* Use global cache */
		gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsGlobal;
		gfxPrimitivesPolyAllocated = gfxPrimitivesPolyAllocatedGlobal;
	} else {
		/* Use local cache */
		gfxPrimitivesPolyInts = *polyInts;
		gfxPrimitivesPolyAllocated = *polyAllocated;
	}

	/*
         * Allocate temp array, only grow array
         */
	if (!gfxPrimitivesPolyAllocated) {
		gfxPrimitivesPolyInts = (int *) malloc(sizeof(int) * n);
		gfxPrimitivesPolyAllocated = n;
	} else {
		if (gfxPrimitivesPolyAllocated < n) {
			gfxPrimitivesPolyIntsNew = (int *) realloc(gfxPrimitivesPolyInts, sizeof(int) * n);
			if (!gfxPrimitivesPolyIntsNew) {
				if (!gfxPrimitivesPolyInts) {
					free(gfxPrimitivesPolyInts);
					gfxPrimitivesPolyInts = NULL;
				}
				gfxPrimitivesPolyAllocated = 0;
			} else {
				gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsNew;
				gfxPrimitivesPolyAllocated = n;
			}
		}
	}

	/*
         * Check temp array
         */
	if (gfxPrimitivesPolyInts==NULL) {
		gfxPrimitivesPolyAllocated = 0;
	}

	/*
         * Update cache variables
         */
	if ((polyInts==NULL) || (polyAllocated==NULL)) {
		gfxPrimitivesPolyIntsGlobal =  gfxPrimitivesPolyInts;
		gfxPrimitivesPolyAllocatedGlobal = gfxPrimitivesPolyAllocated;
	} else {
		*polyInts = gfxPrimitivesPolyInts;
		*polyAllocated = gfxPrimitivesPolyAllocated;
	}

	/*
	 * Check temp array again
         */
	if (gfxPrimitivesPolyInts==NULL) {
		return(-1);
	}

	/*
         * Determine Y maxima
         */
	miny = vy[0];
	maxy = vy[0];
	for (i = 1; (i < n); i++) {
		if (vy[i] < miny) {
			miny = vy[i];
		} else if (vy[i] > maxy) {
			maxy = vy[i];
		}
	}

	/*
         * Draw, scanning y
         */
	result = 0;
	for (y = miny; (y <= maxy); y++) {
		ints = 0;
		for (i = 0; (i < n); i++) {
			if (!i) {
				ind1 = n - 1;
				ind2 = 0;
			} else {
				ind1 = i - 1;
				ind2 = i;
			}
			y1 = vy[ind1];
			y2 = vy[ind2];
			if (y1 < y2) {
				x1 = vx[ind1];
				x2 = vx[ind2];
			} else if (y1 > y2) {
				y2 = vy[ind1];
				y1 = vy[ind2];
				x2 = vx[ind1];
				x1 = vx[ind2];
			} else {
				continue;
			}
			if ( ((y >= y1) && (y < y2)) || ((y == maxy) && (y > y1) && (y <= y2)) ) {
				gfxPrimitivesPolyInts[ints++] = ((65536 * (y - y1)) / (y2 - y1)) * (x2 - x1) + (65536 * x1);
			}
		}

		qsort(gfxPrimitivesPolyInts, ints, sizeof(int), _gfxPrimitivesCompareInt);

		/*
                 * Set color
                 */
		result = 0;
		result |= SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
		result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

		for (i = 0; (i < ints); i += 2) {
			xa = gfxPrimitivesPolyInts[i] + 1;
			xa = (xa >> 16) + ((xa & 32768) >> 15);
			xb = gfxPrimitivesPolyInts[i+1] - 1;
			xb = (xb >> 16) + ((xb & 32768) >> 15);
			result |= hline(renderer, xa, xb, y);
		}
	}

	return (result);
}

int filledPolygonColor(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy, int n, Uint32 color)
{
	Uint8 *c = (Uint8 *)&color;
	return filledPolygonRGBAMT(renderer, vx, vy, n, c[0], c[1], c[2], c[3], NULL, NULL);
}

int filledPolygonRGBA(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	return filledPolygonRGBAMT(renderer, vx, vy, n, r, g, b, a, NULL, NULL);
}

#include <SDL.h>
#include <stdio.h>
#include <math.h>
#include "player.h"

float horizontal_distance(float angle, float rel_angle, int);
float vertical_distance(float angle, float rel_angle, int);
float convertAngleZeroToThreeSixty(float raw_angle);
int detectCollision(int direction);
int readfromfile(char *path);
SDL_Texture *loadTexture(char *path, SDL_Renderer *renderTarget);
void setValuesForPlayer();
float convertAngleZeroToThreeSixty(float raw_angle);
void quit_game(SDL_Window* window, SDL_Renderer* gRenderer, SDL_Texture *wallTexture);
int gameloop( SDL_Window* window, SDL_Renderer* gRenderer, SDL_Texture *wallTexture, SDL_Texture *floorTexture, SDL_Texture *ceilingTexture );
//Screen dimension constants
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 320;

maze_player player;
int block_size = 64;
float piRadRatio;

int rayX[320];
int rayY[320];

int texX[51200];
int texY[51200];

#define move_step 3
int mapWidth =24;
int mapHeight =24;
#define True 1
#define False 0

int worldMap[100][100];
int offset[2];
int xx[2];
int yy[2];


int readfromfile(char *path) {
    int  i=0, j=0;
    size_t count = 100;
    size_t width;
    char *line = malloc(100);

    FILE *file;  /* declare a FILE pointer  */
    file = fopen(path, "r");  /* open a text file for reading */

    while( (int) (width = getline(&line, &count, file))!=-1) {

        j=0;
        for (; width > 1; width--, j++){
            worldMap[i][j] = (int)line[j] -48;

        }
        mapWidth=j;
        i++;
    }

    mapHeight = i;

    free(line);
    fclose(file);
    return 0;

}


int main( __attribute__ ((unused)) int argc, __attribute__ ((unused)) char* args[] )
{
    SDL_Window* window = NULL;

    SDL_Texture *wallTexture= NULL;
    SDL_Texture *floorTexture= NULL;
    SDL_Texture *ceilingTexture= NULL;
    readfromfile("map.txt");
    SDL_Renderer* gRenderer = NULL;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %sn", SDL_GetError() );
        return 1;
    }
    setValuesForPlayer();
    gameloop(window, gRenderer, wallTexture, floorTexture, ceilingTexture);
    quit_game(window, gRenderer, wallTexture);
    return 0;
}

SDL_Texture *loadTexture(char *path, SDL_Renderer *renderTarget) {
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = SDL_LoadBMP(path);
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

void quit_game(SDL_Window* window, SDL_Renderer* gRenderer, SDL_Texture *wallTexture)
{

    SDL_DestroyTexture( wallTexture );
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
}

void setValuesForPlayer() {
    player.FOV = 60;
    player.height = 32;
    player.x = 118;
    player.y = 439;
    player.viewing_angle =90;
    player.distanceFromProjectionPlane = (SCREEN_WIDTH>>1)/tan(M_PI/180*(player.FOV>>1));
    player.AngleBetweenSubsequentRays = (float)player.FOV / SCREEN_WIDTH;
    piRadRatio =M_PI/180;
}

float convertAngleZeroToThreeSixty(float raw_angle) {
    if (raw_angle < 0) {
        return 360 + raw_angle;
    }
    else if (raw_angle >= 360) {
        return raw_angle - 360;
    }
    else {
        return raw_angle;
    }
}

void viewingangleinc(int inc) {
    int temp = player.viewing_angle;
    temp+=inc;
    player.viewing_angle = convertAngleZeroToThreeSixty(temp);
}

int detectCollision(int direction) {

    float raw_angle = player.viewing_angle + direction - 10;
    for (int i=0; i<20; i++, raw_angle ++) {
        float angle;
        float rel_angle = player.viewing_angle + direction - raw_angle;
        int dist_hor, dist_vert;

        // convert angle to range 0 to 360
        angle = convertAngleZeroToThreeSixty(raw_angle);

        dist_hor = horizontal_distance(angle, rel_angle, False);
        dist_vert = vertical_distance(angle, rel_angle, False);
        if (dist_hor <15 || dist_vert < 15) {
            return 1;
        }
    }
    return 0;
}

void movePlayer(int inc, int direction) {
        if (!detectCollision(direction)) {
            player.x += inc*cos(piRadRatio*player.viewing_angle);
            player.y -= inc*sin(piRadRatio*player.viewing_angle);
        }
}

void movePlayerSideways(int inc, int direction) {
    if (!detectCollision(direction)) {
        player.x += inc*cos( piRadRatio* (player.viewing_angle+ 90) );
        player.y -= inc*sin( piRadRatio* (player.viewing_angle+ 90) );
    }
}


int gameloop( SDL_Window* window, SDL_Renderer* gRenderer, SDL_Texture *wallTexture, SDL_Texture *floorTexture,  __attribute__ ((unused)) SDL_Texture *ceilingTexture )
{

    int showmap = True;
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    window = SDL_CreateWindow( "Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        int quit = True;
        SDL_Event e;

        int i, y, j, u, p;


        //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
        gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
        wallTexture = loadTexture("123.bmp", gRenderer);
        if (wallTexture == NULL) {
            printf("Wall texture loading error");
        }
        floorTexture = loadTexture("grass.bmp", gRenderer);
        if (floorTexture == NULL) {
            printf("Floor texture loading error");
        }
        if( gRenderer == NULL )
        {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            return 1;
        }

        while (quit) {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = False;
                }

                //User presses a key
                else if( e.type == SDL_KEYDOWN )
                {

                switch( e.key.keysym.sym )
                {
                    case SDLK_m:
                    showmap = !showmap;
                    break;
                }

            }
        }

        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
        SDL_RenderClear( gRenderer );

    if( keystates[ SDL_GetScancodeFromKey(SDLK_UP) ] )
    {
        movePlayer(move_step, 0);
        printf("Px: %f, Py: %f, VA: %d\n", player.x, player.y, player.viewing_angle);

    }
    if( keystates[ SDL_GetScancodeFromKey(SDLK_DOWN) ] )
    {
        movePlayer(move_step * (-1), 180);
    }

    if( keystates[ SDL_GetScancodeFromKey(SDLK_RIGHT) ] )
    {
             movePlayerSideways(move_step * (-1),-90 );
    }
    if( keystates[ SDL_GetScancodeFromKey(SDLK_LEFT) ] )
    {
        movePlayerSideways(move_step, 90);
    }

    if( keystates[ SDL_GetScancodeFromKey(SDLK_z) ] )
    {
        viewingangleinc(1);
    }

    if( keystates[  SDL_GetScancodeFromKey(SDLK_x) ] )
    {
        viewingangleinc(-1);
    }


    float raw_angle = player.viewing_angle + (player.FOV / 2);

for (i=0; i<SCREEN_WIDTH; i++, raw_angle -= player.AngleBetweenSubsequentRays) {
    float angle;
    float rel_angle;
    float dist_hor, dist_vert, projected_height, *distance;
    rel_angle = player.viewing_angle - raw_angle;

    // convert angle to range 0 to 360
    angle = convertAngleZeroToThreeSixty(raw_angle);


    dist_hor = horizontal_distance(angle, rel_angle, True);
    dist_vert = vertical_distance(angle, rel_angle, True);
    SDL_Rect srcRect;
    if (dist_vert<dist_hor) {
        distance = &dist_vert;
        //projected_height = ceil((float)(block_size)/(dist_vert) * player.distanceFromProjectionPlane);
        //SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_SetRenderDrawColor( gRenderer, 0.9*0x87, 0.9*0xCE, 0.9*0xEB, 00 );
        //printf("========\n");
        //intensity = 0.1/dist_hor * 7000000;

        srcRect.h = block_size;
        srcRect.w = 1;
        srcRect.x = offset[1];
        srcRect.y = 0;
        xx[0]=xx[1];
        yy[0]=yy[1];
        //printf("x: %d\n",offset[1]);
    }
    else {
        distance = &dist_hor;
       // projected_height = ceil((float)(block_size)/(dist_hor) * player.distanceFromProjectionPlane);
        SDL_SetRenderDrawColor( gRenderer, 0x87, 0xCE, 0xEB, 00 );

        srcRect.h = block_size;
        srcRect.w = 1;
        srcRect.x = offset[0];
        srcRect.y = 0;
        xx[1]=xx[0];
        yy[1]=yy[0];
       // printf("x: %d\n",offset[0]);
       // intensity = 0.1/dist_hor * 7000000;
    }
    projected_height = ceil((float)(block_size)/(*distance) * player.distanceFromProjectionPlane);

    SDL_Rect dRect;
    dRect.h = projected_height;
    dRect.w = 1;
    dRect.x = i;
    dRect.y = SCREEN_HEIGHT/2-projected_height/2;
    SDL_RenderCopy(gRenderer, wallTexture,&srcRect, &dRect);



   // SDL_UpdateWindowSurface(window);


    for (y=SCREEN_HEIGHT/2+projected_height/2+1; y<SCREEN_HEIGHT; y++) {
        SDL_SetRenderDrawColor(gRenderer, 34, 139, 34, 0);
        SDL_RenderDrawPoint(gRenderer, i, y);
        SDL_SetRenderDrawColor(gRenderer, 0x87, 0xCE, 0xCB, 0);
        SDL_RenderDrawPoint(gRenderer, i, SCREEN_HEIGHT- y);
    }



    rayX[i]=xx[0];
    rayY[i]=yy[0];

    }

    if (showmap) {
        int xxxx1=0;
        int yyyy1=0;
        int xxxx2 = 0;
        int yyyy2 = 2;
            for (i=0; i<mapHeight; i++) {
                xxxx1=0;
                xxxx2 = 0;
                for (j=0; j<mapWidth; j++) {
                    if (worldMap[i][j] == 1) SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);
                    else SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 0);

                    for (p=0; p<2; p++) {
                        SDL_RenderDrawLine( gRenderer, xxxx1, yyyy1, xxxx2, yyyy2 );
                        xxxx1++;
                        xxxx2++;
                    }
                }
                 yyyy1+=2;
                yyyy2+=2;
            }
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
            SDL_Rect position;
            position.x = player.x*2/block_size;
            position.y = player.y*2/block_size;
            position.w = 2;
            position.h = 2;
            SDL_RenderFillRect(gRenderer, &position);

            SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
            for (u=0; u<SCREEN_WIDTH; u++) {
                SDL_RenderDrawLine( gRenderer, player.x*2/block_size, player.y*2/block_size, rayX[u]*2.0/block_size, rayY[u]*2.0/block_size );

            }
        }

        SDL_RenderPresent( gRenderer );

        }
    }
    return 0;
}

float horizontal_distance(float angle, float rel_angle, int ShouldICalculateOffset) {
    // for horizontal intersection, calculating nearest intersection
    float Xa, Ax, distance, Ay;
    int Ya, grid_Ay, grid_Ax;

    // Ya has to be negative if the ray is facing up
    if (angle>0.0 && angle<180.0) {
        Ya = block_size*(-1);
        Ay = ((int)((float)player.y/block_size)) * block_size -0.0001;
        Xa = block_size/tan(piRadRatio*angle);

    }
    // else if facing down it has to be positive
    else {
        Ya = block_size;
        Ay = ((int)((float)player.y/block_size)) * block_size + block_size;
        Xa = block_size/tan(piRadRatio*angle) * (-1);
    }


    Ax = player.x + (player.y - Ay)/tan(piRadRatio*angle);

    while(1) {
         //if we run out of the map
        if (Ax <0 || Ay < 0 || Ax > block_size*mapWidth - 1 || Ay > block_size*mapHeight -1) {
            //set distance to max
            distance = block_size*mapWidth;
            break;
        }

        grid_Ay = Ay/block_size;
        grid_Ax = Ax/block_size;
//                if (angle > 117 && angle < 118)
//                printf("----====-------y: %d, gx: %d\n", grid_Ay, grid_Ax);

        //check if the first intersection hits a wall
        if (worldMap[grid_Ay][grid_Ax] > 0) {
           // dist_hor = sqrt( pow((player.y - Ay), 2) + pow((player.x - Ax), 2) );
            distance = sqrt( (player.y - Ay)*(player.y - Ay) + (player.x - Ax)*(player.x - Ax) );
            //dist_hor = sqrt(dist_hor);
            distance = distance * cos(piRadRatio*rel_angle);
            break;
        }

        Ax = Ax + Xa;
        Ay = Ay + Ya;

    }
    if (ShouldICalculateOffset){
        offset[0]=(int)Ax%block_size;
        xx[0]=Ax;
        yy[0]=Ay;
    }
 //  printf("dist_hor:%.1f, angle: %f, Ax: %.1f, Ay: %d, Ya: %d, Xa: %f\n", distance, angle, Ax, Ay, Ya, Xa);
    //printf("--hor--> gridAx: %d, gridAy: %d\n", grid_Ax, grid_Ay);
    return distance;
    // end of horizontal intersection check
}

float vertical_distance(float angle, float rel_angle,  int ShouldICalculateOffset) {
    // for horizontal intersection, calculating nearest intersection
    float Ya, Ay, distance, Ax;
    int Xa, grid_Ay, grid_Ax;
    // Ya has to be negative if the ray is facing right
    if ( angle<90.0 || angle>270.0 ) {
        Xa = block_size;
        Ax = ((int)((float)player.x/block_size)) * block_size + block_size;
        Ya = block_size*tan(piRadRatio*angle) * (-1);
    }
    // else if facing down it has to be positive
    else {
        Xa = block_size*(-1);
        Ax = ((int)((float)player.x/block_size)) * block_size - 0.0001;
        Ya = block_size*tan(piRadRatio*angle);
        // printf(" bbllll: %d\n\n\n", Ax);
    }


    Ay = player.y + (player.x - Ax)*tan(piRadRatio*angle);



  while(1) {
         //if we run out of the map
        if (Ax <0 || Ay < 0 || Ax > block_size*mapWidth - 1 || Ay > block_size*mapHeight -1) {
            //set distance to max
            distance = block_size*mapHeight;
            break;
        }

        grid_Ay = Ay/block_size;
        grid_Ax = Ax/block_size;
//                if (angle > 117 && angle < 118)
//                printf("--------------y: %d, gx: %d\n", grid_Ay, grid_Ax);

        //check if the first intersection hits a wall
        if (worldMap[grid_Ay][grid_Ax] > 0) {
           // dist_hor = sqrt( pow((player.y - Ay), 2) + pow((player.x - Ax), 2) );
            distance = sqrt( (player.y - Ay)*(player.y - Ay) + (player.x - Ax)*(player.x - Ax) );
            //dist_hor = sqrt(dist_hor);
            distance = distance * cos(piRadRatio*rel_angle);
            break;
        }

        Ax = Ax + Xa;
        Ay = Ay + Ya;

    }
    if (ShouldICalculateOffset){
        offset[1]=(int)Ay%block_size;
        xx[1]=Ax;
        yy[1]=Ay;
    }
//  printf("*dist_ver%.1f, angle: %f, Ax: %d, Ay: %f, Ya: %.1f, Xa: %d\n\n", distance, angle, Ax, Ay, Ya, Xa);
    //printf("ver--> gridAx: %d, gridAy: %d\n", grid_Ax, grid_Ay);
    return distance;
    // end of horizontal intersection check
}



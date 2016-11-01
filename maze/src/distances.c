#include <stdio.h>
#include <math.h>
#include "../inc/extern.h"
#include "../inc/definitions.h"
#include "../inc/prototypes.h"

/**
 * Measures both horizontal and vertical distances and returns the lesser one
 * @angle: the angle of the ray being casted
 * @rel_angle: angle of the ray relative to the viewing angle, [range: FOV/2 to -FOV/2], used for removing fish eye effect
 * @index: index for storing wallHits x and y coordinates, as well as texture offset, this index is the same as the main game loop iterator, see game.c
 */
float horizontal_distance(float angle, float rel_angle, int index) 
{
    // for horizontal intersection, calculating nearest intersection
    float Xa, Ax, distance, Ay;
    float vert_distance;
    int Ya, grid_Ay, grid_Ax;

    // Ya has to be negative if the ray is facing up
    if (angle>0.0 && angle<180.0) 
    {
        Ya = BLOCK_SIZE*(-1);
        Ay = ((int)((float)player.y/BLOCK_SIZE)) * BLOCK_SIZE -0.0001;
        Xa = BLOCK_SIZE/tan(piRadRatio*angle);

    }
    // else if facing down it has to be positive
    else 
    {
        Ya = BLOCK_SIZE;
        Ay = ((int)(player.y/BLOCK_SIZE)) * BLOCK_SIZE + BLOCK_SIZE;
        Xa = BLOCK_SIZE/tan(piRadRatio*angle) * (-1);
    }

    Ax = player.x + (player.y - Ay)/tan(piRadRatio*angle);

    while(1) 
    {
         //if we run out of the map
        if (Ax <0 || Ay < 0 || Ax > BLOCK_SIZE*mapWidth - 1 || Ay > BLOCK_SIZE*mapHeight -1) 
        {
            //set distance to max
            distance = BLOCK_SIZE*mapWidth;
            break;
        }

        grid_Ay = Ay/BLOCK_SIZE;
        grid_Ax = Ax/BLOCK_SIZE;

        if (worldMap[grid_Ay][grid_Ax] > 0) 
        {
            distance = sqrt( (player.y - Ay)*(player.y - Ay) + (player.x - Ax)*(player.x - Ax) );
            distance *= cos(piRadRatio*rel_angle);
            break;
        }

        Ax += Xa;
        Ay += Ya;

    }

    vert_distance = vertical_distance(angle,rel_angle, index);
    if (distance<vert_distance) 
    {
        if (index>=0)
        {
            wallHit.texture_offset=(int)Ax%BLOCK_SIZE;
            wallHit.x[index]=Ax;
            wallHit.y[index]=Ay;
        }
        return distance;
    }

    else
        return vert_distance;
}

/**
 * Measures both vertical distances and returns the lesser one
 * @angle: the angle of the ray being casted
 * @rel_angle: angle of the ray relative to the viewing angle, [range: FOV/2 to -FOV/2]
 * @index: index for storing wallHits x and y coordinates, as well as texture offset, this index is the same as the main game loop iterator, see game.c
 */
float vertical_distance(float angle, float rel_angle,  int index) 
{
    // for horizontal intersection, calculating nearest intersection
    float Ya, Ay, distance, Ax;
    int Xa, grid_Ay, grid_Ax;
    // Ya has to be negative if the ray is facing right
    if ( angle<90.0 || angle>270.0 ) 
    {
        Xa = BLOCK_SIZE;
        Ax = ((int)(player.x/BLOCK_SIZE)) * BLOCK_SIZE + BLOCK_SIZE;
        Ya = BLOCK_SIZE*tan(piRadRatio*angle) * (-1);
    }
    // else if facing down it has to be positive
    else 
    {
        Xa = BLOCK_SIZE*(-1);
        Ax = ((int)(player.x/BLOCK_SIZE)) * BLOCK_SIZE - 0.0001;
        Ya = BLOCK_SIZE*tan(piRadRatio*angle);
    }

    Ay = player.y + (player.x - Ax)*tan(piRadRatio*angle);

    while(1) {
         //if we run out of the map
        if (Ax <0 || Ay < 0 || Ax > BLOCK_SIZE*mapWidth - 1 || Ay > BLOCK_SIZE*mapHeight -1) 
        {
            //set distance to max
            distance = BLOCK_SIZE*mapHeight;
            break;
        }

        grid_Ay = Ay/BLOCK_SIZE;
        grid_Ax = Ax/BLOCK_SIZE;

        if (worldMap[grid_Ay][grid_Ax] > 0) 
        {
            distance = sqrt( (player.y - Ay)*(player.y - Ay) + (player.x - Ax)*(player.x - Ax) );
            distance *= cos(piRadRatio*rel_angle);
            break;
        }

        Ax += Xa;
        Ay += Ya;

    }
    if (index>=0)
    {
        wallHit.texture_offset=(int)Ay%BLOCK_SIZE;
        wallHit.x[index]=Ax;
        wallHit.y[index]=Ay;
    }
    return distance;
}


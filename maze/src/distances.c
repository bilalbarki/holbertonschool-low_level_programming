#include <stdio.h>
#include <math.h>
#include "../inc/extern.h"
#include "../inc/definitions.h"
float vertical_distance(float angle, float rel_angle,  int index);

/**
 * Measures both horizontal and vertical distances and returns the lesser one
 * @angle: the angle of the ray being casted
 * @rel_angle: angle of the ray relative to the viewing angle, [range: FOV/2 to -FOV/2], used for removing fish eye effect
 * @index: index for storing wallHits x and y coordinates, as well as texture offset, this index is the same as the main game loop iterator, see game.c
 */
float ray_distance(float angle, float rel_angle, int index) 
{
    /*calculating horizontal distance*/
    float Xa, Ax, distance, Ay;
    float vert_distance;
    int Ya, grid_Ay, grid_Ax;
    
    /*for horizontal intersection, calculating nearest intersection*/
    if (angle>0.0 && angle<180.0) 
    {
        Ya = BLOCK_SIZE*(-1); /*Ya has to be negative if the ray is facing up*/
        Ay = ((int)((float)player.y/BLOCK_SIZE)) * BLOCK_SIZE -0.0001;
        Xa = BLOCK_SIZE/tan(piRadRatio*angle); /*Xa has to be positive if the ray is facing up*/

    }
    else 
    {
        Ya = BLOCK_SIZE; /*Ya has to be positive if the ray is facing down*/
        Ay = ((int)(player.y/BLOCK_SIZE)) * BLOCK_SIZE + BLOCK_SIZE;
        Xa = BLOCK_SIZE/tan(piRadRatio*angle) * (-1); /*Xa has to be negative if the ray is facing down*/
    }

    Ax = player.x + (player.y - Ay)/tan(piRadRatio*angle);

    while(1) 
    {
        /*if we run out of the map*/
        if (Ax <0 || Ay < 0 || Ax > BLOCK_SIZE*worldMap.width - 1 || Ay > BLOCK_SIZE*worldMap.height -1) 
        {
            /*set distance to max and break*/
            distance = BLOCK_SIZE*worldMap.width;
            break;
        }

        /*calculate respective grid coordinates*/
        grid_Ay = Ay/BLOCK_SIZE;
        grid_Ax = Ax/BLOCK_SIZE;

        /*check if on those grid coordinates, there is a wall*/
        if (worldMap.map[grid_Ay][grid_Ax] > 0) 
        {
            /*calculate ray distance*/
            distance = sqrt( (player.y - Ay)*(player.y - Ay) + (player.x - Ax)*(player.x - Ax) );
            distance *= cos(piRadRatio*rel_angle); /*remove fish-eye effect*/
            break;
        }

        /*move to next block if no wall on these grid coordinates*/
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
    float Ya, Ay, distance, Ax;
    int Xa, grid_Ay, grid_Ax;

    /*for horizontal intersection, calculating nearest intersection*/
    if ( angle<90.0 || angle>270.0 ) 
    {
        Xa = BLOCK_SIZE;
        Ax = ((int)(player.x/BLOCK_SIZE)) * BLOCK_SIZE + BLOCK_SIZE;
        Ya = BLOCK_SIZE*tan(piRadRatio*angle) * (-1); /*Ya has to be negative if the ray is facing right*/
    }
    
    else 
    {
        Xa = BLOCK_SIZE*(-1);   /*Xa has to be negative if the ray is facing left*/
        Ax = ((int)(player.x/BLOCK_SIZE)) * BLOCK_SIZE - 0.0001;
        Ya = BLOCK_SIZE*tan(piRadRatio*angle); /*Ya has to be positive if the ray is facing left*/
    }

    Ay = player.y + (player.x - Ax)*tan(piRadRatio*angle);

    while(1) {
        /*if we run out of the map*/
        if (Ax <0 || Ay < 0 || Ax > BLOCK_SIZE*worldMap.width - 1 || Ay > BLOCK_SIZE*worldMap.height -1) 
        {
            /*set distance to max*/
            distance = BLOCK_SIZE*worldMap.height;
            break;
        }

        /*calculating respective grid coordinates*/
        grid_Ay = Ay/BLOCK_SIZE;
        grid_Ax = Ax/BLOCK_SIZE;

        /*if there is a wall at that grid coorinate*/
        if (worldMap.map[grid_Ay][grid_Ax] > 0) 
        {
            /*calculate ray distance*/
            distance = sqrt( (player.y - Ay)*(player.y - Ay) + (player.x - Ax)*(player.x - Ax) );
            distance *= cos(piRadRatio*rel_angle); /*remove fish-eye effect*/
            break;
        }

        /*move to next block*/
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


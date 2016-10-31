#include <stdio.h>
#include <math.h>
#include "../inc/description.h"

float horizontal_distance(float angle, float rel_angle, int index) 
{
    // for horizontal intersection, calculating nearest intersection
    float Xa, Ax, distance, Ay;
    float vert_distance;
    int Ya, grid_Ay, grid_Ax;

    // Ya has to be negative if the ray is facing up
    if (angle>0.0 && angle<180.0) 
    {
        Ya = block_size*(-1);
        Ay = ((int)((float)player.y/block_size)) * block_size -0.0001;
        Xa = block_size/tan(piRadRatio*angle);

    }
    // else if facing down it has to be positive
    else 
    {
        Ya = block_size;
        Ay = ((int)(player.y/block_size)) * block_size + block_size;
        Xa = block_size/tan(piRadRatio*angle) * (-1);
    }

    Ax = player.x + (player.y - Ay)/tan(piRadRatio*angle);

    while(1) 
    {
         //if we run out of the map
        if (Ax <0 || Ay < 0 || Ax > block_size*mapWidth - 1 || Ay > block_size*mapHeight -1) 
        {
            //set distance to max
            distance = block_size*mapWidth;
            break;
        }

        grid_Ay = Ay/block_size;
        grid_Ax = Ax/block_size;

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
            wallHit.texture_offset=(int)Ax%block_size;
            wallHit.x[index]=Ax;
            wallHit.y[index]=Ay;
        }
        return distance;
    }

    else
        return vert_distance;
}

float vertical_distance(float angle, float rel_angle,  int index) 
{
    // for horizontal intersection, calculating nearest intersection
    float Ya, Ay, distance, Ax;
    int Xa, grid_Ay, grid_Ax;
    // Ya has to be negative if the ray is facing right
    if ( angle<90.0 || angle>270.0 ) 
    {
        Xa = block_size;
        Ax = ((int)(player.x/block_size)) * block_size + block_size;
        Ya = block_size*tan(piRadRatio*angle) * (-1);
    }
    // else if facing down it has to be positive
    else 
    {
        Xa = block_size*(-1);
        Ax = ((int)(player.x/block_size)) * block_size - 0.0001;
        Ya = block_size*tan(piRadRatio*angle);
    }

    Ay = player.y + (player.x - Ax)*tan(piRadRatio*angle);

    while(1) {
         //if we run out of the map
        if (Ax <0 || Ay < 0 || Ax > block_size*mapWidth - 1 || Ay > block_size*mapHeight -1) 
        {
            //set distance to max
            distance = block_size*mapHeight;
            break;
        }

        grid_Ay = Ay/block_size;
        grid_Ax = Ax/block_size;

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
        wallHit.texture_offset=(int)Ay%block_size;
        wallHit.x[index]=Ax;
        wallHit.y[index]=Ay;
    }
    return distance;
}


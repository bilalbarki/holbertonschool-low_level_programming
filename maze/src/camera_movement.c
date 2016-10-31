#include "../inc/description.h"

void viewingangleinc(int inc) 
{
	int temp = player.viewing_angle;
    temp+=inc;
    player.viewing_angle = convertAngleZeroToThreeSixty(temp);
}

void movePlayer(int inc, int direction) 
{
    if (!detectCollision(direction)) 
    {
       	player.x += inc*cos(piRadRatio*player.viewing_angle);
        player.y -= inc*sin(piRadRatio*player.viewing_angle);
    }
}

void movePlayerSideways(int inc, int direction) 
{
    if (!detectCollision(direction)) 
    {
       	player.x += inc*cos( piRadRatio* (player.viewing_angle+ 90) );
        player.y -= inc*sin( piRadRatio* (player.viewing_angle+ 90) );
    }
}
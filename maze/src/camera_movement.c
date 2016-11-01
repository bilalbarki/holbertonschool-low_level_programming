#include "../inc/description.h"
#include "../inc/definitions.h"
#include "../inc/prototypes.h"

/**
 * Viewing angle increment/decrement
 * @inc: the increment that has to be made
 */
void increment_viewing_angle(int inc) 
{
	int angle = player.viewing_angle;
    angle += inc;
    player.viewing_angle = convertAngleZeroToThreeSixty(angle);
}

/**
 * Moves player in front or backwards direction
 * @inc: the increment that has to be made
 * @rel_direction: the direction RELATIVE to the "viewing angle" that the player has to move, e.g. 0 means front, 180 means backwards
 */
void move_player_front_backwards(int inc, int rel_direction) 
{
    if (!detectCollision(rel_direction)) 
    {
       	player.x += inc*cos(piRadRatio*player.viewing_angle);
        player.y -= inc*sin(piRadRatio*player.viewing_angle);
    }
}

/**
 * Moves player left or right
 * @inc: the increment that has to be made
 * @rel_direction: the direction RELATIVE to the "viewing angle" that the player has to move, e.g. 90 means left, -90 means right
 */
void move_player_sideways(int inc, int rel_direction) 
{
    if (!detectCollision(rel_direction)) 
    {
       	player.x += inc*cos( piRadRatio* (player.viewing_angle + 90) );
        player.y -= inc*sin( piRadRatio* (player.viewing_angle + 90) );
    }
}
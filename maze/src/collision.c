#include "../inc/description.h"
#include "../inc/definitions.h"
#include "../inc/prototypes.h"

/**
 * Detects a collision by casting a predefined number of rays from the camera to measure the distance of an object in the direction of movement
 * @rel_direction: the direction RELATIVE to the "viewing angle" that the player has to move, e.g. 0 means front, 180 means backwards
 * RETURN: returns 1 upon detecting a collision, else returns 0 if no collision
 */
int detectCollision(int direction) {
    float raw_angle = player.viewing_angle + direction;
    for (int i=0; i<20; i++, raw_angle ++)
    {
        float angle;
        int distance;
        float rel_angle = player.viewing_angle + direction - raw_angle;

        // convert angle to range 0 to 360
        angle = convertAngleZeroToThreeSixty(raw_angle);
        distance = horizontal_distance(angle, rel_angle, -1);

        if (distance <15) {
            return 1;
        }
    }
    return 0;
}
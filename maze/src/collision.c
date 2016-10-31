#include "../inc/description.h"

int detectCollision(int direction) {
    float raw_angle = player.viewing_angle + direction - 10;
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
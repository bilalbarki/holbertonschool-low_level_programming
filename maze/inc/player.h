#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

typedef struct plyr {
   float x;
   float y;
   int viewing_angle;
   int height;
   int FOV;
   int distanceFromProjectionPlane;
   float AngleBetweenSubsequentRays;
} maze_player;

#endif // PLAYER_H_INCLUDED


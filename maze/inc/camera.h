#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

struct camera {
   float x;
   float y;
   int viewing_angle;
   int height;
   int FOV;
   int distanceFromProjectionPlane;
   float AngleBetweenSubsequentRays;
};

#endif // CAMERA_H_INCLUDED


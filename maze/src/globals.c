#include "../inc/extern.h"
#include "../inc/definitions.h"

/*Screen dimension constants*/
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 320;

struct camera player;
float piRadRatio;
struct wallHits wallHit;
int mapWidth;
int mapHeight;
int **worldMap;
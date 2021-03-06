const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

static int *gfxPrimitivesPolyIntsGlobal = NULL;
static int gfxPrimitivesPolyAllocatedGlobal = 0;


int altitude[102][102] = {
        {5, 10, 40, 60, 20, -20, -80, -120},
        {40, 20, 30, 30, -10, -40, -90, -110},
        {20, 30, 10, 06, -6, -20, -26, -90},
        {0, -6, 10, 10, -6, -20, -20, -40},
        {-20, -20, -18, -14, -40, -20, -20, -30},
        {-10, -10, -10, -10, -8, -20, -20, -30},
        {20, 10, 10, 10, 10, 04, 10, -10},
        {30, 24, 24, 22, 20, 18, 14, 16}
};

int rotate = 0;
int tile_dimension = 30;
float incline = 0.7;
int tiles =8;

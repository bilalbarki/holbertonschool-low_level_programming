#ifndef WALLHITS_H_INCLUDED
#define WALLHITS_H_INCLUDED

struct wallHits {
    float distance;
    int *x;
    int *y;
    int texture_offset;
};

#endif // WALLHITS_H_INCLUDED
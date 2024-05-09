#include "../includes/fractol.h"

int map_to_color(int iteration)
{
    double t;
    double p;

    t = (double)iteration / MAX_ITERATIONS;
    p = 0.7;
    int red = (int)(9 * (1 - t) * t * t * t * 255) * p;
    int green = (int)(12 * (1 - t) * (1 - t) * t * t * 255) * p;
    int blue = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255) * p;
    
    return (red << 16) | (green << 8) | blue;
}

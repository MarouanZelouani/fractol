#include "../includes/fractol.h"

int map_to_color(int iteration, int p)
{
    double t = (double)iteration / MAX_ITERATIONS;
    int red = (int)(9 * (1 - t) * t * t * t * 255) * p;
    int green = (int)(15 * (1 - t) * (1 - t) * t * t * 255) * p;
    int blue = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255) * p;
     return (red << 16) | (green << 8) | blue;
}
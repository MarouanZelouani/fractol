#include "../includes/fractol.h"

// int map_to_color(int iteration, int color_shift)
// {
//     double t;

//     t = (double)iteration / MAX_ITERATIONS;
//     int red = (int)(9 * (1 - t) * t * t * t * 255);
//     int green = (int)(12 * (1 - t) * (1 - t) * t * t * 255);
//     int blue = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
    
//     red = (red + color_shift) % 255;
//     green = (green + color_shift) % 255;
//     blue = (blue + color_shift) % 255;

//     return (red << 16) | (green << 8) | blue;
// }

#include <math.h>

int map_to_color(int iteration, int hue_shift)
{
    double t;

    t = (double)iteration / MAX_ITERATIONS;
    double hue = fmod(360.0 * (1 - t) + hue_shift, 360.0);

    double red, green, blue;
     
    double c = 1.0;
    double x = c * (1 - fabs(fmod(hue / 60.0, 2) - 1));
    double m = 0.0;

    if (hue >= 0 && hue < 60) {
        red = c;
        green = x;
        blue = 0;
    } else if (hue >= 60 && hue < 120) {
        red = x;
        green = c;
        blue = 0;
    } else if (hue >= 120 && hue < 180) {
        red = 0;
        green = c;
        blue = x;
    } else if (hue >= 180 && hue < 240) {
        red = 0;
        green = x;
        blue = c;
    } else if (hue >= 240 && hue < 300) {
        red = x;
        green = 0;
        blue = c;
    } else {
        red = c;
        green = 0;
        blue = x;
    }

    int r = (int)((red + m) * 255);
    int g = (int)((green + m) * 255);
    int b = (int)((blue + m) * 255);

    return (r << 16) | (g << 8) | b;
}

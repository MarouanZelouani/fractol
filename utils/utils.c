#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int julia(t_complex c, t_complex z)
{
    int iter;
    double temp;

	iter = 0;
    while ((z.real * z.real + z.imag * z.imag) < 4 && iter < MAX_ITERATIONS) {
        temp = z.real * z.real - z.imag * z.imag + c.real;
        z.imag = 2 * z.real * z.imag + c.imag;
        z.real = temp;
        iter++;
    }

    return iter;
}

void draw_julia(void *img, t_plan *plan, t_moves move, t_complex c)
{    
	int i;
	int j;
	int iteration;
	t_complex z;

	// printf("julia\n");
	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			z.imag = map_pixel(i, j, plan, move).imag;
			z.real = map_pixel(i, j, plan, move).real;
			
			iteration = julia(c, z);

			if (iteration == MAX_ITERATIONS)
                my_mlx_pixel_put(img, i, j, 0X000000);
            else 
                my_mlx_pixel_put(img, i, j, map_to_color(iteration, 1));
			j++;
		}
		i++;
	}
}
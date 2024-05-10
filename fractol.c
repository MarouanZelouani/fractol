#include "./includes/fractol.h"

t_complex map_pixel(int i, int j, t_plan *plan, t_moves move)
{
    t_complex c;

    c.real = (((double)i - WIDTH / 2) * (plan->plan_width / WIDTH)) + move.x_move;
	c.imag = (((double)j - HEIGHT / 2) * (plan->plan_width / HEIGHT)) + move.y_move;

    return (c);
}

int calculate_mandelbrot(t_complex z, t_param param)
{
    t_complex c;
    t_complex com;
    double tmp;
    int iteration;

    c = z;  
    tmp = 1;
    iteration = 0;
    com = (t_complex){0.0, 0.0};
    while (com.real * com.real + com.imag * com.imag <= 50
        && iteration < param.iterations)
    {
        tmp = com.real * com.real - com.imag * com.imag + c.real;
        com.imag = 2 * com.real * com.imag + c.imag;
        com.real = tmp;
        iteration++;
    }
    return (iteration);
}

void draw_mandelbrot(void *img, t_plan *plan, t_moves move, t_param param)
{
    t_complex z;
    int iteration;
    int i;
    int j;

    i = 0;
    while (i < WIDTH)
    {
        j = 0;
        while (j < HEIGHT)
        {
            z = map_pixel(i, j, plan, move);
            iteration = calculate_mandelbrot(z, param);
            if (iteration == param.iterations)
                my_mlx_pixel_put(img, i, j, 0X000000);
            else 
                my_mlx_pixel_put(img, i, j, map_to_color(iteration, param.p));
            j++;
        }
        i++;
    }
}

void draw_fractal(char **type)
{
    t_param param;

    param.mlx = mlx_init();
    param.win = mlx_new_window(param.mlx, WIDTH, HEIGHT, "fractol");
    param.img.img = mlx_new_image(param.mlx, WIDTH, HEIGHT);
    param.img.addr = mlx_get_data_addr(param.img.img, &param.img.bits_per_pixel, &param.img.line_length, &param.img.endian);
    param.plan.plan_width = PLANEWIDTH;
    param.move.x_move = 0;
    param.move.y_move = 0;
    param.iterations = MAX_ITERATIONS;
    param.zoom_pers = 0.5;
    param.fractal.name = type[1];
    if (!ft_strncmp("julia", type[1], 5))
        param.fractal.c = (t_complex){ft_atof(type[2]), ft_atof(type[3])};
    param.p = 1;
    if (!ft_strncmp("mandelbrot", type[1], 10))
        draw_mandelbrot(&param.img, &param.plan, (t_moves){0,0}, param);
    else if (!ft_strncmp("julia", type[1], 5))
        draw_julia(&param.img, &param.plan, (t_moves){0,0}, param.fractal.c);
    else if (!ft_strncmp("tricorn", type[1], 7))
        draw_tricorn(&param.img, &param.plan, (t_moves){0,0});
    mlx_key_hook(param.win, events_handler, &param);
    mlx_mouse_hook(param.win, mouse_event, &param);
    mlx_put_image_to_window(param.mlx, param.win, param.img.img, 0, 0);
    mlx_loop(param.mlx);
}

int main(int ac, char **av)
{
    if (ac < 2 || !av[1][0])
        _error(1);
    else if (!ft_strncmp("mandelbrot", av[1], ft_strlen(av[1])) 
        && ft_strlen(av[1]) == 10)
    {
        if (ac > 2)
            _error(1);
        draw_fractal(av);
    }
    else if (!ft_strncmp("tricorn", av[1], ft_strlen(av[1])) 
        && ft_strlen(av[1]) == 7)
    {
        if (ac > 2)
            _error(1);
        draw_fractal(av);
    }
    else if (!ft_strncmp("julia", av[1], ft_strlen(av[1])) 
        && ft_strlen(av[1]) == 5)
    {
        if (ac < 4 || ac > 4 || !av[2][0] || !av[3][0])
            _error(2);
        draw_fractal(av);
    }
    else
        _error(1);       
}
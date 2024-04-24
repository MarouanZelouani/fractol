#include "./includes/fractol.h"

t_complex map_pixel(int i, int j, t_plan *plan, t_moves move)
{
    t_complex c;

    double whratio = (double)WIDTH / HEIGHT;
    c.real = (((double)i / WIDTH) * plan->plan_width * whratio - (plan->plan_start + move.x_move) * whratio);
    c.imag = ((((double)j / HEIGHT)) * (plan->plan_width) - (plan->plan_start + move.y_move));
    return (c);
}

void draw_mandelbrot(void *img, t_plan *plan, t_moves move, int p)
{
    t_mandelbrot m;
    int i;
    int j;

    i = 0;
    while (i < WIDTH)
    {
        j = 0;
        while (j < HEIGHT)
        {
            m.z = map_pixel(i, j, plan, move);
            m.xo = m.z.real;
            m.yo = m.z.imag;  
            m.x = 0.0;
            m.y = 0.0;
            m.iteration = 0;
            m.tmp = 1;
            while (m.x * m.x + m.y * m.y <= 50 && m.iteration < MAX_ITERATIONS)
            {
                m.tmp = m.x * m.x - m.y * m.y + m.xo;
                m.y = 2 * m.x * m.y + m.yo;
                m.x = m.tmp;
                m.iteration++;
            }
            if (m.iteration == MAX_ITERATIONS)
                my_mlx_pixel_put(img, i, j, 0X000000);
            else 
                my_mlx_pixel_put(img, i, j, map_to_color(m.iteration, p));
            j++;
        }
        i++;
    }
}

void draw_fractal(char *type)
{
    t_param param;

    param.mlx = mlx_init();
    param.win = mlx_new_window(param.mlx, WIDTH, HEIGHT, "fractol");
    param.img.img = mlx_new_image(param.mlx, WIDTH, HEIGHT);
    param.img.addr = mlx_get_data_addr(param.img.img, &param.img.bits_per_pixel, &param.img.line_length, &param.img.endian);
    param.plan.plan_start = PLANESTART;
    param.plan.plan_width = PLANEWIDTH;
    param.move.x_move = 0;
    param.move.y_move = 0;
    param.zoom_pers = 0.5;
    param.fractal.name = type;
    param.p = 1;
    if (!ft_strncmp("mandelbrot", type, 10))
        draw_mandelbrot(&param.img, &param.plan, (t_moves){0,0}, param.p);
    else if (!ft_strncmp("julia", type, 5))
        draw_julia(&param.img, &param.plan, (t_moves){0,0}, (t_complex){-1.476,0});
    mlx_key_hook(param.win, events_handler, &param);
    mlx_mouse_hook(param.win, mouse_event, &param);
    mlx_put_image_to_window(param.mlx, param.win, param.img.img, 0, 0);
    mlx_loop(param.mlx);
}

int main(int ac, char **av)
{
    if (ac < 2)
    {
        ft_putstr_fd("Usage : ./fractol <type>\n", 1);       
        return (0);
    }
    else if (!ft_strncmp("mandelbrot", av[1], ft_strlen(av[1])) 
        && ft_strlen(av[1]) == 10)
    {
        draw_fractal(av[1]);
    }
    else if (!ft_strncmp("julia", av[1], ft_strlen(av[1])) 
        && ft_strlen(av[1]) == 5)
    {
        // check the x and y
        // if (ac < 4)
        // {
        //     ft_putstr_fd("Usage : ./fractol julia <x> <y>\n", 1);       
        //     return (0);
        // }
        draw_fractal(av[1]);
    }
    else
        ft_putstr_fd("Usage : ./fractol <type>\n", 1);       
}
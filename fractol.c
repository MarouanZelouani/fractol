#include "./includes/fractol.h"

t_complex map_pixel(int i, int j, t_plan *plan, t_moves move)
{
    t_complex c;

    double whratio = (double)WIDTH / HEIGHT;
    c.real = (((double)i / WIDTH) * plan->plan_width * whratio - (plan->plan_start + move.x_move) * whratio);
    c.imag = ((((double)j / HEIGHT)) * (plan->plan_width) - (plan->plan_start + move.y_move));
    return (c);
}

void draw_mandelbrot(void *img, t_plan *plan, t_moves move)
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
            while (m.x * m.x + m.y * m.y <= 50 && m.iteration < 50)
            {
                m.tmp = m.x * m.x - m.y * m.y + m.xo;
                m.y = 2 * m.x * m.y + m.yo;
                m.x = m.tmp;
                m.iteration++;
            }
            if (m.iteration == 50)
                my_mlx_pixel_put(img, i, j, 0X000000);
            else 
                my_mlx_pixel_put(img, i, j, 202);
            j++;
        }
        i++;
    }
}

void draw_fractal(char *type)
{
    t_param param;
    t_data img;

    param.plan.plan_start = PLANESTART;
    param.plan.plan_width = PLANEWIDTH;

    param.mlx = mlx_init();
    param.win = mlx_new_window(param.mlx, WIDTH, HEIGHT, "fractol");

    img.img = mlx_new_image(param.mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    
    if (!ft_strncmp("mandelbrot", type, 10))
        draw_mandelbrot(&img, &param.plan, (t_moves){0,0});
    // mlx_key_hook(param.win, events_handler, &param);
    // mlx_hook(param.win, 6, 1L << 6, event, &param);
    mlx_put_image_to_window(param.mlx, param.win, img.img, 0, 0);
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
        if (ac < 4)
        {
            ft_putstr_fd("Usage : ./fractol julia <x> <y>\n", 1);       
            return (0);
        }
        draw_fractal(av[1]);
    }
    else
        ft_putstr_fd("Usage : ./fractol <type>\n", 1);       
}
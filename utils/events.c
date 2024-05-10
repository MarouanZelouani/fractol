#include "../includes/fractol.h"

int events_handler(int keycode, t_param *param)
{
    if (keycode == 65363)
        param->move.x_move = param->move.x_move + (0.5 * param->zoom_pers);
    else if (keycode == 65361)
        param->move.x_move = param->move.x_move - (0.5 * param->zoom_pers);
    else if (keycode == 65362)
        param->move.y_move = param->move.y_move - (0.5 * param->zoom_pers);
    else if (keycode == 65364)
        param->move.y_move = param->move.y_move + (0.5 * param->zoom_pers);
    else if (keycode == 32)
        param->p += 5;
    else if (keycode == 65293)
        param->iterations += 50;
    else if (keycode == XK_Escape)
        close_window(param);
    if (!ft_strncmp("julia", param->fractal.name, 5))
        draw_julia(&param->img, &param->plan, param->move, param->fractal.c, *param);
    else if (!ft_strncmp("mandelbrot", param->fractal.name, 10))
        draw_mandelbrot(&param->img, &param->plan, param->move, *param);
    else
        draw_tricorn(&param->img, &param->plan, param->move, *param);
    mlx_put_image_to_window(param->mlx, param->win, param->img.img, 0, 0);
    return (0);
}


int	mouse_event(int keycode, int x, int y, t_param *param)
{
    t_complex old;
    t_complex new;

    if (keycode == 4)
    {
        old = map_pixel(x, y, &param->plan, param->move);
        param->zoom_pers = param->zoom_pers / 1.105;
        param->plan.plan_width *= 0.9;                    
        new = map_pixel(x, y, &param->plan, param->move);
        param->move.x_move += (old.real -  new.real);
        param->move.y_move += old.imag -  new.imag;
    }
    else if (keycode == 5)
    {
        old = map_pixel(x, y, &param->plan, param->move);
        param->zoom_pers = param->zoom_pers * 1.105;
        param->plan.plan_width  = param->plan.plan_width / 0.9;
        new = map_pixel(x, y, &param->plan, param->move);
        param->move.x_move += old.real - new.real;
        param->move.y_move += old.imag - new.imag;
    }
    if (!ft_strncmp("julia", param->fractal.name, 5))
        draw_julia(&param->img, &param->plan, param->move, param->fractal.c, *param);
    else if (!ft_strncmp("mandelbrot", param->fractal.name, 10))
        draw_mandelbrot(&param->img, &param->plan, param->move, *param);
    else
        draw_tricorn(&param->img, &param->plan, param->move, *param);
    mlx_put_image_to_window(param->mlx, param->win, param->img.img, 0, 0);
    return (0);
}

int close_window(t_param *param)
{
    mlx_destroy_window(param->mlx,param->win);
    mlx_destroy_image(param->mlx, param->img.img);
    mlx_destroy_display(param->mlx);
    free(param->mlx);
    exit(EXIT_SUCCESS);
}
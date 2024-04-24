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
    {
        param->p++;
    }
    else if (keycode == XK_Escape)
    {
        mlx_destroy_window(param->mlx,param->win);
        mlx_destroy_image(param->mlx, param->img.img);  
        exit(0);
    }
    if (!ft_strncmp("julia", param->fractal.name, 5))
        draw_julia(&param->img, &param->plan, param->move, (t_complex){-1.476,0});
    else
        draw_mandelbrot(&param->img, &param->plan, param->move, param->p);
    mlx_put_image_to_window(param->mlx, param->win, param->img.img, 0, 0);
    return (0);
}


int	mouse_event(int keycode, int x, int y, t_param *param)
{
    if (keycode == 4)
    {
        param->zoom_pers = param->zoom_pers / 1.105;
        param->plan.plan_width *= 0.9;
        param->plan.plan_start *= 0.9;                    
    }
    else if (keycode == 5)
    {
        param->zoom_pers = param->zoom_pers * 1.105;
        param->plan.plan_width  = param->plan.plan_width / 0.9;
        param->plan.plan_start  = param->plan.plan_start / 0.9;
    }

    if (!ft_strncmp("julia", param->fractal.name, 5))
        draw_julia(&param->img, &param->plan, param->move, (t_complex){-1.476,0});
    else
        draw_mandelbrot(&param->img, &param->plan, param->move, param->p);
    mlx_put_image_to_window(param->mlx, param->win, param->img.img, 0, 0);
    return (0);
}
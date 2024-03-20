# include "./includes/fractol.h"

#define WIDTH 1800
#define HEIGHT 1000
#define PLANEWIDTH 3.0
#define PLANESTART (double)PLANEWIDTH / 2
// double bottom_right_c_real = 1.0;  
// double bottom_right_c_imag = -2.0;
// double top_left_c_real = -2.0;
// double top_left_c_imag = 2.0;

t_data img;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// t_complex map_pixel(int i, int j, int z, int x)
// {
//     t_complex c;
//     static double PLANEWIDTH = 3.0;
//     static double PLANESTART = PLANEWIDTH / 2;


//     double whratio = (double)WIDTH / HEIGHT;
//     // zoom line
//     c.real = (((double)i / WIDTH) * (PLANEWIDTH / z) * whratio - (PLANESTART  / z) * whratio);
//     // shift line
//     c.imag = ((((double)j / HEIGHT)) * (PLANEWIDTH / z) - ((PLANESTART) / z));
//     return (c);
// }

t_complex map_pixel(int i, int j, t_plan *plan, t_moves move)
{
    t_complex c;

    double whratio = (double)WIDTH / HEIGHT;
    // zoom line
    c.real = (((double)i / WIDTH) * plan->plan_width * whratio - (plan->plan_start + move.x_move) * whratio);
    // shift line
    c.imag = ((((double)j / HEIGHT)) * (plan->plan_width) - (plan->plan_start + move.y_move));
    return (c);
}


// t_complex mapi(int i, int j)
// {
//     t_complex c;
//     double aspect_ratio;
//     double range_real;
//     double range_img;
//     double scaled_width;

//     aspect_ratio = (double)WIDTH / HEIGHT;
//     range_real = bottom_right_c_real - top_left_c_real;
//     range_img = top_left_c_imag - bottom_right_c_imag;
//     scaled_width = aspect_ratio * range_img;

//     c.real = ((double)i / WIDTH) * range_real + top_left_c_real;
//     c.imag = ((double)j / HEIGHT) * scaled_width + bottom_right_c_imag;

//     return (c);
// }

void draw_fractol(void *img, int p, t_plan *plan, t_moves move)
{
    double x;
    double y;
    double xo;
    double yo;
    double tmp;
    t_complex z;

    int i;
    int j;
    int iteration;

    i = 0;
    while (i < WIDTH)
    {
        j = 0;
        while (j < HEIGHT)
        {
            z = map_pixel(i, j, plan, move);
            xo = z.real;
            yo = z.imag;  
            x = 0.0;
            y = 0.0;
            iteration = 0;
            tmp = 1;
            while (x * x + y * y <= 50 && iteration < 50)
            {
                tmp = x * x - y * y + xo;
                y = 2 * x * y + yo;
                x = tmp;
                iteration++;
            }
            if (iteration == 50)
                my_mlx_pixel_put(img, i, j, 0X000000);
            else 
            {
                // printf("%d\n", p);
                int color = iteration * 300 + iteration * 10 + iteration * 1024 * p;
                my_mlx_pixel_put(img, i, j, color);
            }
            j++;
        }
        i++;
    }
}
int events_handler(int keycode, t_param *param)
{
    static int p = 1;
    static t_moves move;
    // static int iterations;
    static double pers = 0.5;

    // zoom_pers = 0.5;
    printf("%d\n", keycode);
    if (keycode == XK_a)
        p = p % 10000 * 2 + 1;
    else if (keycode == XK_s)
    {
        pers = pers * 2;
        param->plan.plan_width  = param->plan.plan_width / 0.5;
        param->plan.plan_start  = param->plan.plan_start / 0.5;
    }
    else if (keycode == XK_q)
    {
        pers = pers / 2;
        param->plan.plan_width  = param->plan.plan_width * 0.5;
        param->plan.plan_start  = param->plan.plan_start * 0.5;
    }
    else if (keycode == 65363)
        move.x_move = move.x_move + (0.5 * pers);
    else if (keycode == 65361)
        move.x_move = move.x_move - (0.5 * pers);
    else if (keycode == 65362)
        move.y_move = move.y_move - (0.5 * pers);
    else if (keycode == 65364)
        move.y_move = move.y_move + (0.5 * pers);
    else if (keycode == 61)
    {

    }
    else if (keycode == XK_Escape)
    {
        mlx_destroy_window(param->mlx,param->win);
        mlx_destroy_image(param->mlx,img.img);
        exit(0);
    }
    draw_fractol(&img, p, &param->plan, move);
    mlx_put_image_to_window(param->mlx, param->win, img.img, 0, 0);
    return (0);
}

int main(void)
{
    // void *mlx;
    // void *mlx_win;
    t_param param;
    int w;
    int h;    
    // t_plan plan;

    w = WIDTH;
    h = HEIGHT;

    // plan = (t_plan *) malloc(sizeof(t_plan));
    param.plan.plan_start = PLANESTART;
    param.plan.plan_width = PLANEWIDTH;

    param.mlx = mlx_init();
    param.win = mlx_new_window(param.mlx, w, h, "fractol");

    img.img = mlx_new_image(param.mlx, w, h);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    
    draw_fractol(&img, 1, &param.plan, (t_moves){0,0});

    mlx_key_hook(param.win, events_handler, &param);
    // mlx_hook(param.win, 2, 1L<<0, &);
    mlx_put_image_to_window(param.mlx, param.win, img.img, 0, 0);
    mlx_loop(param.mlx);
}
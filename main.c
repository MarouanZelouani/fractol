# include "./includes/fractol.h"

#define WIDTH 800
#define HEIGHT 800
#define PLANEWIDTH 3.0
#define PLANESTART (double)PLANEWIDTH / 2


t_data img;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

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
                int color = iteration * 300 + iteration * 10 + iteration * 1024 * p;
                my_mlx_pixel_put(img, i, j, color);
            }
            j++;
        }
        i++;
    }
}
int event (int x, int y, t_param *param)
{
    //printf("Mouse :x=%d, y =%d\n", x , y);
    //printf("here");
    // int y0 = y;
    param->mouse.x = x;
    param->mouse.y = y;
    return (0);
}

int events_handler(int keycode, t_param *param)
{
        t_complex old;
        t_complex new;
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
        // printf("Keypress :x=%d, y =%d\n", param->mouse.x , param->mouse.y);
        

        old = map_pixel(param->mouse.x, param->mouse.y, &param->plan, move);
        printf("OLD real: %f ==> OLD IMG: %f\n", old.real, old.imag);
        param->plan.plan_width  = param->plan.plan_width / 0.5;
        param->plan.plan_start  = param->plan.plan_start / 0.5;
        
        new = map_pixel(param->mouse.x, param->mouse.y, &param->plan, move);
        printf("NEW real: %f ==> NEW IMG: %f\n", new.real, new.imag);

        move.x_move = move.x_move + (old.real - new.real);
        move.y_move = move.y_move + (old.imag - new.imag);
        // move.y_move = move.y_move + map_pixel(param->mouse.x, param->mouse.y, &param->plan, move).imag * pers;
    }
    else if (keycode == XK_q)
    {
        pers = pers / 2;
        
        
        old = map_pixel(param->mouse.x, param->mouse.y, &param->plan, move);
        

        param->plan.plan_width  = param->plan.plan_width * 0.5;
        param->plan.plan_start  = param->plan.plan_start * 0.5;

        new = map_pixel(param->mouse.x, param->mouse.y, &param->plan, move);
        

        move.y_move =(old.real - new.real);
        move.x_move =(old.imag - new.imag);
        
        // move.x_move = move.x_move + map_pixel(param->mouse.x, param->mouse.y, &param->plan, move).real * pers;
        // move.y_move = move.y_move + map_pixel(param->mouse.x, param->mouse.y, &param->plan, move).imag * pers;
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

    // plan = (t_plan *) malloc(sizeof(t_plan));
    param.plan.plan_start = PLANESTART;
    param.plan.plan_width = PLANEWIDTH;

    param.mlx = mlx_init();
    param.win = mlx_new_window(param.mlx, w, h, "fractol");

    img.img = mlx_new_image(param.mlx, w, h);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    
    draw_fractol(&img, 1, &param.plan, (t_moves){0,0});

    mlx_key_hook(param.win, events_handler, &param);
    // mlx_mouse_hook(param.win, event, &param);
    // mlx_hook(param.win, 2, 1L<<0, &);
    mlx_hook(param.win, 6, 1L << 6, event, &param);
    mlx_put_image_to_window(param.mlx, param.win, img.img, 0, 0);
    mlx_loop(param.mlx);
}
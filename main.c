# include "./includes/fractol.h"

#define WIDTH 1800
#define HEIGHT 1000
#define PLANEWIDTH 3.0
//#define PLANESTART (double)PLANEWIDTH / 2
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

t_complex map_pixel(int i, int j, int z, int x)
{
    t_complex c;

    double whratio = (double)WIDTH / HEIGHT;
    c.real = (((double)i / WIDTH) * (PLANEWIDTH / z) * whratio - (((double)PLANEWIDTH / (2 + x)) / z) * whratio);
    c.imag = ((((double)j / HEIGHT)) * (PLANEWIDTH / z) - (((double)PLANEWIDTH / (2 + x) ) / z));
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

void draw_fractol(void *img, int p, double zoom, double w)
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
    (void)zoom;
    (void)w;

    i = 0;
    while (i < WIDTH)
    {
        j = 0;
        while (j < HEIGHT)
        {
            z = map_pixel(i, j, zoom, w);
            // z = mapi(i, j);
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
            if (iteration == 30)
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
int zoom(int keycode, t_param *param)
{
    static int p = 1;
    static double zoom = 1;
    static double x = 0;

    if (keycode == XK_a)
    {
        p = p % 10000 * 2 + 1;
        draw_fractol(&img, p, zoom, x);
        mlx_put_image_to_window(param->mlx, param->win, img.img, 0, 0);
    }
    else if (keycode == XK_s)
    {
        zoom = zoom * 2;
        draw_fractol(&img, p, zoom, x);
        mlx_put_image_to_window(param->mlx, param->win, img.img, 0, 0);
    }
    else if (keycode == XK_w)
    {
        x = x * 2;
        draw_fractol(&img, p, zoom, x);
        mlx_put_image_to_window(param->mlx, param->win, img.img, 0, 0);
    }
    else if (keycode == XK_Escape)
    {
        mlx_destroy_window(param->mlx,param->win);
        mlx_destroy_image(param->mlx,img.img);
        exit(0);
    }
    return (0);
}

int main(void)
{
    // void *mlx;
    // void *mlx_win;
    t_param param;
    int w;
    int h;    

    w = WIDTH;
    h = HEIGHT;
    param.mlx = mlx_init();
    param.win = mlx_new_window(param.mlx, w, h, "fractol");

    img.img = mlx_new_image(param.mlx, w, h);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    
    draw_fractol(&img, 1, 1, 0);

    mlx_key_hook(param.win, zoom, &param);
    // mlx_hook(param.win, 2, 1L<<0, &);

    mlx_put_image_to_window(param.mlx, param.win, img.img, 0, 0);
    mlx_loop(param.mlx);
}
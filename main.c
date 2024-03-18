# include "./includes/fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_circle(t_data *img, int x, int y, int r)
{
    int i;
    int j;

    i = x - r;
    while (i <= x + r)
    {
        j = y - r;
        while (j <= y + r)
        {
            if ((i - x) * (i - x) + (j - y) * (j - y) <= r * r)
                my_mlx_pixel_put(img, i, j, 0XFFFFFF);
            j++;
        }
        i++;
    }
}

void color_window(t_data *img, int x, int y)
{
    int i;
    int j;

    i = 0;
    while (i <= x)
    {
        j = 0;
        while(j <= y)
        {
            my_mlx_pixel_put(img, i, j, 0XFFFFFF);            
            j++;
        }
        i++;
    }
}

void draw_line(t_data *img)
{
    int i;

    i = 0;
    while (i <= 500)
    {
        my_mlx_pixel_put(img, i, 250, 0XFFFFFF);
        i++;
    }
}

t_complex map_pixel(int i, int j, int w, int h)
{
    t_complex c;

    c.real = (((double)i / w) * (2.0 + 2.0) - 2.0 ) / 2;
    c.imag = ((((double)h - j) / h) * (2.0 + 2.0) - 2.0 ) / 2;
    return (c);
}

// t_complex pixel_to_complex(int i, int j, int width, int height, t_complex top_left_c, t_complex bottom_right_c) {
//     double real_part = top_left_c.real + (bottom_right_c.real - top_left_c.real) * i / width;
//     double imag_part = bottom_right_c.imag + (top_left_c.imag - bottom_right_c.imag) * j / height;
//     t_complex result = {real_part, imag_part};
//     return result;
// }

void draw_fractol(void *img, int w, int h)
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
    while (i < w)
    {
        j = 0;
        while (j < h)
        {
            // xo = ((double)i / w) * (MAX_REAL - MIN_REAL) + MIN_REAL;
            // yo = ((double)j / h) * (MAX_IMAG - MIN_IMAG) + MIN_IMAG;
            z = map_pixel(i, j, w, h);
            xo = z.real;
            yo = z.imag;  
            x = 0.0;
            y = 0.0;
            iteration = 0;
            while (x * x + y * y <= 4 && iteration < 500)
            {
                tmp = x * x - y * y + xo;
                y = 2 * x * y + yo;
                x = tmp;
                iteration++;
            }

            if (iteration == 500)
                my_mlx_pixel_put(img, i, j, 0X000000);
            else 
            {
                int color = iteration * 280;
                my_mlx_pixel_put(img, i, j, color);
            }
            j++;
        }
        i++;
    }
}

int main(void)
{
    void *mlx;
    void *mlx_win;
    t_data img;
    int w;
    int h;    

    w = 800;
    h = 800;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, w, h, "fractol");

    img.img = mlx_new_image(mlx, w, h);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    
    // int i = 0;
    // int j = 0;

    // draw_line(&img);
    // draw_circle(&img, 250, 250, 50);
    // color_window(&img, 500, 500);
    draw_fractol(&img, w, h);

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}
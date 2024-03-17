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

int main(void)
{
    void *mlx;
    void *mlx_win;
    t_data img;    

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 500, 500, "fractol");

    img.img = mlx_new_image(mlx, 500, 500);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    
    // draw_line(&img);
    // draw_circle(&img, 250, 250, 50);
    color_window(&img, 500, 500);

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}
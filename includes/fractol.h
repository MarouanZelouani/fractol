#include <mlx.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <X11/keysym.h>

#define WIDTH 900
#define HEIGHT 800
#define PLANEWIDTH 3.0
#define PLANESTART (double)PLANEWIDTH / 2


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct  s_complex
{
	double real;
	double imag;
} t_complex;

typedef struct s_plan
{
	double plan_width;
	double plan_start;
}t_plan;

typedef struct s_mo
{
	int x;
	int y;
}t_mo;

typedef struct s_param
{
	void *win;
	void *mlx;
	// t_data img;
	t_plan plan;
	t_mo mouse;
} t_param;

typedef struct s_moves
{
	double x_move;
	double y_move;
}t_moves;

typedef struct s_mandelbrot
{
	double x;
    double y;
    double xo;
    double yo;
    double tmp;
    int iteration;
    t_complex z;
} t_mandelbrot;

void	ft_putchar_fd(char c, int fd);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
int ft_strlen (char *str);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
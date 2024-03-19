#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <X11/keysym.h>

# define MAX_REAL 1.5
# define MIN_REAL -2.5
# define MAX_IMAG 1.5
# define MIN_IMAG -1.5

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

typedef struct s_param
{
	void *win;
	void *mlx;
} t_param;

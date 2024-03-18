#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

# define MAX_REAL 1.0
# define MIN_REAL -2.5
# define MAX_IMAG 1.0
# define MIN_IMAG -1.0

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


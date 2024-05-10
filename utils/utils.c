#include "../includes/fractol.h"

static	int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\n' || c == '\r' || c == '\f')
		return (1);
	return (0);
}

long	ft_atoi(const char *str)
{
	int					sign;
	long long	result;
	int					i;

	sign = 1;
	result = 0;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + str[i] - '0';
		i++;
	}
	return ((long)sign * result);
}
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double ft_atof (const char *str)
{
    double				exponent;
	double		fraction; 
	char *c;
	double s = 1;

	c = (char *)str;
	if (str[0] == '-' && str[1] == '0')
		s = -1;
	exponent = (double)ft_atoi(c);
	if (str[0] == '.')
		exponent = 0.0;
	while (*c && *c != '.')
		c++;
	if(*c == '.')
		c++;
	fraction = (double)ft_atoi(c);
	int len = ft_strlen(c);
	while(len != 0)
	{
		fraction /= 10;
		len--;
	}
	if (exponent >= 0 )
		return ( s * (exponent + fraction));
    return (s * (exponent - fraction));
}

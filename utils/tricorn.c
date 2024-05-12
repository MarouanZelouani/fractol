/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 03:13:44 by mzelouan          #+#    #+#             */
/*   Updated: 2024/05/12 03:13:45 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	calculate_tricorn(t_complex z, t_param param)
{
	int			iter;
	double		temp;
	t_complex	c;

	c = z;
	iter = 0;
	while ((z.real * z.real + z.imag * z.imag) < 4 && iter < param.iterations)
	{
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = -2 * z.real * z.imag + c.imag;
		z.real = temp;
		iter++;
	}
	return (iter);
}

void	draw_tricorn(void *img, t_plan *plan, t_moves move, t_param param)
{
	int			i;
	int			j;
	int			iteration;
	t_complex	z;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			z.imag = map_pixel(i, j, plan, move).imag;
			z.real = map_pixel(i, j, plan, move).real;
			iteration = calculate_tricorn(z, param);
			if (iteration == param.iterations)
				my_mlx_pixel_put(img, i, j, 0X000000);
			else
				my_mlx_pixel_put(img, i, j, map_to_color(iteration, param.p));
			j++;
		}
		i++;
	}
}

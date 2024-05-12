/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 04:59:32 by mzelouan          #+#    #+#             */
/*   Updated: 2024/05/12 05:15:16 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_complex	map_pixel(int i, int j, t_plan *plan, t_moves move)
{
	t_complex	c;

	c.real = (((double)i - WIDTH / 2) * (plan->plan_width / WIDTH)) \
	+ move.x_move;
	c.imag = (((double)j - HEIGHT / 2) * (plan->plan_width / HEIGHT)) \
	+ move.y_move;
	return (c);
}

int	map_to_color(int iteration, int hue_shift)
{
	double	t;
	double	hue;
	double	c;
	double	x;
	t_color	color;

	t = (double)iteration / MAX_ITERATIONS;
	hue = fmod(360.0 * (1 - t) + hue_shift, 360.0);
	c = 1.0;
	x = c * (1 - fabs(fmod(hue / 60.0, 2) - 1));
	if (hue >= 0 && hue < 60)
		color = (t_color){c, x, 0};
	else if (hue >= 60 && hue < 120)
		color = (t_color){x, c, 0};
	else if (hue >= 120 && hue < 180)
		color = (t_color){0, c, x};
	else if (hue >= 180 && hue < 240)
		color = (t_color){0, x, c};
	else if (hue >= 240 && hue < 300)
		color = (t_color){x, 0, c};
	else
		color = (t_color){c, 0, x};
	return ((((int)(color.red * 255)) << 16) \
		| (((int)(color.green * 255)) << 8) | (int)(color.blue * 255));
}

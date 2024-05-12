/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 03:14:09 by mzelouan          #+#    #+#             */
/*   Updated: 2024/05/12 03:41:30 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	_error(int number)
{
	if (number == 1)
	{
		ft_putstr_fd("Usage: ./fractol <name>\n", 1);
		ft_putstr_fd("Available Fractals:\n", 1);
		ft_putstr_fd("\t> mandelbrot\n", 1);
		ft_putstr_fd("\t> julia\n", 1);
		ft_putstr_fd("\t> tricorn\n", 1);
	}
	if (number == 2)
		ft_putstr_fd("Usage: ./fractol julia <x> <y>\n", 1);
	exit(EXIT_FAILURE);
}

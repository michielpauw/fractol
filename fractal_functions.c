/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 18:08:33 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/15 14:21:26 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	in_mandelbrot(t_complex c, t_complex z, int iterations)
{
	long double		z_r_sq;
	long double		z_i_sq;
	int				i;

	i = 0;
	z_r_sq = 0;
	z_i_sq = 0;
	z.i = 0;
	z.r = 0;
	while (z_i_sq + z_r_sq <= 4.0 && i < iterations)
	{
		z.i = z.i * z.r;
		z.i += z.i;
		z.i += c.i;
		z.r = z_r_sq - z_i_sq + c.r;
		z_r_sq = z.r * z.r;
		z_i_sq = z.i * z.i;
		i++;
	}
	if (z_i_sq + z_r_sq > 4.0)
		return (i);
	return (0);
}

int	in_julia(t_complex z, t_complex c, int iterations)
{
	int			i;
	long double	z_r_sq;
	long double	z_i_sq;

	i = 0;
	z_r_sq = z.r * z.r;
	z_i_sq = z.i * z.i;
	while (z_i_sq + z_r_sq <= 4.0 && i < iterations)
	{
		z.i = z.i * z.r;
		z.i += z.i;
		z.i += c.i;
		z.r = z_r_sq - z_i_sq + c.r;
		z_r_sq = z.r * z.r;
		z_i_sq = z.i * z.i;
		i++;
	}
	if (z_i_sq + z_r_sq > 4.0)
		return (i);
	return (0);
}

int	in_sierpinski(t_complex z, t_complex c, int iterations)
{
	int	x;
	int	y;

	(void)c;
	x = (int)z.r;
	y = (int)z.i;
	while ((x > 0 || y > 0))
	{
		if (x % 3 == 1 && y % 3 == 1)
			return (0);
		x /= 3;
		y /= 3;
		iterations--;
	}
	return (1);
}

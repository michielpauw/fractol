/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 18:08:33 by mpauw             #+#    #+#             */
/*   Updated: 2018/01/02 16:47:46 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		in_mand(t_complex c, t_complex z, int iterations)
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

int		in_julia(t_complex z, t_complex c, int iterations)
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

int		in_sierp(t_complex z, t_complex c, int iterations)
{
	int	x;
	int	y;

	(void)iterations;
	(void)c;
	x = (int)z.r;
	y = (int)z.i;
	while (x > 0 || y > 0)
	{
		if (x % 3 == 1 && y % 3 == 1)
			return (0);
		x /= 3;
		y /= 3;
	}
	return (1);
}

t_event	*add_tri_point(t_event *event, int x, int y)
{
	int	random;
	int	x_tri;
	int	y_tri;

	random = rand() % 3;
	y_tri = I_H - MARGIN_TRI;
	if (random == 0)
	{
		x_tri = I_H / 2.0;
		y_tri = MARGIN_TRI;
	}
	else
		x_tri = (random == 1) ? 100 : I_H - MARGIN_TRI;
	if (!x && !y)
	{
		x = 0.5 * (event->store_x + x_tri);
		y = 0.5 * (event->store_y + y_tri);
	}
	event->cur_grain += 1;
	event->store_x = x;
	event->store_y = y;
	((int *)((event->img)->img_arr))[x + y *
		((event->img)->size_line_int)] = event->color;
	return (event);
}

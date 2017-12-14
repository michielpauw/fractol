/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 18:08:33 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/14 18:19:53 by mpauw            ###   ########.fr       */
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

t_event	*construct_menger(t_event *event)
{
	t_point	*cube;
	int		size = 100;
	int		i;
	t_angle	sq[4];

	cube = get_cube(size);
	cube = simple_rotation(cube, 0, -1);
	cube = simple_rotation(cube, 1, -1);
	cube = get_projection(cube, 0, event);
	i = 0;
	sq[0].x = cube[0].x;
	sq[0].y = cube[0].y;
	sq[0].index = cube[0].x + cube[0].y * (event->img)->size_line_int;
	sq[1].x = cube[4].x;
	sq[1].y = cube[4].y;
	sq[1].index = cube[4].x + cube[4].y * (event->img)->size_line_int;
	sq[2].x = cube[7].x;
	sq[2].y = cube[7].y;
	sq[2].index = cube[7].x + cube[7].y * (event->img)->size_line_int;
	sq[3].x = cube[3].x;
	sq[3].y = cube[3].y;
	sq[3].index = cube[3].x + cube[3].y * (event->img)->size_line_int;
	event->img = fill_surface(event->img, sq, 0xffff00);

	sq[0].x = cube[5].x;
	sq[0].y = cube[5].y;
	sq[0].index = cube[5].x + cube[5].y * (event->img)->size_line_int;
	sq[1].x = cube[6].x;
	sq[1].y = cube[6].y;
	sq[1].index = cube[6].x + cube[6].y * (event->img)->size_line_int;
	sq[2].x = cube[7].x;
	sq[2].y = cube[7].y;
	sq[2].index = cube[7].x + cube[7].y * (event->img)->size_line_int;
	sq[3].x = cube[4].x;
	sq[3].y = cube[4].y;
	sq[3].index = cube[4].x + cube[4].y * (event->img)->size_line_int;
//	event->img = fill_surface(event->img, sq, 0xff00ff);

	sq[0].x = cube[0].x;
	sq[0].y = cube[0].y;
	sq[0].index = cube[0].x + cube[0].y * (event->img)->size_line_int;
	sq[1].x = cube[1].x;
	sq[1].y = cube[1].y;
	sq[1].index = cube[1].x + cube[1].y * (event->img)->size_line_int;
	sq[2].x = cube[5].x;
	sq[2].y = cube[5].y;
	sq[2].index = cube[5].x + cube[5].y * (event->img)->size_line_int;
	sq[3].x = cube[4].x;
	sq[3].y = cube[4].y;
	sq[3].index = cube[4].x + cube[4].y * (event->img)->size_line_int;
//	event->img = fill_surface(event->img, sq, 0xff00);
	sq[0].x = cube[0].x;
	sq[0].y = cube[0].y;
	sq[0].index = cube[0].x + cube[0].y * (event->img)->size_line_int;
	sq[1].x = cube[1].x;
	sq[1].y = cube[1].y;
	sq[1].index = cube[1].x + cube[1].y * (event->img)->size_line_int;
	sq[2].x = cube[2].x;
	sq[2].y = cube[2].y;
	sq[2].index = cube[2].x + cube[2].y * (event->img)->size_line_int;
	sq[3].x = cube[3].x;
	sq[3].y = cube[3].y;
	sq[3].index = cube[3].x + cube[3].y * (event->img)->size_line_int;
//	event->img = fill_surface(event->img, sq, 0xffffff);
	sq[0].x = cube[7].x;
	sq[0].y = cube[7].y;
	sq[0].index = cube[7].x + cube[7].y * (event->img)->size_line_int;
	sq[1].x = cube[6].x;
	sq[1].y = cube[6].y;
	sq[1].index = cube[6].x + cube[6].y * (event->img)->size_line_int;
	sq[2].x = cube[2].x;
	sq[2].y = cube[2].y;
	sq[2].index = cube[2].x + cube[2].y * (event->img)->size_line_int;
	sq[3].x = cube[3].x;
	sq[3].y = cube[3].y;
	sq[3].index = cube[3].x + cube[3].y * (event->img)->size_line_int;
	event->img = fill_surface(event->img, sq, 0xff);
	sq[0].x = cube[5].x;
	sq[0].y = cube[5].y;
	sq[0].index = cube[5].x + cube[5].y * (event->img)->size_line_int;
	sq[1].x = cube[1].x;
	sq[1].y = cube[1].y;
	sq[1].index = cube[1].x + cube[1].y * (event->img)->size_line_int;
	sq[2].x = cube[2].x;
	sq[2].y = cube[2].y;
	sq[2].index = cube[2].x + cube[2].y * (event->img)->size_line_int;
	sq[3].x = cube[6].x;
	sq[3].y = cube[6].y;
	sq[3].index = cube[6].x + cube[6].y * (event->img)->size_line_int;
	event->img = fill_surface(event->img, sq, 0xffff);


	return (event);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fractal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 11:45:13 by mpauw             #+#    #+#             */
/*   Updated: 2018/01/02 16:47:49 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_color(t_complex z, int random, t_event *ev)
{
	int	color;
	int	pos;

	while (z.r > 1)
		z.r -= 1;
	while (z.i > 1)
		z.i -= 1;
	pos = z.r * 3;
	pos = pos + z.i * 3 + 1;
	color = (pos * 0xff * ev->color / ((random % 9) + 1));
	return (color);
}

t_event		*get_fractal(t_event *ev)
{
	t_complex	z;
	int			i;
	int			length;
	int			rep;
	int			random;

	i = 0;
	random = rand();
	length = (ev->img)->size_line_int * (ev->frc).height /
		ev->cur_grain * ev->cur_grain;
	while (i < length)
	{
		z.i = get_im(ev, i);
		z.r = get_re(ev, i);
		if (!(rep = (ev->frc).f(z, ev->c, (ev->frc).iterations)))
			i = fill_square(&(ev->img), i, ev->cur_grain, ev->sec_color);
		else if ((ev->frc).id == 2)
			i = fill_square(&(ev->img), i, ev->cur_grain, get_color(z,
						random, ev));
		else
			i = fill_square(&(ev->img), i, ev->cur_grain, (((rep * 0xff) /
							((ev->frc).iterations) * ev->color)
						% 0xffffff + 1));
	}
	return (ev);
}

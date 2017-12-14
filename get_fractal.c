/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 12:23:21 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/14 15:21:44 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_event	*get_fractal(t_event *ev)
{
	t_complex	z;
	int			i;
	int			length;
	int			rep;
	
	if ((ev->frc).id == 3)
		return (construct_menger(ev));
	i = 0;
	length = (ev->img)->size_line_int * (ev->frc).height /
		ev->cur_grain * ev->cur_grain;
	while (i < length)
	{
		z.i = get_im(ev, i);
		z.r = get_re(ev, i);
		if (!(rep = (ev->frc).f(z, ev->c, (ev->frc).iterations)))
			i = fill_square(&(ev->img), i, ev->cur_grain, ev->sec_color);
		else
			i = fill_square(&(ev->img), i, ev->cur_grain, (((rep * 0xff) /
							(ev->frc).iterations) * ev->color) % 0xffffff); 
	}
	return (ev);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 12:23:21 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/13 19:47:19 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_event	*get_fractal(t_event *event)
{
	t_complex	z;
	int			index;
	int			length;
	int			rep;
	
	index = 0;
	length = (event->img)->size_line_int * (event->frc).height /
		event->cur_grain * event->cur_grain;
	while (index < length)
	{
		z.i = get_im(event, index);
		z.r = get_re(event, index);
		if (!(rep = (event->frc).f(z, event->c, (event->frc).iterations)))
		{
			index = fill_square(&(event->img), index,
					event->cur_grain, event->sec_color);
		}
		else
		{
			index = fill_square(&(event->img), index, event->cur_grain,
				(((rep * 0xff) / (event->frc).iterations) *
				 event->color) % 0xffffff); 
		}
	}
	return (event);
}

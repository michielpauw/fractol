/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 13:57:50 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/14 15:20:51 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_fractal	find_frac(int fractal)
{
	static t_fractal	frac_array[] = {
		{0, "Mandelbrot", &in_mandelbrot, 16, 1800, 1200, 0xff, -2.0, -4.0 / 3.0, 4.0 / 1800},
		{1, "Julia", &in_julia, 8, 1800, 1200, 0xff, -2.0, -4.0 / 3.0, 4.0 / 1800},
		{2, "Sierpinski", &in_sierpinski, 1, 1200, 1200, 1, 0, 0, 3.0 / 1200},
		{3, "Menger sponge", &in_julia, 1, 1200, 1200, 1, 0, 0, 3.0 / 1200}
	};
	return (frac_array[fractal]);
}

t_event				*setup_event(void *mlx, int fractal)
{
	t_event		*event;
	t_complex	c;
	(void)fractal;

	c.r = 0;
	c.i = 0;
	if (!(event = (t_event *)malloc(sizeof(t_event))))
		error(errno);
	event->mlx = mlx;
	event->c = c;
	event->frc = find_frac(fractal);
	event->cur_grain = (event->frc).grain;
	event->store_x = 0;
	event->store_y = 0;
	event->disco = 0;
	event->color = 0x100000;
	event->sec_color = 0xffffff;
	return (event);
}

t_event				*update_event(t_event *event, int fractal)
{
	event->frc = find_frac(fractal);
	return (event);
}

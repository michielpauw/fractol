/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 13:57:50 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/15 16:29:07 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_fractal	find_frac(int fractal)
{
	static t_fractal	frac_array[] = {
		{0, "Mandelbrot", &in_mandelbrot, 16, IMG_W, IMG_H, 0xff, -2.5, -4.0 / 3.0, 4.0 / IMG_W},
		{1, "Julia", &in_julia, 8, IMG_W, IMG_H, 0xff, -2.0, -4.0 / 3.0, 4.0 / IMG_W},
		{2, "Sierpinski", &in_sierpinski, 1, IMG_SQ_3, IMG_SQ_3, IMG_SQ_3, 0, 0, 3 / IMG_SQ_3}
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
	event->coor_wanted = 1;
	event->coor_put = 0;
	event->disco = 0;
	event->mouse_hold = 0;
	event->change_c = 1;
	event->color = 0x100000;
	event->sec_color = 0xffffff;
	return (event);
}

t_event				*change_fractal(t_event *event, int fractal)
{
	if (fractal == 43)
		fractal = ((event->frc).id + AMOUNT_FRAC - 1) % AMOUNT_FRAC;	
	else if (fractal == 47)
		fractal = ((event->frc).id + AMOUNT_FRAC + 1) % AMOUNT_FRAC;	
	else if (fractal >= 18 && fractal < 21)
		fractal = fractal - 18;
	event->frc = find_frac(fractal);
	event->cur_grain = (event->frc).grain;
	mlx_destroy_window(event->mlx, event->win);
	free(event->img);
	event->img = init_image(event->mlx, (event->frc).width, (event->frc).height); 
	event->win = mlx_new_window(event->mlx, (event->frc).width,
			(event->frc).height, (event->frc).title); 
	loop(event);
	return (event);
}

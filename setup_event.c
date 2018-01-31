/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 13:57:50 by mpauw             #+#    #+#             */
/*   Updated: 2018/01/02 16:59:26 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_fractal	find_frac(int fractal)
{
	static t_fractal	frac_array[] = {
		{0, "Mandelbrot", &in_mand, 16, I_W, I_H, 255, -2.5, Y_Z, 4.0 / I_W},
		{1, "Julia", &in_julia, 8, I_W, I_H, 255, -2.0, Y_Z, 4.0 / I_W},
		{2, "Sierpinski", &in_sierp, 1, I_S, I_S, I_S, 0, 0, 3 / I_S},
		{3, "Triangle", &in_sierp, 1, I_H, I_H, 1, 0, 0, 1}
	};

	return (frac_array[fractal]);
}

t_event				*setup_event(void *mlx, int fractal)
{
	t_event		*event;
	t_complex	c;

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
	event->color = (fractal == 3) ? 0xffff : 0x100000;
	event->sec_color = 0xffffff;
	return (event);
}

t_event				*change_fractal(t_event *event, int fractal)
{
	if (fractal == 43)
		fractal = ((event->frc).id + AMOUNT_FRAC - 1) % AMOUNT_FRAC;
	else if (fractal == 47)
		fractal = ((event->frc).id + AMOUNT_FRAC + 1) % AMOUNT_FRAC;
	else if (fractal >= 18 && fractal <= 21)
		fractal = fractal - 18;
	event->frc = find_frac(fractal);
	event->cur_grain = (event->frc).grain;
	event->color = (fractal == 3) ? 0xffff : 0x100000;
	mlx_destroy_window(event->mlx, event->win);
	free(event->img);
	event->img = init_image(event->mlx, (event->frc).width,
			(event->frc).height);
	event->win = mlx_new_window(event->mlx, (event->frc).width,
			(event->frc).height, (event->frc).title);
	if ((event->frc).id != 3)
	{
		event = get_fractal(event);
		mlx_put_image_to_window(event->mlx, event->win, (event->img)->img_ptr,
			IMG_X, IMG_Y);
	}
	event->store_x = 0;
	event->store_y = 0;
	init_loop(event);
	return (event);
}

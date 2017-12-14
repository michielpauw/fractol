/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:12:27 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/14 18:19:54 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		key_pressed(int key, void *param)
{
	t_event	*event;

	event = (t_event *)param;
	if (key == 53)
		exit(0);
	else if (key == 126)
		event = set_move(event, -1);
	else if (key == 125)
		event = set_move(event, 1);
	else if (key == 123)
		event = set_move(event, -2);
	else if (key == 124)
		event = set_move(event, 2);
	else if ((key >= 6 && key <= 8) || (key >= 0 && key <= 2) || key == 0x0f ||
			key == 0x05 || key == 0x0b)
		event = set_color(event, key, 0);
	else if (key == 24 || key == 27)
		event = set_detail(event, key);
	else if (key == 0x23)
		event->disco = (event->disco + 1) % 2;
	event->cur_grain = (event->frc).grain;
	event = new_image(event);
	return (1);
}

static int		loop_event(void *param)
{
	t_event		*event;
	static int	colors[] = {0, 1, 2, 6, 7, 8, 0x0b, 0x05, 0x0f};

	event = (t_event *)param;
	if (event->disco)
		event = set_color(event, colors[abs(rand() % 6)], 1);
	if (event->cur_grain > 1)
	{
		event->cur_grain /= 2;
	}
	event = new_image(event);
	return (1);
}

void			handle_window(int fractal)
{
	void	*mlx;
	t_event	*event;

	mlx = mlx_init();
	event = setup_event(mlx, fractal);
	event->win = mlx_new_window(mlx, (event->frc).width,
			(event->frc).height, (event->frc).title); 
	event->img = init_image(mlx, (event->frc).width, (event->frc).height); 
	event = get_fractal(event);
	mlx_put_image_to_window(mlx, event->win, (event->img)->img_ptr, IMG_X, IMG_Y);
	mlx_key_hook(event->win, &key_pressed, event);
	mlx_mouse_hook(event->win, &mouse_click, event);
	mlx_loop_hook(mlx, &loop_event, event);
	if ((event->frc).id == 1)
		mlx_hook(event->win, MotionNotify, PointerMotionMask, &mouse_motion_julia, event);
	else if ((event->frc).id == 2)
		mlx_hook(event->win, MotionNotify, Button1MotionMask, &mouse_motion_sierpinski, event);
	mlx_loop(mlx);
}

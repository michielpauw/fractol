/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:12:27 by mpauw             #+#    #+#             */
/*   Updated: 2018/01/02 16:50:02 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		key_pressed(int key, void *param)
{
	t_event	*event;

	event = (t_event *)param;
	if (key == 53)
		exit(0);
	else if (key >= 123 && key <= 126)
		event = set_move(event, key);
	else if ((key >= 6 && key <= 8) || (key >= 0 && key <= 2) || key == 0x0f ||
			key == 0x05 || key == 0x0b)
		event = set_color(event, key, 0);
	else if (key == 24 || key == 27)
		event = set_detail(event, key);
	else if (key == 0x23)
		event->disco = (event->disco + 1) % 2;
	else if (key == 31)
		event->coor_wanted = (event->coor_wanted + 1) % 2;
	else if ((key >= 18 && key < (18 + AMOUNT_FRAC) && key != 24 && key != 27)
			|| key == 43 || key == 47)
		change_fractal(event, key);
	else if (key == 0x31)
		event->change_c = 1;
	event->cur_grain = (event->frc).grain;
	event = new_image(event);
	return (1);
}

static int		loop_event(void *param)
{
	t_event			*event;
	static int		colors[] = {0, 1, 2, 6, 7, 8, 0x0b, 0x05, 0x0f};
	static time_t	prev_time = 0;

	event = (t_event *)param;
	if (event->disco)
		event = set_color(event, colors[abs(rand() % 6)], 1);
	if ((event->frc).id == 3 && event->store_x)
		event = add_tri_point(event, 0, 0);
	else if (event->cur_grain > 1)
		event->cur_grain /= 2;
	if (event->cur_grain > 1 || (event->frc).id == 3 || (event->disco &&
				difftime(time(NULL), prev_time) >= 1))
	{
		prev_time = time(NULL);
		event = new_image(event);
		event->coor_put = 0;
	}
	if (!event->coor_put && event->coor_wanted && (event->frc).id < 2)
	{
		event = put_coordinates(event);
		event->coor_put = 1;
	}
	return (1);
}

static int		toggle_change_c(int key, void *param)
{
	t_event	*event;

	event = (t_event *)param;
	if (key == 0x31)
		event->change_c = 0;
	else
		key_pressed(key, param);
	return (1);
}

void			init_loop(t_event *event)
{
	mlx_key_hook(event->win, &key_pressed, event);
	mlx_mouse_hook(event->win, &mouse_click, event);
	mlx_loop_hook(event->mlx, &loop_event, event);
	if ((event->frc).id == 1)
	{
		mlx_hook(event->win, MOTION_NOTIFY, POINTER_MOTION_MASK,
				&mouse_motion_julia, event);
		mlx_hook(event->win, KEY_PRESS, KEY_PRESS_MASK,
				&toggle_change_c, event);
	}
	else if ((event->frc).id == 2)
		mlx_hook(event->win, MOTION_NOTIFY, BUTTON_MOTION_MASK,
				&mouse_motion_sierpinski, event);
	if (((event->frc).id == 1 || (event->frc).id == 0))
		mlx_hook(event->win, MOTION_NOTIFY, POINTER_MOTION_MASK,
				&drag_fractal, event);
	mlx_hook(event->win, BUTTON_RELEASE, BUTTON_RELEASE_MASK,
			&toggle_button, event);
	mlx_loop(event->mlx);
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
	if ((event->frc).id != 3)
	{
		event = get_fractal(event);
		mlx_put_image_to_window(mlx, event->win, (event->img)->img_ptr,
			IMG_X, IMG_Y);
	}
	init_loop(event);
}

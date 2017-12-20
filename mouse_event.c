/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 18:05:52 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/13 19:07:02 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_motion_julia(int x, int y, void *param)
{
	t_event	*event;

	event = (t_event *)param;
	if (event->change_c)
	{
		(event->c).r = get_re(event, x + (event->img)->size_line_int * y);
		(event->c).i = get_im(event, x + (event->img)->size_line_int * y);
		event->cur_grain = (event->frc).grain;
		event = new_image(event);
	}
	return (1);
}

int		mouse_motion_sierpinski(int x, int y, void *param)
{
	t_event	*event;

	event = (t_event *)param;
	if (event->mouse_hold)
	{
		if (x - event->store_x > 100)
		{
			event->store_x = x;
			event->store_y = y;
			(event->frc).val_pp *= 3.0;
		}
		else if (x - event->store_x < -100)
		{
			event->store_x = x;
			event->store_y = y;
			(event->frc).val_pp /= 3.0;
		}
		event->cur_grain = (event->frc).grain;
		event = new_image(event);
		event->moved = 1;
	}
	return (1);
}

int		drag_fractal(int x, int y, void *param)
{
	t_event	*ev;

	ev = (t_event *)param;
	if (ev->mouse_hold)
	{
		(ev->frc).y_zero += (ev->frc).val_pp * (ev->store_y - y);
		(ev->frc).x_zero += (ev->frc).val_pp * (ev->store_x - x);
		ev->store_x = x;
		ev->store_y = y;
		ev->moved = 1;
		ev->cur_grain = (ev->frc).grain;
		ev = new_image(ev);
	}
	else if ((ev->frc).id == 1)
		mouse_motion_julia(x, y, param);
	return (1);
}

int		mouse_click(int button, int x, int y, void *param)
{
	t_event	*event;

	event = (t_event *)param;
	event->moved = 0;
	if (button == 1)
	{
		event->mouse_hold = 1;
		event->store_x = x;
		event->store_y = y;
	}
	else
		toggle_button(button, x, y, param);
	return (1);
}

int		toggle_button(int button, int x, int y, void *param)
{
	t_event	*event;

	event = (t_event *)param;
	if (button == 1)
		event->mouse_hold = 0;
	if (!event->moved)
	{
		if (button == 1 || button == 4)
			event = set_zoom(event, x, y, 1);
		else if (button == 2 || button == 5)
			event = set_zoom(event, x, y, -1);
		event->cur_grain = (event->frc).grain;
		event = new_image(event);
	}
	return (1);
}

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
	(event->c).r = get_re(event, x + (event->img)->size_line_int * y);
	(event->c).i = get_im(event, x + (event->img)->size_line_int * y);
	event->cur_grain = (event->frc).grain;
	event = new_image(event);
	return (1);
}

int		mouse_motion_sierpinski(int x, int y, void *param)
{
	t_event	*event;

	event = (t_event *)param;
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
	return (1);
}

int		mouse_click(int button, int x, int y, void *param)
{
	t_event	*event;

	event = (t_event *)param;
	if (button == 1 || button == 4)
		event = set_zoom(event, x, y, 1);
	else if (button == 2 || button == 5)
		event = set_zoom(event, x, y, -1);
	event->cur_grain = (event->frc).grain;
	event = new_image(event);
	return (1);
}

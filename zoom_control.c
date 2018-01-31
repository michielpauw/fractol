/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 14:19:42 by mpauw             #+#    #+#             */
/*   Updated: 2018/01/02 16:47:45 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_event	*set_zoom(t_event *event, int x, int y, int dir)
{
	if ((event->frc).id == 2)
	{
		if (dir == 1)
			(event->frc).val_pp *= 3.0;
		else if ((event->frc).val_pp > 3.0 / I_S)
			(event->frc).val_pp /= 3.0;
		return (event);
	}
	(event->frc).x_zero = (event->frc).x_zero + dir * x *
		((event->frc).val_pp - (event->frc).val_pp * ZOOM_FACTOR);
	(event->frc).y_zero = (event->frc).y_zero + dir * y *
		((event->frc).val_pp - (event->frc).val_pp * ZOOM_FACTOR);
	if (dir > 0)
		(event->frc).val_pp = (event->frc).val_pp * ZOOM_FACTOR;
	else
		(event->frc).val_pp = (event->frc).val_pp / ZOOM_FACTOR;
	return (event);
}

t_event	*set_move(t_event *ev, int key)
{
	int	dir;

	if ((ev->frc).id == 2)
		return (ev);
	dir = (key == 125 || key == 124) ? 1 : -1;
	if (key == 125 || key == 126)
		(ev->frc).y_zero += (ev->frc).val_pp * dir * (ev->frc).height / 10;
	if (key == 123 || key == 124)
		(ev->frc).x_zero += (ev->frc).val_pp * dir * (ev->frc).width / 20;
	return (ev);
}

t_event	*set_color(t_event *event, int color, int disco)
{
	int	sign;

	sign = 1;
	if (color >= 6 && color <= 8)
		sign = -1;
	if (color == 0 || color == 6)
		event->color += sign * 0x020000;
	else if (color == 1 || color == 7)
		event->color += sign * 0x000200;
	else if (color == 2 || color == 8)
		event->color += sign * 0x000002;
	else if (color == 0x0f)
		event->color = 0x100000;
	else if (color == 0x05)
		event->color = 0x1000;
	else if (color == 0x0b)
		event->color = 0x10;
	if (event->color < 0)
		event->color = 0xffffff - event->color % 0xffffff;
	if (disco)
		event->sec_color = rand() % 0xffffff;
	return (event);
}

t_event	*set_detail(t_event *event, int detail)
{
	if (detail == 27 && detail > 0x10)
		(event->frc).iterations -= 0x10;
	else
		(event->frc).iterations += 0x10;
	return (event);
}

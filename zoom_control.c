/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 14:19:42 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/13 19:51:46 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_event	*set_zoom(t_event *event, int x, int y, int dir)
{
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

t_event	*set_move(t_event *event, int dir)
{
	if (dir == 1 || dir == -1)
		(event->frc).y_zero += (event->frc).val_pp * dir * IMG_H / 10;
	if (dir == 2 || dir == -2)
		(event->frc).x_zero += (event->frc).val_pp * dir * IMG_W / 20;
	return (event);
}

t_event	*set_color(t_event *event, int color, int disco)
{
	int	sign;

	sign = 1;
	if (color >= 6 && color <= 8)
		sign = -1;
	if (color == 0 || color == 6)
		event->color += sign * 0x010000;
	else if (color == 1 || color == 7)
		event->color += sign * 0x000100;
	else if (color == 2 || color == 8)
		event->color += sign * 0x000001;
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

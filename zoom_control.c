/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 14:19:42 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/11 16:52:24 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_img	*set_zoom(t_img *img, int x, int y, int dir)
{
	img->x_zero = img->x_zero + dir * x * (img->val_pp - img->val_pp *
			(img->zoom_new_r / (double)img->zoom_old_r));
	img->y_zero = img->y_zero + dir * y * (img->val_pp - img->val_pp *
			(img->zoom_new_r / (double)img->zoom_old_r));
	if (dir > 0)
		img->val_pp = img->val_pp * (img->zoom_new_r / (double)img->zoom_old_r);
	else
		img->val_pp = img->val_pp / (img->zoom_new_r / (double)img->zoom_old_r);
	return (img);
}

t_img	*set_move(t_img *img, int dir)
{
	if (dir == 1 || dir == -1)
		img->y_zero += img->val_pp * dir * IMG_H / 10;
	if (dir == 2 || dir == -2)
		img->x_zero += img->val_pp * dir * IMG_W / 20;
	return (img);
}

t_img	*set_color(t_img *img, int color)
{
	int	sign;

	sign = 1;
	if (color >= 6 && color <= 8)
		sign = -1;
	if (color == 0 || color == 6)
		img->color += sign * 0x010000;
	else if (color == 1 || color == 7)
		img->color += sign * 0x000100;
	else if (color == 2 || color == 8)
		img->color += sign * 0x000001;
	return (img);
}

t_img	*set_detail(t_img *img, int detail)
{
	if (detail == 27 && detail > 0x10)
		img->detail -= 0x10;
	else
		img->detail += 0x10;
	return (img);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:01:50 by mpauw             #+#    #+#             */
/*   Updated: 2018/01/02 16:47:46 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_event		*new_image(t_event *event)
{
	if ((event->frc).id != 3)
		event = get_fractal(event);
	mlx_put_image_to_window(event->mlx, event->win,
			(event->img)->img_ptr, IMG_X, IMG_Y);
	return (event);
}

t_img		*init_image(void *mlx, int width_scr, int height_scr)
{
	t_img	*img;
	int		bpp;
	int		size_line;
	int		endian;

	if (!(img = (t_img *)malloc(sizeof(t_img))))
		error(errno);
	img->img_ptr = mlx_new_image(mlx, width_scr, height_scr);
	img->width = width_scr;
	img->height = height_scr;
	img->img_arr = mlx_get_data_addr(img->img_ptr, &bpp, &size_line, &endian);
	img->bpp = bpp;
	img->size_line = size_line;
	img->size_line_int = size_line / (bpp / 8);
	img->endian = endian;
	return (img);
}

long double	get_re(t_event *event, int index)
{
	long double	re;

	re = (event->frc).x_zero + (event->frc).val_pp *
		(index % (event->img)->size_line_int);
	return (re);
}

long double	get_im(t_event *event, int index)
{
	long double	im;

	im = (event->frc).y_zero + index * (event->frc).val_pp /
		(event->img)->size_line_int;
	return (im);
}

int			fill_square(t_img **img, int index, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size && (index % (*img)->size_line_int) + i < (*img)->width)
	{
		j = 0;
		while (j < size && (index / (*img)->size_line_int) + j < (*img)->height)
		{
			((int *)((*img)->img_arr))[index + i + j *
				(*img)->size_line_int] = color;
			j++;
		}
		i++;
	}
	index += i;
	if (index % ((*img)->size_line_int) == 0)
	{
		index = index + 1 + ((j - 1) * ((*img)->size_line_int));
	}
	return (index);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:01:50 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/12 15:02:25 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

long double	get_re(t_img *img, int index)
{
	long double	re;

	re = img->x_zero + img->val_pp * (index % img->size_line_int);
	return (re);
}

long double	get_im(t_img *img, int index)
{
	long double	im;

	im = img->y_zero + index * img->val_pp / img->size_line_int;
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
			((int *)((*img)->img_arr))[index + i + j * (*img)->size_line_int] = color;
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
